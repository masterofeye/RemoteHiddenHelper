#include "PortalInfo.h"
#include <qstring.h>
#include <qdatastream.h>
#include <qwidget.h>
#include <qurlquery.h>
#include <qtextcodec.h>
#include <QMultiMap>
#include <qregexp.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <QLabel>
#include <QMainWindow>

#include "ui_remotehiddenhelper.h"
#include "FlashInformations.h"




namespace RW{
    namespace CORE{
        PortalInfo::PortalInfo(QObject* Parent) : BasicWrapper(Parent),
            m_Dialog(nullptr),
            m_ui(nullptr), 
            m_FlashInformationen(new FlashInformations(this))
        {
        }


        PortalInfo::~PortalInfo()
        {
            delete m_ui;
            delete m_Dialog;
        }

        void PortalInfo::OnProcessMessage(Util::MessageReceiver Type, Util::Functions Func, QByteArray Report)
        {
            if (Type == Util::MessageReceiver::PortalInfo)
            {
                switch (Func)
                {
                case Util::Functions::PortalInfoShowDialog:
                    ShowDialog();
                    break;
                case Util::Functions::PortalInfoCloseDialog:
                    CloseDialog();
                    break;
                    //case Util::Functions::PortalInfoFittingAC:
                    //    GetFittingAcByGitHash(Report);
                    //    break;
                    //case Util::Functions::PortalInfoAcByIcom:
                    //    GetAcByIcom(Report.toInt());
                    //    break;
                    //case Util::Functions::PortalInfoReleases:
                    //    GetReleases();
                    //    break;
                    //case Util::Functions::PortalInfoSoftwareById:
                    //    GetSoftwareById(0, "", "");
                    //    break;
                default:
                    break;
                }
            }
        }

        // not all hashes have been build by the server ....
      


        void PortalInfo::ShowDialog()
        {
            if (m_Dialog == nullptr)
            {
                m_Dialog = new QMainWindow();
            }
            else if (m_Dialog->isHidden())
            {
                m_Dialog->setVisible(true);
            }

            if (m_ui == nullptr)
                m_ui = new Ui::RemoteHiddenHelperClass();

            m_ui->setupUi(m_Dialog);
            connect(m_ui->btnFlash, &QPushButton::pressed, this, &PortalInfo::Flash);

            FillProjectCombobox();

            m_Dialog->show();
        }

        void PortalInfo::CloseDialog()
        {
            if (m_Dialog != nullptr && m_Dialog->isVisible())
            m_Dialog->close();
        }


		Util::ErrorID PortalInfo::FillProjectCombobox()
		{
			QComboBox* cbProject = m_ui->cbProject;
			QList<QString> uniqueProjects;
			Util::ErrorID result = Util::ErrorID::Success;
			result = m_FlashInformationen->GetUniqueKeys(uniqueProjects);
			if (result != Util::ErrorID::Success)
			{
				emit NewMessage(Util::Functions::PortalInfoShowDialog, result, "");
				return result;
			}

			for each (auto var in uniqueProjects)
			{
				cbProject->insertItem(0, var);
			}
			//QOverload funktioniert hier nicht
			connect(cbProject, QOverload<const QString &>::of(&QComboBox::activated), this, &PortalInfo::FillSamplePhaseCombobox);
			return Util::ErrorID::Success;
		}

		Util::ErrorID PortalInfo::FillSamplePhaseCombobox(const QString &SelectedProject)
		{
			Util::ErrorID result = Util::ErrorID::Success;
			QComboBox* cbSample = m_ui->cbSamplePhase;
			//Löschen der Releases weil dieser vom User neu ausgewält werden müssen
			QComboBox* cbRelease = m_ui->cbRelease;
			cbRelease->clear();
			QList<QString> samplePhaseList;
			result = m_FlashInformationen->GetSamplePhaseList(SelectedProject, samplePhaseList);
			if (result != Util::ErrorID::Success)
			{
				emit NewMessage(Util::Functions::PortalInfoShowDialog, result, "");
				return result;
			}

			cbSample->clear();
			cbSample->insertItems(0, samplePhaseList);
			connect(cbSample, QOverload<const QString &>::of(&QComboBox::activated), this, &PortalInfo::FillReleaseCombobox);
			return Util::ErrorID::Success;
		}

		Util::ErrorID  PortalInfo::FillReleaseCombobox(const QString &SelectedSamplePhase)
		{
			Util::ErrorID result = Util::ErrorID::Success;
			QComboBox* cbRelease = m_ui->cbRelease;
			QComboBox* cbProject = m_ui->cbProject;
			QString selectedProject = cbProject->currentText();
			QList<QString> releaseList;
			result = m_FlashInformationen->GetReleaseList(SelectedSamplePhase, selectedProject, releaseList);
			if (result != Util::ErrorID::Success)
			{
				emit NewMessage(Util::Functions::PortalInfoShowDialog, result, "");
				return result;
			}
			cbRelease->addItems(releaseList);
			return Util::ErrorID::Success;
		}

