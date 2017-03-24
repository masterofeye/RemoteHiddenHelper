#include "CanEasyWrapper.h"
#include <qfile.h>
#include <qfileinfo.h>
#include <qthread.h>

#include "Util.h"

namespace RW{
	namespace CORE{

        CanEasyWrapper::CanEasyWrapper(QObject* Parent) : BasicWrapper(Parent),
            m_IsRunning(false)
		{
		}


		CanEasyWrapper::~CanEasyWrapper()
		{
		}

		void CanEasyWrapper::OnProcessMessage(COM::Message Msg)
		{
			switch (Msg.MessageID())
			{
			case COM::MessageDescription::EX_CanEasyStartApplication:
				StartCanEasy(QFile(Msg.ParameterList()[0].toString()));
				break;
			case COM::MessageDescription::EX_CanEasyLoadWorkspace:
				LoadWorkspace(QFile(Msg.ParameterList()[0].toString()));
				break;
			case COM::MessageDescription::EX_CanEasyStartSimulation:
				StartSimulation();
				break;
			case COM::MessageDescription::EX_CanEasyStopSimulation:
				StopSimulation();
				break;
			case COM::MessageDescription::EX_CanEasyCloseApplication:
				StopCanEasy();
				break;
			default:
				break;
			}
		}

		void CanEasyWrapper::StartCanEasy(const QFile &File)
		{
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_CanEasyStartApplication);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            //Wenn ein CanEasy noch offen ist, wird es zunächst geschlossen
            if (GetProcessByName("CanEasy.exe", true))
            {
				msg.SetSuccess(false);
				msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyApplication));
				emit NewMessage(msg);
                return;
            }

			CoInitialize(nullptr);

			HRESULT hr = CoCreateInstance(__uuidof(CanEasyProcess), NULL, CLSCTX_LOCAL_SERVER/*CLSCTX_ALL*/, __uuidof(ICanEasyProcess), (void**)&m_Process);
			if (FAILED(hr))
			{
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyCoCreateInstance));
				emit NewMessage(msg);
			    return;
			}
			
			CComPtr<IDispatch> appDisp;
			
            hr = m_Process->GetApplication(&appDisp);
			if (FAILED(hr))
			{    
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyGetApplication));
				emit NewMessage(msg);
			    return;
			}


			appDisp->QueryInterface(__uuidof(ICanEasyApplication), (void**)&m_App);
			
			CComPtr<IAppWindow> appWindow;
			hr = m_App->get_AppWindow(&appWindow);
			if (FAILED(hr))
			{
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyGetAppWindow));
				emit NewMessage(msg);
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

			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

		void CanEasyWrapper::LoadWorkspace(const QFile &File)
		{
			//"C:\\Arbeitsbereiche_PF3\\Arbeitsbereich_BR213_V4.50\\W213\\CanEasyBR213_V4.50.csm"
            COM::Message msg;
            msg.SetMessageID(COM::MessageDescription::EX_CanEasyLoadWorkspace);
            msg.SetIsExternal(true);
            msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			if (!File.exists())
			{
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyWorkspaceNotFound));
				emit NewMessage(msg);
                return;
			}

			HRESULT hr = m_App->LoadWorkspace(_bstr_t(QFileInfo(File).absoluteFilePath().toStdString().c_str()));
            if (FAILED(hr))
            {
				msg.SetExcVariant(COM::Message::ExecutionVariant::NON);
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyWorkspaceNotLoaded));
				emit NewMessage(msg);
                return;
            }

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);
			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

		void CanEasyWrapper::StopCanEasy()
		{
 			HRESULT hr = m_App->StopSimulation();
			COM::Message msg;
			msg.SetMessageID(COM::MessageDescription::EX_CanEasyCloseApplication);
			msg.SetIsExternal(true);
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

			if (FAILED(hr))
			{
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyStop));
				emit NewMessage(msg);
			}

            hr = m_App->DeInit();
			if (FAILED(hr))
			{
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyDeInit));
				emit NewMessage(msg);
			}
            //Warten bis CanEasy wirklich beendet ist
            QThread::msleep(2000);
            //! \todo hier könnte man nochmal abfragen ob CanEasy wirklich tot ist 
            m_IsRunning = false;

            m_App.Detach();
            m_App.Release();

            m_Process.Detach();
            m_Process.Release();

			CoUninitialize();

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

		void CanEasyWrapper::StartSimulation()
		{
			HRESULT hr = m_App->StartSimulation();
			COM::Message msg;
			msg.SetMessageID(COM::MessageDescription::EX_CanEasyStartSimulation);
			msg.SetIsExternal(true);
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);
			if (FAILED(hr))
			{
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyStartSimulation));
				emit NewMessage(msg);
                return;
			}
            
            VARIANT_BOOL isRunning = false;

            do
            {
                Sleep(100);
                hr = m_App->get_SimulationIsRunning(&isRunning);
                if (FAILED(hr))
				{
					msg.SetSuccess(false);
                    msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyStartSimulation));
					emit NewMessage(msg);
                    return;
				}
            } while (!isRunning);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

		void CanEasyWrapper::StopSimulation()
		{
			HRESULT hr = m_App->StopSimulation();
			COM::Message msg;
			msg.SetMessageID(COM::MessageDescription::EX_CanEasyStopSimulation);
			msg.SetIsExternal(true);
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);
			if (FAILED(hr))
			{
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyStopSimulation));
				emit NewMessage(msg);
                return;
			}

            VARIANT_BOOL isRunning = false;

            do
            {
                Sleep(100);
                hr = m_App->get_SimulationIsRunning(&isRunning);
				if (FAILED(hr))
				{
					msg.SetSuccess(false);
                    msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyStopSimulation));
					emit NewMessage(msg);
                    return;
				}
			} while (isRunning);

            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetSuccess(true);
			emit NewMessage(msg);
		}

        void CanEasyWrapper::CloseExplicit()
        {
			COM::Message msg;
			msg.SetMessageID(COM::MessageDescription::EX_CanEasyCloseApplication);
			msg.SetIsExternal(true);
			msg.SetExcVariant(COM::Message::ExecutionVariant::NON);

            HRESULT hr = m_App->StopSimulation();
            if (FAILED(hr))
            {
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyStopSimulation));
				emit NewMessage(msg);
            }

            VARIANT_BOOL isRunning = false;

            do
            {
                Sleep(100);
                hr = m_App->get_SimulationIsRunning(&isRunning);
                if (FAILED(hr))
                {
					msg.SetSuccess(false);
                    msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyStopSimulation));
					emit NewMessage(msg);
                }
            } while (isRunning);

            hr = m_App->DeInit();
            if (FAILED(hr))
            {
				msg.SetSuccess(false);
                msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::ErrorCanEasyDeInit));
				emit NewMessage(msg);
            }

            m_IsRunning = false;
            CoUninitialize();
            msg.SetResult(QVariant::fromValue(COM::ErrorDecscription::Success));
			msg.SetSuccess(true);
			emit NewMessage(msg);
        }
	}
}
