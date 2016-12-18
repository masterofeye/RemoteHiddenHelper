#pragma once
#include "qobject.h"

QT_BEGIN_NAMESPACE
class QSqlDatabase;
QT_END_NAMESPACE

class SQLConstructor :
	public QObject
{
public:
	SQLConstructor();
	~SQLConstructor();

	bool MySQLInitialization();

private:
	void CreateInstructionTbl();
	void CreateProductTbl();
	void CreateReceptTbl();

	void InsertInstructionTblTestData();
	void InsertProductTblTestData();
	void InsertReceptTblTestData();

	void DropAllTables();
	void DropProductTbl();
	void DropReceptTbl();
	void DropInstructionTbl();

};

