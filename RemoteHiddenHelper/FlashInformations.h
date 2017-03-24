#pragma once
#include "qobject.h"
#include <RemoteCommunicationLibrary.h>

QT_BEGIN_NAMESPACE
class QNetworkRequest;
QT_END_NAMESPACE

namespace RW{
	namespace CORE
	{
		class FlashInformations :
			public QObject
		{
		private:
			QMultiMap<QString, QString>* m_ReleaseMap;
			QStringList m_ReleaseBuffer;
		public:
			FlashInformations(QObject* Parent = nullptr);
			~FlashInformations();
		private:
			QString GetFittingAcByGitHash(QString hash);
			QString GetAcByIcom(uint checksum);
			QString GetReleases();
			

			QString WebRequest(QNetworkRequest &Request);

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief Übertragt die Releasedaten in eine interne Verwaltungsstruktur.
			@return Zustand des Ausfühungsschrittes
			@retval COM::ErrorDecscription::ErrorPortalInfoFinalRegexCheck
			@retval COM::ErrorDecscription::ErrorPortalInfoProjectnameCount
			@retval COM::ErrorDecscription::Success
			**********************************************************************/
            COM::ErrorDecscription FillReleaseMap();

			void PrepareProjectInformation();

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief
			@return Zustand des Ausfühungsschrittes
			@retval COM::ErrorDecscription::ErrorPortalInfoSamplePhaseAndReleaseCount
			@retval COM::ErrorDecscription::ErrorPortalInfoSamplePhaseCount
			@retval COM::ErrorDecscription::Success
			**********************************************************************/
            COM::ErrorDecscription PrepareSamplePhaseInformation(QString SelectedProject, QList<QString> &UniqueSamplePhase);
            COM::ErrorDecscription PrepareReleaseInformation(QString SelectedSamplePhase, QString SelectedProject, QList<QString> &UniqueReleaseList);
		public:
			QStringList GetSoftwareById(int systemId, bool AC, bool GC);

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief Gibt eine Liste an Projekten zurück, die aus dem Portal gelesen wurden.
			@param[out] UniqueProjects
			@return Zustand des Ausfühungsschrittes
			@retval COM::ErrorDecscription::ErrorPortalInfoProjectCount
			@retval COM::ErrorDecscription::ErrorPortalInfoFinalRegexCheck
			@retval COM::ErrorDecscription::ErrorPortalInfoProjectnameCount
			@retval COM::ErrorDecscription::Success
			**********************************************************************/
            COM::ErrorDecscription GetUniqueKeys(QList<QString> &UniqueProjects);

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief
			@return Zustand des Ausfühungsschrittes
			@retval COM::ErrorDecscription::ErrorPortalInfoSamplePhaseAndReleaseCount
			@retval COM::ErrorDecscription::ErrorPortalInfoSamplePhaseCount
			@retval COM::ErrorDecscription::Success
			**********************************************************************/
            COM::ErrorDecscription GetSamplePhaseList(QString SelectedProject, QList<QString> &UniqueSamplePhase);

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief
			@return Zustand des Ausfühungsschrittes
			@retval COM::ErrorDecscription::ErrorPortalInfoPrepareReleaseInformation
			@retval COM::ErrorDecscription::ErrorPortalInfoReleaseCount
			@retval COM::ErrorDecscription::Success
			**********************************************************************/
            COM::ErrorDecscription GetReleaseList(QString SelectedSamplePhase, QString SelectedProjec, QList<QString> &UniqueReleaseList);
			quint16 GetSoftwareID(QString ProjectMain, QString Samplephase, QString Release, QString ProjectConttroller, QString ProjectVariant, QString ProjectModellYear);
		};
	}
}   