        void PortalInfo::Flash()
        {
            NormalizeCheckBoxes();
            NormalizeComboBoxes();

            //AlleDatenfelder auslesen
            QComboBox* cbProject = m_ui->cbProject;
            QComboBox* cbSamplePhase = m_ui->cbSamplePhase;
            QComboBox* cbRelease = m_ui->cbRelease;

            QCheckBox* cbxBootLoader = m_ui->cbxBootloader;
            QCheckBox* cbxAC = m_ui->cbxAC;
            QCheckBox* cbxGC = m_ui->cbxGC;

            //Überprüfen ob notwendige Felder nicht ausgewählt wurden
            if (cbProject->currentText().isEmpty())
            {
                QMessageBox* m = new QMessageBox(m_Dialog);
                m->setText("Please choose a project.");
                m->show();
                HighlightComboBoxes(m_ui->lProject);
                return;
            }

            if (cbSamplePhase->currentText().isEmpty())
            {
                QMessageBox* m = new QMessageBox(m_Dialog);
                m->setText("Please choose a sample phase.");
                m->show();
                HighlightComboBoxes(m_ui->lSamplePhase);
                return;
            }

            if (cbRelease->currentText().isEmpty())
            {
                QMessageBox* m = new QMessageBox(m_Dialog);
                m->setText("Please choose a release.");
                m->show();
                HighlightComboBoxes(m_ui->lRelease);
                return;
            }

            if (!cbxBootLoader->isChecked() && !cbxAC->isChecked() && !cbxGC->isChecked())
            {
                QMessageBox* m = new QMessageBox(m_Dialog);
                m->setText("Please choose at least one component, that you want to flash.");
                m->show();
                HighlighCheckBoxes();

                return;
            }

			//Auslesen der Informationen aus den Steuerelementen
            QByteArray arr;
            QDataStream data(&arr, QIODevice::WriteOnly);

            QString Project = cbProject->currentText();
            QString Samplephase = cbSamplePhase->currentText();
            QString Release = cbRelease->currentText();

			bool FlashAC = cbxAC->isChecked();
			bool FlashGC = cbxGC->isChecked();
			bool FlasgBootloader = cbxBootLoader->isChecked();

            data << Project;
            data << Samplephase;
            data << Release;
			data << FlasgBootloader;
			data << FlashAC;
			data << FlashGC;

            QStringList splitted = Project.split("-");
            QString ProjectMain = splitted[0];
            QString ProjectConttroller = splitted[1];
            QStringList splitted2 = splitted[2].split("_");
            QString ProjectVariant  = splitted2[0];
            QString ProjectModellYear = splitted2[1];

			//Software Id aus dem Portal besorgen
			quint16 id = m_FlashInformationen->GetSoftwareID(ProjectMain, Samplephase, Release, ProjectConttroller, ProjectVariant, ProjectModellYear);

			//Da die ID nun klar ist, können die MKS links aus dem Portal geholt werden
			data << id;
			QStringList software = m_FlashInformationen->GetSoftwareById(id, FlashAC, FlashGC);
            
			//Wenn es nicht erwünscht ist den Bootloader zu flashen entfernen wir diesen hier. Dieser ist nähmlich standard mässig immer dabei
            if (!FlasgBootloader)
                software.removeFirst();

			//Auslesen wieiviel Flashfiles wir bekommen haben ...
            data << software.count();
            for each (auto var in software)
            {
				//.... und schreiben diesen nun auch hier weg
                if (!var.isEmpty())
                    data << var;
            }

			//Alle Informationen sind abgefragt. Nun kann der Dialog verschwinden
            m_Dialog->hide();
			//Es muss noch das Signal ermitted werden um den Arbeisschritt abzuschließen, gleichzeitig werden auch die Informationen an den 
			//Communikationsmanager geschickt
            emit NewMessage(Util::Functions::PortalInfoShowDialog, Util::ErrorID::Success, arr);
        }


        void PortalInfo::HighlighCheckBoxes()
        {
            QCheckBox* cbxBootLoader = m_ui->cbxBootloader;
            QCheckBox* cbxAC = m_ui->cbxAC;
            QCheckBox* cbxGC = m_ui->cbxGC;

            cbxBootLoader->setStyleSheet("QCheckBox { color: red }");
            cbxAC->setStyleSheet("QCheckBox { color: red }");
            cbxGC->setStyleSheet("QCheckBox { color: red }");
        }

        
        void PortalInfo::HighlightComboBoxes(QLabel* Highlight)
        {
            Highlight->setStyleSheet("QLabel { color: red }");
        }                

        void PortalInfo::NormalizeCheckBoxes()
        {
            QCheckBox* cbxBootLoader = m_ui->cbxBootloader;
            QCheckBox* cbxAC = m_ui->cbxAC;
            QCheckBox* cbxGC = m_ui->cbxGC;


            cbxBootLoader->setStyleSheet("QCheckBox { color: black }");
            cbxAC->setStyleSheet("QCheckBox { color: black }");
            cbxGC->setStyleSheet("QCheckBox { color: black }");
        }

        void PortalInfo::NormalizeComboBoxes()
        {
            QLabel* cbProject = m_ui->lProject;
            QLabel* cbSamplePhase = m_ui->lSamplePhase;
            QLabel* cbRelease = m_ui->lRelease;

            cbProject->setStyleSheet("QLabel { color: black }");
            cbSamplePhase->setStyleSheet("QLabel { color: black }");
            cbRelease->setStyleSheet("QLabel { color: black }");

        }

    }
}