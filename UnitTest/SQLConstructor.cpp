#include "SQLConstructor.h"
#include <QtSql>
#include <qdebug.h>
#include "Constans.h"


SQLConstructor::SQLConstructor()
{
}


SQLConstructor::~SQLConstructor()
{
}

bool SQLConstructor::MySQLInitialization()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setPort(3306);
	db.setDatabaseName("remoteworkstation");
	db.setUserName("remoteUser");
	db.setPassword("schleissheimer");


	//Please see the link for QT5: http://seppemagiels.com/blog/create-mysql-driver-qt5-windows => qsqlmysql.dll and libmysql.dll
	//(and libmysql.lib, if your installation of MySQL has it) are needed
	QSqlError error = db.lastError();
	if (!db.open())
		return false;

	CreateInstructionTbl(db);
	CreateProductTbl();
	CreateReceptTbl();

	db.close();
	return true;
}


void SQLConstructor::CreateInstructionTbl(QSqlDatabase &db)
{

	QSqlQuery query(db);
	const QString cmd = "CREATE TABLE IF NOT EXISTS instruction (idInstruction INTEGER UNIQUE PRIMARY KEY, step VARCHAR(255))";
	bool res = query.prepare(cmd);
	if (res)
	{
		if (query.exec())
		{
			qDebug() << "InstructionTbl created succesfully";
		}
		else
		{
			qDebug() << "Error " << "MySQl  Error " << query.lastError().text();
		}
	}
	query.finish();
}

void SQLConstructor::CreateReceptTbl()
{

	QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery query(db);
	bool res = query.prepare("CREATE TABLE IF NOT EXISTS recept (idRecept INTEGER UNIQUE PRIMARY KEY, orderNumber SMALLINT UNSIGNED, receptName VARCHAR(255), ingredientID INT, FOREIGN KEY (ingredientID) REFERENCES instruction(ingredientID))");
	if (res)
	{
		if (query.exec())
		{
			qDebug() << "InstructionTbl created succesfully";
		}
		else
		{
			qDebug() << "Error " << "MySQl Error " << query.lastError().text();
		}
	}
}

void SQLConstructor::CreateProductTbl()
{
	QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery query(db);
	bool res = query.prepare("CREATE TABLE IF NOT EXISTS production (idProduction INTEGER UNIQUE PRIMARY KEY, productName VARCHAR(255), part VARCHAR(255), receptID INT, FOREIGN KEY (receptID) REFERENCES recept(receptID))");
	if (res)
	{
		if (query.exec())
		{
			qDebug() << "InstructionTbl created succesfully";
		}
		else
		{
			qDebug() << "Error " << "MySQl Error " << query.lastError().text();
		}
	}
}

void SQLConstructor::InsertInstructionTblTestData()
{
	QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery query(db);
	
	const QMetaObject &mo = RW::CORE::Util::staticMetaObject;
	int index = mo.indexOfEnumerator("Functions");
	QMetaEnum metaEnum = mo.enumerator(index);

	query.prepare("INSERT INTO instruction (step) VALUES(:step)");
	for (int i = 0; i < metaEnum.keyCount(); i++)
	{
		const char* s = metaEnum.key(i); // enum name as string
		query.bindValue(":step", s);
		if(query.exec())
		{
			qDebug() << "InstructionTbl created succesfully";
		}
		else
		{
			qDebug() << "Error " << "MySQl Error " << query.lastError().text();
		}
	}
}

#define BOOTLOADER "Bootloader"
#define GC "GC"
#define AC "AC"

#define FHOST_BOOTLOADER "FHOST_BOOTLOADER"
#define FHOST_AC "FHOST_AC"
#define FHOST_EL_GC "FHOST_EL_GC"
#define USB "USB_HL"

