#pragma		once
#include "BasicWrapper.h"

namespace Ui {
    class RemoteHiddenHelperClass;
    
}

QT_BEGIN_NAMESPACE
class QMainWindow;
class QIODevice;
class QLabel;
QT_END_NAMESPACE

namespace RW{
	namespace CORE{
		class FlashInformations;

		/***************************************************************************************************************//**
		@autor Ivo Kunadt
		@brief Sammelt die Informationen zum flasen einen Standes. Ist an sich kein wirkliche Wrapperklassse aber verarbeitet
		Anfragen, wie eine solche. 
		********************************************************************************************************************/
		class PortalInfo : public BasicWrapper
		{
			Q_OBJECT
        private:
            QMainWindow *m_Dialog;
            Ui::RemoteHiddenHelperClass *m_ui;

			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Datenobjekt welches für die Aufbereitung der Flashinformationen dient. Beinhaltet die Methoden um über das 
			Portal die Informationen zum flashen abzurufen. 
			********************************************************************************************************************/
			FlashInformations* m_FlashInformationen;
        private: 
			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Färbt die Schriftfarbe der Checkbox ein um den User darauf aufmerksam zu machen, das er min. eine Checkboxen 
			makieren sollte.
			@return void
			********************************************************************************************************************/
            void HighlighCheckBoxes();
			
			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Färbt die Schriftfarbe der Combobox ein um den User darauf aufmerksam zu machen, das er min. eine Checkboxen 
			makieren sollte.
			@param[in] Highlight Das Label welches manipuliert werden soll.
			@return void
			********************************************************************************************************************/
            void HighlightComboBoxes(QLabel* Highlight);

			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Setzt die urspürnglichen Eigenschaften der Checkbox, nach einem Highlight Aufruf, wieder zurück.
			@return void
			********************************************************************************************************************/
            void NormalizeCheckBoxes();

			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Setzt die urspürnglichen Eigenschaften der Combobox, nach einem Highlight Aufruf, wieder zurück.
			@return void 
			********************************************************************************************************************/
            void NormalizeComboBoxes();

			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Zeigt den Dialog für die Auswahl des Projektes an.
			@return void
			********************************************************************************************************************/
			void ShowDialog();

			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Schließt den Dialog für die Auswahl des Projektes an.
			@return void
			********************************************************************************************************************/
			void CloseDialog();

			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Ließt alle notwendigen Daten aus Steuerelemten aus und emited das Signal für den Abschluss des
			Arbeitsschrittes.
			@return void
			********************************************************************************************************************/
			void Flash();
		public:
			PortalInfo(QObject* Parent = nullptr);
			~PortalInfo();

         private slots:
			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Füllt die ComboBox, die die Auswahlmöglichkeit für die Projekte liefer. Dabei wird der Name entsprechend der 
			MR-DB zusammengesetzt. 
			@return COM::ErrorDecscription Status des Ausführungschrittes
			********************************************************************************************************************/
			COM::ErrorDecscription  FillProjectCombobox();

			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Füllt die Combobox, die die Auswahlmöglichkeit für die Sample Phase liefert.
			@param[in] SelectedProject Das zuvor aus der Projekt Combobox ausgewählte Projekt. 
			@return COM::ErrorDecscription Status des Ausführungschrittes
			********************************************************************************************************************/
			COM::ErrorDecscription  FillSamplePhaseCombobox(const QString &SelectedProject);

			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Füllt die Combobox, die die Auswahlmöglichkeit für die Release Version liefert. 
			@param[in] SelectedSamplePhase Die zuvor aus der SamplePhase Combobox ausgewählte Samplephase. 
			@return COM::ErrorDecscription Status des Ausführungschrittes
			
			********************************************************************************************************************/
			COM::ErrorDecscription  FillReleaseCombobox(const QString &SelectedSamplePhase);
		public slots:
			/***************************************************************************************************************//**
			@autor Ivo Kunadt
			@brief Message Verarbeitungsroutine, Alle Nachrichten die vom CommunikationsManager empfangen werden, weden zunächst
			an diesen Slot geleitet und werden im Anschluss gefiltert. Nachrichten die nicht dem Filter entsprechen werden
			verworfen. 
			@param[in] Type Basistype der Nachricht
			@param[in] Func Arbeitsschritt der durchgeführt werden soll
			@param[in] Report Userdaten, die eine oder mehrere Informationen enthalten können. Die Daten werden dabei mit einem 
			QDataStream in die Nachricht geschrieben. 
			@return void
			********************************************************************************************************************/
			virtual void OnProcessMessage(COM::Message Msg);
		};
	}
}
