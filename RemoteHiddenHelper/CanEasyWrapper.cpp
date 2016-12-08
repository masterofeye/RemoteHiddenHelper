#include "CanEasyWrapper.h"
#include <qfile.h>
#include <qfileinfo.h>
#include <qthread.h>

namespace RW{
	namespace CORE{

        CanEasyWrapper::CanEasyWrapper(QObject* Parent) : BasicWrapper(Parent),
            m_IsRunning(false)
		{
		}


		CanEasyWrapper::~CanEasyWrapper()
		{
		}

		void CanEasyWrapper::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report)
		{
			if (Type == Util::MessageReceiver::CanEasyWrapper)
			{
				switch (Func)
				{
				case RW::CORE::Util::Functions::CanEasyStartApplication:
					StartCanEasy(QFile(Report));
					break;
				case RW::CORE::Util::Functions::CanEasyLoadWorkspace:
					LoadWorkspace(QFile(Report));
					break;
				case RW::CORE::Util::Functions::CanEasyStartSimulation:
					StartSimulation();
					break;
				case RW::CORE::Util::Functions::CanEasyStopSimulation:
					StopSimulation();
					break;
				case RW::CORE::Util::Functions::CanEasyCloseApplication:
					StopCanEasy();
					break;
				default:
					break;
				}
			}
		}

		void CanEasyWrapper::StartCanEasy(const QFile &File)
		{
			CoInitialize(nullptr);


			HRESULT hr = CoCreateInstance(__uuidof(CanEasyProcess), NULL, CLSCTX_LOCAL_SERVER/*CLSCTX_ALL*/, __uuidof(ICanEasyProcess), (void**)&m_Process);
			if (FAILED(hr))
			{
				emit NewMessage(Util::Functions::CanEasyStartApplication, Util::ErrorID::ErrorCanEasyComServerMissing, "Can't create CanEasy Instance");
			    return;
			}
			
			CComPtr<IDispatch> appDisp;
			
            hr = m_Process->GetApplication(&appDisp);
			if (FAILED(hr))
			{       
				emit NewMessage(Util::Functions::CanEasyStartApplication, Util::ErrorID::ErrorCanEasyApplicationError, "Can't create CanEasy Instance");
			    return;
			}


			appDisp->QueryInterface(__uuidof(ICanEasyApplication), (void**)&m_App);
			
			CComPtr<IAppWindow> appWindow;
			hr = m_App->get_AppWindow(&appWindow);
			if (FAILED(hr))
			{
				emit NewMessage(Util::Functions::CanEasyStartApplication, Util::ErrorID::ErrorCanEasyApplicationError, "Can't create CanEasy Instance");
			    return;
			}
			
			hr = appWindow->ChangePosition(0, 0);
			if (FAILED(hr))
			{
				//nicht so schlimm
			}

			//hr = appWindow->Close();
			//if (FAILED(hr))
			//{
			//	//nicht so schlimm
			//}

            appWindow.Detach();
            appWindow.Release();

            m_IsRunning = true;
			emit NewMessage(Util::Functions::CanEasyStartApplication, Util::ErrorID::Success, nullptr);
		}

		void CanEasyWrapper::LoadWorkspace(const QFile &File)
		{
			//"C:\\Arbeitsbereiche_PF3\\Arbeitsbereich_BR213_V4.50\\W213\\CanEasyBR213_V4.50.csm"

			if (!File.exists())
			{
				emit NewMessage(Util::Functions::CanEasyLoadWorkspace, Util::ErrorID::ErrorCanEasyWorkspaceNotFound, nullptr);
                return;
			}

			HRESULT hr = m_App->LoadWorkspace(_bstr_t(QFileInfo(File).absoluteFilePath().toStdString().c_str()));
            if (FAILED(hr))
            {
				emit NewMessage(Util::Functions::CanEasyLoadWorkspace, Util::ErrorID::ErrorCanEasyWorkspaceNotLoaded, nullptr);
                return;
            }
			emit NewMessage(Util::Functions::CanEasyLoadWorkspace, Util::ErrorID::Success, nullptr);
		}

		void CanEasyWrapper::StopCanEasy()
		{
 			HRESULT hr = m_App->StopSimulation();
            if (FAILED(hr))
				emit NewMessage(Util::Functions::CanEasyCloseApplication, Util::ErrorID::ErrorCanEasyStopSimulation, nullptr);

            hr = m_App->DeInit();
            if (FAILED(hr))
				emit NewMessage(Util::Functions::CanEasyCloseApplication, Util::ErrorID::ErrorCanEasyDeInitError, nullptr);
            //Warten bis CanEasy wirklich beendet ist
            QThread::msleep(2000);
            //! \todo hier könnte man nochmal abfragen ob CanEasy wirklich tot ist 
            m_IsRunning = false;

            m_App.Detach();
            m_App.Release();

            m_Process.Detach();
            m_Process.Release();

			CoUninitialize();
			emit NewMessage(Util::Functions::CanEasyCloseApplication, Util::ErrorID::Success, nullptr);
		}

		void CanEasyWrapper::StartSimulation()
		{
			HRESULT hr = m_App->StartSimulation();
			if (FAILED(hr))
				emit NewMessage(Util::Functions::CanEasyStartSimulation, Util::ErrorID::ErrorCanEasyStartSimulation, nullptr);
            
            VARIANT_BOOL isRunning = false;

            do
            {
                Sleep(100);
                hr = m_App->get_SimulationIsRunning(&isRunning);
                if (FAILED(hr))
					emit NewMessage(Util::Functions::CanEasyStartSimulation, Util::ErrorID::ErrorCanEasySimulationIsRunningFailed, nullptr);
            } while (!isRunning);

			emit NewMessage(Util::Functions::CanEasyStartSimulation, Util::ErrorID::Success, nullptr);
		}

		void CanEasyWrapper::StopSimulation()
		{
			HRESULT hr = m_App->StopSimulation();
			if (FAILED(hr))
				emit NewMessage(Util::Functions::CanEasyStopSimulation, Util::ErrorID::ErrorCanEasyStartSimulation, nullptr);

            VARIANT_BOOL isRunning = false;

            do
            {
                Sleep(100);
                hr = m_App->get_SimulationIsRunning(&isRunning);
                if (FAILED(hr))
					emit NewMessage(Util::Functions::CanEasyStartSimulation, Util::ErrorID::ErrorCanEasySimulationIsRunningFailed, nullptr);
            } while (isRunning);
			emit NewMessage(Util::Functions::CanEasyStopSimulation, Util::ErrorID::Success, nullptr);
		}

        void CanEasyWrapper::CloseExplicit()
        {
        
            HRESULT hr = m_App->StopSimulation();
            if (FAILED(hr))
            {
            }

            VARIANT_BOOL isRunning = false;

            do
            {
                Sleep(100);
                hr = m_App->get_SimulationIsRunning(&isRunning);
                if (FAILED(hr))
                {

                }
            } while (isRunning);

            hr = m_App->DeInit();
            if (FAILED(hr))
            {

            }

            m_IsRunning = false;
            CoUninitialize();
        }
	}
}
