#include "FlashInformations.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDataStream>
#include <QUrl>
#include <QEventLoop>




namespace RW{
	namespace CORE
	{
		const QString URLGetAcByGitHash = "http://bhd22ygg/10_Daimler/10_Portal/20_content/fDarling/OCF/api.php?action=getAcByGitHash&hash=";
		const QString URLGetACByIcom = "http://bhd22ygg/10_Daimler/10_Portal/20_content/fDarling/OCF/api.php?action=getAcByIcom&checksum=";
		const QString URLGetRelease = "http://bhd22ygg/10_Daimler/10_Portal/20_content/fDarling/OCF/api.php?action=getReleases";
		const QString URLGetSoftwareById = "http://bhd22ygg/10_Daimler/10_Portal/20_content/fDarling/OCF/api.php?action=getFlashableSoftwareById&id=";

		const quint8 RELEASEID = 0;
		const quint8 DATE = 1;
		const quint8 PROJECT = 2;
		const quint8 VARIANT = 3;
		const quint8 CONTROLLER = 4;
		const quint8 PHASE = 5;

		//BR213IC
		const QRegExp RegularExpressionProject("[a-zA-Z]{2,2}\\d{1,4}[a-zA-Z]{2,2}");
		//Kompletter neu zusammengesetzter MR-DB Name 
		const QRegExp RegularExpressionComplete("[a-zA-Z]{2,2}\\d{1,4}[a-zA-Z]{2,2}-[a-zA-Z]{2,2}-[a-zA-Z]{2,2}_*");

		const QRegExp RegularExpressionSamplePhase("[a-zA-Z]{1,1}\\d{1,4}");

		FlashInformations::FlashInformations(QObject* Parent) : QObject(Parent),
			m_ReleaseMap(new QMultiMap<QString, QString>())
		{
		}


		FlashInformations::~FlashInformations()
		{
			delete m_ReleaseMap;
		}


		QString FlashInformations::WebRequest(QNetworkRequest &Request)
		{
			QNetworkAccessManager accessManager;
			QNetworkReply* replay = accessManager.get(Request);

			//Warten bis Antwort komplett empfangen wurde
			QEventLoop loop;
			connect(replay, SIGNAL(finished()), &loop, SLOT(quit()));
			loop.exec();

			//Daten aus dem Antwortobjekt lesen
			QByteArray raw_data;
			if (replay->error() == QNetworkReply::NoError){
				raw_data = replay->readAll();
			}
			else{
				qDebug() << replay->errorString();
			}
			return raw_data;
		}

		/*
		@brief 
		@param Hash Git Hash der zu dem GC Stand passt.
		@return 
		*/
		QString FlashInformations::GetFittingAcByGitHash(QString Hash)
		{
			//URL für die Abfrage erzeugen
			QUrl url(URLGetAcByGitHash + Hash);
			return WebRequest(QNetworkRequest(url));
		}

		QString FlashInformations::GetAcByIcom(uint checksum)
		{
			//URL für die Abfrage erzeugen
			QUrl url(URLGetACByIcom + QString::number(checksum));
			return WebRequest(QNetworkRequest(url));
		}

		QString FlashInformations::GetReleases()
		{
			//URL für die Abfrage erzeugen
			QUrl url(URLGetRelease);
			return WebRequest(QNetworkRequest(url));
		}

		QStringList FlashInformations::GetSoftwareById(int systemId, bool AC, bool GC)
		{
			QString ACString = AC ? "True" : "False";
			QString GCString = GC ? "True" : "False";
			QUrl url(URLGetSoftwareById + QString::number(systemId) + "&AC=" + ACString + "&GC=" + GCString);

			QString softwareUrls = WebRequest(QNetworkRequest(url));
		
			return softwareUrls.split("\n");
		}

		void FlashInformations::PrepareProjectInformation()
		{
			//Ruft alle Release die derzeit auf dem Server sind
			QString Releases = GetReleases();

			//Jede Zeile des enthält einen Release, deswegen wird das gesamte Dokument nun aufgesplittet
			m_ReleaseBuffer = Releases.split("\n");

			qDebug() << m_ReleaseMap->uniqueKeys();
		}