void SQLConstructor::InsertProductTblTestData()
{
	QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery query(db);

	QMap<QString,QPair<QString,QString>> projectNameList;
	projectNameList.insertMulti("BR213IC-GC-HL_MY16", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR213IC-GC-HL_MY16", QPair<QString, QString>(GC, USB));
	projectNameList.insertMulti("BR213IC-GC-HL_MY17", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR213IC-GC-HL_MY17", QPair<QString, QString>(GC, USB));
	projectNameList.insertMulti("BR213IC-GC-HLVAR205_MY18", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR213IC-GC-HLVAR205_MY18", QPair<QString, QString>(GC, USB));
	projectNameList.insertMulti("BR213IC-GC-HLVAR213_MY18", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR213IC-GC-HLVAR213_MY18", QPair<QString, QString>(GC, USB));
	projectNameList.insertMulti("BR463IC-GC-HL", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR463IC-GC-HL", QPair<QString, QString>(GC, USB));
	projectNameList.insertMulti("BR463IC-GC-EL", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR463IC-GC-EL", QPair<QString, QString>(GC, FHOST_EL_GC));
	projectNameList.insertMulti("BR213IC-GC-EL_MY16", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR213IC-GC-EL_MY16", QPair<QString, QString>(GC, FHOST_EL_GC));
	projectNameList.insertMulti("BR213IC-GC-EL_MY17", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR213IC-GC-EL_MY17", QPair<QString, QString>(GC, FHOST_EL_GC));
	projectNameList.insertMulti("BR213IC-GC-EL_MY18", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR213IC-GC-EL_MY18", QPair<QString, QString>(GC, FHOST_EL_GC));
	projectNameList.insertMulti("BR213IC-GC-EL205MY18", QPair<QString, QString>(BOOTLOADER, FHOST_BOOTLOADER));
	projectNameList.insertMulti("BR213IC-GC-EL205MY18", QPair<QString, QString>(GC, FHOST_EL_GC));
	projectNameList.insertMulti("BR213IC-AC-HL_MY16", QPair<QString, QString>(AC, FHOST_AC));
	projectNameList.insertMulti("BR213IC-AC-HL_MY17", QPair<QString, QString>(AC, FHOST_AC));
	projectNameList.insertMulti("BR213IC-AC-EL_MY16", QPair<QString, QString>(AC, FHOST_AC));
	projectNameList.insertMulti("BR213IC-AC-EL_MY17", QPair<QString, QString>(AC, FHOST_AC));


	query.prepare("INSERT INTO product (productName, part, receptName) VALUES(?, ?, ?)");
	QMap<QString, QPair<QString, QString>>::const_iterator i = projectNameList.constBegin();
	while (i != projectNameList.constEnd()) {
		 
		QList<QPair<QString, QString>> values = projectNameList.values(i.key());
		for each (auto var in values)
		{
			QVariantList values;
			values << i.key() << var.first << var.second;
			query.execBatch(QSqlQuery::BatchExecutionMode::ValuesAsColumns);
		}
	}
}

void SQLConstructor::InsertReceptTblTestData()
{
	QSqlDatabase db = QSqlDatabase::database();
	QSqlQuery query(db);
	quint8 i = 0;
	QMap < QString, QPair<QString, quint8>> receptList;
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSLogin).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSCreateSandBox).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSClose).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStartApplication).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyLoadWorkspace).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::ToggleCl30Slow).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStartSimulation).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPStartFHost).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPLoadFlashFile).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPStartFlash).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPGetState).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPAbortSequence).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPCloseSequence).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPCloseFHost).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStopSimulation).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyCloseApplication).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::ToggleCl30Fast).toString(), i++));
	receptList.insertMulti(FHOST_BOOTLOADER, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::PortalInfoCloseDialog).toString(), i++));

	i = 0;
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSLogin).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSCreateSandBox).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSClose).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStartApplication).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyLoadWorkspace).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::ToggleCl30Slow).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStartSimulation).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPStartFHost).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPLoadFlashFile).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPStartFlash).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPGetState).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPAbortSequence).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPCloseSequence).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPCloseFHost).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStopSimulation).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyCloseApplication).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::ToggleCl30Fast).toString(), i++));
	receptList.insertMulti(FHOST_AC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::PortalInfoCloseDialog).toString(), i++));

	i = 0;
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSLogin).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSCreateSandBox).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSClose).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStartApplication).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyLoadWorkspace).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::ToggleCl30Slow).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::SwitchToFlash).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStartSimulation).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FileUtilUnZip).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::UsbHidLoaderFlashFile).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FileUtilDelete).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStopSimulation).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyCloseApplication).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::ToggleCl30Fast).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::SwitchToDebug).toString(), i++));
	receptList.insertMulti(USB, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::PortalInfoCloseDialog).toString(), i++));

	i = 0;
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSLogin).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSCreateSandBox).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::MKSClose).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStartApplication).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyLoadWorkspace).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::ToggleCl30Slow).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStartSimulation).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPStartFHost).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPLoadFlashFile).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPStartFlash).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPGetState).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPAbortSequence).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPCloseSequence).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::FHostSPCloseFHost).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyStopSimulation).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::CanEasyCloseApplication).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::ToggleCl30Fast).toString(), i++));
	receptList.insertMulti(FHOST_EL_GC, QPair<QString, int>(QVariant::fromValue(RW::CORE::Util::Functions::PortalInfoCloseDialog).toString(), i++));


	query.prepare("INSERT INTO recept (order, instructionID, receptName) VALUES(?, (SELECT idInstruction from instruction WHERE step = ?) , ?)");
	
	QMap<QString, QPair<QString,quint8>>::const_iterator ii = receptList.constBegin();
	while (ii != receptList.constEnd()) {

		QList<QPair<QString, quint8>> values = receptList.values(ii.key());
		for each (auto var in values)
		{
			QVariantList values;
			values << ii.key() << var.first << var.second;
			query.execBatch(QSqlQuery::BatchExecutionMode::ValuesAsColumns);
		}
	}
}