#pragma once

#include "qdatastream.h"
#include "Constants.h"
#include <RemoteCommunicationLibrary.h>

#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include "BasicWrapper.h"



inline QString GetMKSLink(QString Destination, QString MksLink)
{
	QRegExp reg("#b=\\d{1,1}.\\d{1,5}#");
	int i = reg.indexIn(MksLink);
	int ii = reg.matchedLength();
	MksLink = MksLink.replace(i + ii - 1, MksLink.count() - (i + ii - 1), "");

	QString left = MksLink.replace("#b=", "/");
	left = left.replace("#/id/", "");

	return Destination + left;
}

inline BOOL CALLBACK TerminateAppEnum(HWND hwnd, LPARAM lParam)
{
    DWORD dwID;

    GetWindowThreadProcessId(hwnd, &dwID);

    if (dwID == (DWORD)lParam)
    {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
    }

    return TRUE;
}



inline bool GetProcessByName(QString ProcessName, bool Terminate = false)
{
    DWORD aProcesses[1024], cbNeeded = 0 , cProcesses = 0;
    unsigned int i;

    //Zunächst versuchen die Applikation über WM_CLOSE zu schließen
    HANDLE   hProc = 0;
    DWORD   dwRet = 0;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return true;
    }

    cProcesses = cbNeeded / sizeof(DWORD);

    for (i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            char szProcessName[MAX_PATH];

            // Get a handle to the process.

            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                PROCESS_VM_READ | PROCESS_TERMINATE,
                FALSE, aProcesses[i]);

            // Get the process name.

            if (NULL != hProcess)
            {
                HMODULE hMod;
                DWORD cbNeeded;

                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
                    &cbNeeded))
                {
                    GetModuleBaseNameA(hProcess, hMod, szProcessName,
                        sizeof(szProcessName) / sizeof(TCHAR));
                }
            }

            // Compare process name with your string        
            bool matchFound = !strcmp(szProcessName, ProcessName.toStdString().c_str());


            if (matchFound)
            {
                if (Terminate)
                {
                    DWORD   dwPID = 0;
                    EnumWindows((WNDENUMPROC)TerminateAppEnum, (LPARAM)dwPID);

                    //Prüfen ob Applikation nun geschlossen ist, wenn nicht wenden wir Terminate Process an.
                    if (WaitForSingleObject(hProc, 5000) != WAIT_OBJECT_0)
                    {
                        DWORD error;
                        GetExitCodeProcess(hProcess, &error);
                        if (TerminateProcess(hProcess, error))
                        {
                            DWORD error = GetLastError();
                            return false;
                        }
                        else
                        {
                            DWORD error = GetLastError();
                            return true;
                        }
                    }
                }
                // Release the handle to the process.    
                CloseHandle(hProcess);
                return matchFound;
            }
            // Release the handle to the process.   
            CloseHandle(hProcess);
        }
    }
    return false;
}
