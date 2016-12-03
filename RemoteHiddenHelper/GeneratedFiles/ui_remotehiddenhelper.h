/********************************************************************************
** Form generated from reading UI file 'remotehiddenhelper.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTEHIDDENHELPER_H
#define UI_REMOTEHIDDENHELPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteHiddenHelperClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *Integration;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_12;
    QPushButton *btnFlash;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_13;
    QCheckBox *cbxBootloader;
    QCheckBox *cbxAC;
    QCheckBox *cbxGC;
    QVBoxLayout *verticalLayout_11;
    QLabel *lProject;
    QComboBox *cbProject;
    QLabel *lSamplePhase;
    QComboBox *cbSamplePhase;
    QLabel *lRelease;
    QComboBox *cbRelease;
    QVBoxLayout *verticalLayout_2;
    QListView *listView;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frame;
    QWidget *tab;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RemoteHiddenHelperClass)
    {
        if (RemoteHiddenHelperClass->objectName().isEmpty())
            RemoteHiddenHelperClass->setObjectName(QStringLiteral("RemoteHiddenHelperClass"));
        RemoteHiddenHelperClass->resize(600, 400);
        centralWidget = new QWidget(RemoteHiddenHelperClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        Integration = new QWidget();
        Integration->setObjectName(QStringLiteral("Integration"));
        verticalLayout_4 = new QVBoxLayout(Integration);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        btnFlash = new QPushButton(Integration);
        btnFlash->setObjectName(QStringLiteral("btnFlash"));

        verticalLayout_12->addWidget(btnFlash);

        groupBox = new QGroupBox(Integration);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_14 = new QVBoxLayout(groupBox);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        cbxBootloader = new QCheckBox(groupBox);
        cbxBootloader->setObjectName(QStringLiteral("cbxBootloader"));

        verticalLayout_13->addWidget(cbxBootloader);

        cbxAC = new QCheckBox(groupBox);
        cbxAC->setObjectName(QStringLiteral("cbxAC"));

        verticalLayout_13->addWidget(cbxAC);

        cbxGC = new QCheckBox(groupBox);
        cbxGC->setObjectName(QStringLiteral("cbxGC"));

        verticalLayout_13->addWidget(cbxGC);


        verticalLayout_14->addLayout(verticalLayout_13);


        verticalLayout_12->addWidget(groupBox);


        horizontalLayout_2->addLayout(verticalLayout_12);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        lProject = new QLabel(Integration);
        lProject->setObjectName(QStringLiteral("lProject"));

        verticalLayout_11->addWidget(lProject);

        cbProject = new QComboBox(Integration);
        cbProject->setObjectName(QStringLiteral("cbProject"));

        verticalLayout_11->addWidget(cbProject);

        lSamplePhase = new QLabel(Integration);
        lSamplePhase->setObjectName(QStringLiteral("lSamplePhase"));
        lSamplePhase->setFrameShape(QFrame::NoFrame);
        lSamplePhase->setFrameShadow(QFrame::Plain);
        lSamplePhase->setLineWidth(1);
        lSamplePhase->setTextFormat(Qt::AutoText);

        verticalLayout_11->addWidget(lSamplePhase);

        cbSamplePhase = new QComboBox(Integration);
        cbSamplePhase->setObjectName(QStringLiteral("cbSamplePhase"));

        verticalLayout_11->addWidget(cbSamplePhase);

        lRelease = new QLabel(Integration);
        lRelease->setObjectName(QStringLiteral("lRelease"));

        verticalLayout_11->addWidget(lRelease);

        cbRelease = new QComboBox(Integration);
        cbRelease->setObjectName(QStringLiteral("cbRelease"));

        verticalLayout_11->addWidget(cbRelease);


        horizontalLayout_2->addLayout(verticalLayout_11);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listView = new QListView(Integration);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout_2->addWidget(listView);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_4->setStretch(0, 2);
        verticalLayout_4->setStretch(1, 1);
        tabWidget->addTab(Integration, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_4 = new QHBoxLayout(tab_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        frame = new QFrame(tab_2);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        horizontalLayout_4->addWidget(frame);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        horizontalLayout->addLayout(verticalLayout);

        RemoteHiddenHelperClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RemoteHiddenHelperClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        RemoteHiddenHelperClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RemoteHiddenHelperClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RemoteHiddenHelperClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RemoteHiddenHelperClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RemoteHiddenHelperClass->setStatusBar(statusBar);

        retranslateUi(RemoteHiddenHelperClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RemoteHiddenHelperClass);
    } // setupUi

    void retranslateUi(QMainWindow *RemoteHiddenHelperClass)
    {
        RemoteHiddenHelperClass->setWindowTitle(QApplication::translate("RemoteHiddenHelperClass", "RemoteHiddenHelper", 0));
        btnFlash->setText(QApplication::translate("RemoteHiddenHelperClass", "PushButton", 0));
        groupBox->setTitle(QApplication::translate("RemoteHiddenHelperClass", "GroupBox", 0));
        cbxBootloader->setText(QApplication::translate("RemoteHiddenHelperClass", "BootLoader", 0));
        cbxAC->setText(QApplication::translate("RemoteHiddenHelperClass", "AC", 0));
        cbxGC->setText(QApplication::translate("RemoteHiddenHelperClass", "GC", 0));
        lProject->setText(QApplication::translate("RemoteHiddenHelperClass", "Project", 0));
        lSamplePhase->setText(QApplication::translate("RemoteHiddenHelperClass", "SamplePhase", 0));
        lRelease->setText(QApplication::translate("RemoteHiddenHelperClass", "Release", 0));
        tabWidget->setTabText(tabWidget->indexOf(Integration), QApplication::translate("RemoteHiddenHelperClass", "Integration Portal", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("RemoteHiddenHelperClass", "Drag and Drop", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("RemoteHiddenHelperClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class RemoteHiddenHelperClass: public Ui_RemoteHiddenHelperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTEHIDDENHELPER_H
