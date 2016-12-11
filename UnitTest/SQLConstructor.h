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
	void CreateInstructionTbl(QSqlDatabase& db);
	void CreateProductTbl();
	void CreateReceptTbl();

	void InsertInstructionTblTestData();
	void InsertProductTblTestData();
	void InsertReceptTblTestData();

};