		Util::ErrorID FlashInformations::FillReleaseMap()
		{
			for each (auto line in m_ReleaseBuffer)
			{
				QStringList splittedReleaseList = line.split(",");
				if (splittedReleaseList.count() >= PHASE)
				{
					//Projektname aktuell in der Form BR213IC_MY17, 
					QString Name = splittedReleaseList.at(PROJECT);
					RegularExpressionProject.indexIn(Name);
					QStringList ProjectNames = RegularExpressionProject.capturedTexts();
					if (ProjectNames.count() > 0)
					{
						//z.b.: BR213IC
						QString projectName = ProjectNames.at(0);
						//z.b.: _MY17 ... _Rel
						QString modelYearIndentifier = Name.section(RegularExpressionProject, 1);
						//z.b.  BR213IC-AC-HL_MY17
						QString completeReleaseName = projectName + "-" + splittedReleaseList.at(CONTROLLER) + "-" + splittedReleaseList.at(VARIANT) + modelYearIndentifier;

						if (RegularExpressionComplete.indexIn(completeReleaseName) > -1)
						{
							//fügt nun den kompleten Namen BR213IC-AC-HL_MY17 und die Phase E001Pre25 in die Map
							m_ReleaseMap->insertMulti(completeReleaseName, splittedReleaseList.at(PHASE));
						}
						else
						{
							return Util::ErrorID::ErrorPortalInfoFinalRegexCheck;
						}
					}
					else
					{
						return Util::ErrorID::ErrorPortalInfoProjectnameCount;
					}
				}
			}
			return Util::ErrorID::Success;
		}

		Util::ErrorID FlashInformations::GetUniqueKeys(QList<QString> &UniqueProjects)
		{
            PrepareProjectInformation();
			Util::ErrorID id = FillReleaseMap();
			if (id != Util::ErrorID::Success)
				return id;
			//Shalow Copy hier, weil ich davon ausgehe, das die ReleaseMap immer besteht und somit der Zugriff 
			//die Daten über die shalow copy immer möglich ist
			UniqueProjects = m_ReleaseMap->uniqueKeys();
			if (UniqueProjects.count() == 0)
				return  Util::ErrorID::ErrorPortalInfoProjectCount;
			return Util::ErrorID::Success;
		}

		Util::ErrorID FlashInformations::PrepareSamplePhaseInformation(QString SelectedProject, QList<QString> &UniqueSamplePhase)
		{
			QList<QString> values = m_ReleaseMap->values(SelectedProject);
			if (values.count() == 0)
			{
				return Util::ErrorID::ErrorPortalInfoSamplePhaseAndReleaseCount;
			}

			QSet<QString> uniqueSamplePhases;
			for each (auto var in values)
			{
				RegularExpressionSamplePhase.indexIn(var);
				QStringList samplePhaseList = RegularExpressionSamplePhase.capturedTexts();
				uniqueSamplePhases.insert(samplePhaseList.first());
			}

			UniqueSamplePhase = uniqueSamplePhases.toList();
			if (UniqueSamplePhase.count() == 0)
			{
				return Util::ErrorID::ErrorPortalInfoSamplePhaseCount;
			}
			return Util::ErrorID::Success;
		}

		Util::ErrorID FlashInformations::GetSamplePhaseList(QString SelectedProject, QList<QString> &UniqueSamplePhaseList)
		{
			return PrepareSamplePhaseInformation(SelectedProject, UniqueSamplePhaseList);
		}

		Util::ErrorID FlashInformations::PrepareReleaseInformation(QString SelectedSamplePhase, QString SelectedProject, QList<QString> &UniqueReleaseList)
		{
			QList<QString> values = m_ReleaseMap->values(SelectedProject);
			QSet<QString> uniqueSamplePhases;
			
			for each (auto var in values)
			{
				QRegExp regex("[a-zA-Z]{1,1}\\d{1,4}");
				regex.indexIn(var);
				QStringList qsl = regex.capturedTexts();
				if (qsl.first() == SelectedSamplePhase)
				{
					QRegExp regex("[a-zA-Z]{3,3}(\\d{1,4})?");
					regex.indexIn(var);

					UniqueReleaseList.append(regex.capturedTexts().first());
				}
			}
			return Util::ErrorID::Success;
		}

		Util::ErrorID FlashInformations::GetReleaseList(QString SelectedSamplePhase, QString SelectedProjec, QList<QString> &UniqueReleaseList)
		{
			if (PrepareReleaseInformation(SelectedSamplePhase, SelectedProjec, UniqueReleaseList) != Util::ErrorID::Success)
			{
				return Util::ErrorID::ErrorPortalInfoPrepareReleaseInformation;
			}
			if (UniqueReleaseList.count() == 0);
				return Util::ErrorID::ErrorPortalInfoReleaseCount;
			return Util::ErrorID::Success;
		}

		quint16 FlashInformations::GetSoftwareID(QString ProjectMain,QString Samplephase, QString Release, QString ProjectConttroller, QString ProjectVariant, QString ProjectModellYear)
		{
			quint16 id;
			try{
				for each (auto var in m_ReleaseBuffer)
				{
					if (var.contains(ProjectMain + "_" + ProjectModellYear)
						&& var.contains(Samplephase + Release)
						&& var.contains(ProjectConttroller)
						&& var.contains(ProjectModellYear)
						&& var.contains(ProjectVariant))
					{

						id = var.split(",").first().toInt();
					}
				}
				return id;
			}
			catch (...)
			{
				return 0;
			}
			
		}
	}
}
