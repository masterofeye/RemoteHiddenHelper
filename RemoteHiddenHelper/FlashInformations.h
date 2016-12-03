#pragma once
#include "qobject.h"
#include "Constants.h"

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
			@retval Util::ErrorID::ErrorPortalInfoFinalRegexCheck
			@retval Util::ErrorID::ErrorPortalInfoProjectnameCount
			@retval Util::ErrorID::Success
			**********************************************************************/
			Util::ErrorID FillReleaseMap();

			void PrepareProjectInformation();

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief
			@return Zustand des Ausfühungsschrittes
			@retval Util::ErrorID::ErrorPortalInfoSamplePhaseAndReleaseCount
			@retval Util::ErrorID::ErrorPortalInfoSamplePhaseCount
			@retval Util::ErrorID::Success
			**********************************************************************/
			Util::ErrorID PrepareSamplePhaseInformation(QString SelectedProject, QList<QString> &UniqueSamplePhase);
			Util::ErrorID PrepareReleaseInformation(QString SelectedSamplePhase, QString SelectedProject, QList<QString> &UniqueReleaseList);
		public:
			QStringList GetSoftwareById(int systemId, bool AC, bool GC);

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief Gibt eine Liste an Projekten zurück, die aus dem Portal gelesen wurden.
			@param[out] UniqueProjects
			@return Zustand des Ausfühungsschrittes
			@retval Util::ErrorID::ErrorPortalInfoProjectCount
			@retval Util::ErrorID::ErrorPortalInfoFinalRegexCheck
			@retval Util::ErrorID::ErrorPortalInfoProjectnameCount
			@retval Util::ErrorID::Success
			**********************************************************************/
			Util::ErrorID GetUniqueKeys(QList<QString> &UniqueProjects);

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief
			@return Zustand des Ausfühungsschrittes
			@retval Util::ErrorID::ErrorPortalInfoSamplePhaseAndReleaseCount
			@retval Util::ErrorID::ErrorPortalInfoSamplePhaseCount
			@retval Util::ErrorID::Success
			**********************************************************************/
			Util::ErrorID GetSamplePhaseList(QString SelectedProject, QList<QString> &UniqueSamplePhase);

			/*******************************************************************//**
			@autor Ivo Kunadt
			@brief
			@return Zustand des Ausfühungsschrittes
			@retval Util::ErrorID::ErrorPortalInfoPrepareReleaseInformation
			@retval Util::ErrorID::ErrorPortalInfoReleaseCount
			@retval Util::ErrorID::Success
			**********************************************************************/
			Util::ErrorID GetReleaseList(QString SelectedSamplePhase, QString SelectedProjec, QList<QString> &UniqueReleaseList);
			quint16 GetSoftwareID(QString ProjectMain, QString Samplephase, QString Release, QString ProjectConttroller, QString ProjectVariant, QString ProjectModellYear);
		};
	}
}   
