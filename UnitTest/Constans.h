#pragma once

#include <qobject.h>
namespace RW{
	namespace CORE{
#ifdef QT
		class Util
		{
			Q_GADGET
		public:
#endif
			enum class FlashType
			{
				Bootloader,
				AC,
				GC,
				NON,
			};
#ifdef QT
			Q_ENUM(FlashType)
#endif
			enum class MessageReceiver
			{
				CommunicationServer,
				ProcessManager,
				CanEasyWrapper,
				BasicWrapper,
				PortalInfo,
				FHostSPWrapper,
				MKSWrapper,
			};
#ifdef QT
			Q_ENUM(MessageReceiver)
#endif
			enum class Functions
			{
				CanEasyStartApplication,
				CanEasyLoadWorkspace,
				CanEasyCloseApplication,
				CanEasyStartSimulation,
				CanEasyStopSimulation,
				MKSLogin,
				MKSStartDownload,
				MKSCreateSandBox,
				MKSDropSandbox,
				MKSClose,
				FHostSPStartFHost,
				FHostSPLoadFlashFile,
				FHostSPCloseFHost,
				FHostSPGetState,
				FHostSPAbortSequence,
				FHostSPCloseSequence,
				FHostSPStartFlash,
				FHostSPGetProgress,
				PortalInfoFittingAC,
				PortalInfoAcByIcom,
				PortalInfoReleases,
				PortalInfoSoftwareById,
				PortalInfoShowDialog,
				PortalInfoCloseDialog,
				Amount
			};
#ifdef QT
			Q_ENUM(Functions)
#endif
			enum class ErrorID
			{
				Success,
				Error,
				Busy,
				ErrorCanEasyComServerMissing,
				ErrorCanEasyStartSimulation,
				ErrorCanEasySimulationIsRunningFailed,
				ErrorCanEasyStopSimulation,
				ErrorCanEasyWorkspaceNotFound,
				ErrorCanEasyWorkspaceNotLoaded,
				ErrorCanEasyApplicationError,
				ErrorCanEasyDeInitError,
				ErrorMKSLocationMissing,
				ErrorMKSError,
				ErrorMKSSandBoxCreation,
				ErrorMKSSanbBoxDrop,
				ErrorMKSMissingParameter,
				ErrorFHostSPStartApplication,
				ErrorFHostSPSequenceStop,
				ErrorFHostSPSequenceStart,
				ErrorFHostSPLoadFlashfileStatusFailed,
				ErrorFHostSPLoadFlashfileFailed,
				ErrorFHostSPFlashfileNotExits,
				ErrorFHostSPGetProgress,
				ErrorFHostSPCloseApplication,
				ErrorFHostSPGetStateFailed,
				ErrorFHostSPAbortFailed,
				ErrorPortalInfoFinalRegexCheck,
				ErrorPortalInfoProjectnameCount,
				ErrorPortalInfoProjectCount,
				ErrorPortalInfoSamplePhaseAndReleaseCount,
				ErrorPortalInfoSamplePhaseCount,
				ErrorPortalInfoPrepareReleaseInformation,
				ErrorPortalInfoReleaseCount,
			};
#ifdef QT
			Q_ENUM(ErrorID)
#endif

			enum class FHostSPState
			{
				JOB_EXECUTE_OK,
				JOB_EXECUTE_NOT_OK,
				JOB_IDLE,
				JOB_LOADING,
				JOB_LOAD_NOT_OK,
				JOB_LOAD_OK,
				JOB_LOAD_WARNING,
				JOB_EXECUTING,
				JOB_NO_DONGLE
			};
#ifdef QT
			Q_ENUM(FHostSPState)
		};
#endif

		typedef struct _Message
		{
			Util::Functions MessageType;
			quint16 MessageSize;
			QByteArray Message;
			Util::ErrorID Error;

			_Message()
			{
				Util::Functions MessageType = Util::Functions::Amount;
				quint16 MessageSize = 0;
				QByteArray Message = QByteArray();
				Error = Util::ErrorID::Success;
			}
			_Message(Util::Functions MessageType, quint16 MessageSize, QByteArray Message, Util::ErrorID Error)
			{
				this->MessageType = MessageType;
				this->MessageSize = MessageSize;
				this->Message = Message;
				this->Error = Error;
			}
		} Message;

		typedef struct _FlashInfo
		{
			QString FlashFile;
			Util::FlashType FlashType;
			QString TargetDir;

			_FlashInfo()
			{
				FlashFile = "";
				FlashType = Util::FlashType::NON;
				TargetDir = "";

			}
			_FlashInfo(QString FlashFile, Util::FlashType, QString TargetDir)
			{
				this->FlashFile = FlashFile;
				this->FlashType = FlashType;
				this->TargetDir = TargetDir;
			}
		}FlashInfo;
	}
}