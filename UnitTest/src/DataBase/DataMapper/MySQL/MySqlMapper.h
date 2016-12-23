#pragma once
#include "DataMapper.h"
#include "RemoteWorkstation.h"
#include "ElementConfiguration.h"
#include "ElementType.h"
#include "User.h"
#include "Recept.h"
#include "Product.h"
#include "Instruction.h"
#include "LogEntry.h"
#include "qsqlquery.h"
#include "qvariant.h"
#include "qdatetime.h"
#include "qdebug.h"
#include "qsqlerror.h"
#include "spdlog/spdlog.h"


namespace RW{
	namespace SQL{

		const QString Insert_RemoteWorkstation = "INSERT INTO remoteWorkstation (elementConfigurationID,userID,hostname,mac, ip) VALUES (:elementConfiguration,:user,:hostname,:mac,:ip)";
		const QString Insert_User = "INSERT INTO user (elementConfiguration,user,hostname,mac, ip) VALUES (:elementConfiguration,:user,:hostname,:mac,:ip)";
		const QString Insert_ElementConfiguration = "INSERT INTO elementConfiguration (typeID,displayName,name,groupName, function) VALUES (:type,:displayName,:name,:groupName,:function)";
		const QString Insert_ElementType = "INSERT INTO elementType (type) VALUES (:type)";
		const QString Insert_Instruction = "INSERT INTO instruction (step) VALUES (:step)";
		const QString Insert_Recept = "INSERT INTO recept (receptName,orderNumber,instructionID) VALUES (:receptName,:orderNumber,:instructionID)";
		const QString Insert_Product = "INSERT INTO product (productName,part,receptID) VALUES (:productName,:part,:receptID)";
		const QString Insert_LogEntry = "INSERT INTO log (date,message,loglevel,threadId,errorId,type,computerName) VALUES (:datetime,:message,:loglevel,:threadId,:errorId,:type,:computerName)";

		const QString Update_RemoteWorkstation = "UPDATE remoteWorkstation SET elementConfiguration=:elementConfiguration,user=:user,hostname=:hostname,mac=:mac,ip=:ip WHERE idRemoteWorkstation=:id";
		const QString Update_ElementConfiguration = "UPDATE elementConfiguration SET type=:type,displayName=:displayName,name=:name,groupName=:groupName,function=:function";
		const QString Update_ElementType = "UPDATE elementType SET type=:type";
		const QString Update_Instruction = "UPDATE instruction SET step=:step";
		const QString Update_Recept = "UPDATE recept SET receptName=:receptName,orderNumber=:orderNumber,instructionID=:instructionID";
		const QString Update_Product = "UPDATE product SET productName=:productName,part=:part,receptID=:receptID";
		const QString Update_LogEntry = "UPDATE log SET datetime=:datetime,message=:message,loglevel=:loglevel,threadId=:threadId,errorId=:errorId,type=:type,computerName=:computerName";

		const QString Delete_RemoteWorkstattion = "DELETE FROM remoteWorkstation WHERE idRemoteWorkstation=:idRemoteWorkstation";
		const QString Delete_ElementConfiguration = "DELETE FROM elementConfiguration WHERE idElementConfiguration=:idElementConfiguration";
		const QString Delete_ElementType = "DELETE FROM elementType WHERE idElementType=:idElementType";
		const QString Delete_Instruction = "DELETE FROM instruction WHERE idIntruction=:idIntruction";
		const QString Delete_Recept = "DELETE FROM recept WHERE idRecept=:idRecept";
		const QString Delete_Product = "DELETE FROM product WHERE idProduct=:idProduct";
		const QString Delele_LogEntry = "DELETE FROM log WHERE idLogEntry=:idLogEntry";

		const QString SelectById_RemoteWorkstation = "SELECT * FROM remoteWorkstation WHERE idRemoteWorkstation = :idRemoteWorkstation";
		const QString SelectById_ElementConfiguration = "SELECT * FROM elementConfiguration WHERE idElementConfiguration = :idElementConfiguration";
		const QString SelectById_ElememtType = "SELECT * FROM elememtType WHERE idElememtType = :idElememtType";
		const QString SelectById_Instruction = "SELECT * FROM Instruction WHERE idInstruction = :idInstruction";
		const QString SelectById_Recept = "SELECT * FROM recept WHERE idRecept = :idRecept";
		const QString SelectById_Product = "SELECT * FROM product WHERE idProduct = :idProduct";
		const QString SelectById_LogEntry = "SELECT * FROM log WHERE idLogEntry=:idLogEntry";

		const QString SelectAll_RemoteWorkstation = "SELECT * FROM remoteWorkstation";
		const QString SelectAll_ElementConfiguration = "SELECT * FROM elementConfiguration";
		const QString SelectAll_ElememtType = "SELECT * FROM elememtType";
		const QString SelectAll_Instruction = "SELECT * FROM Instructio";
		const QString SelectAll_Recept = "SELECT * FROM recept";
		const QString SelectAll_Product = "SELECT * FROM product";
		const QString SelectAll_LogEntry = "SELECT * FROM log";


		class Entity;
		template<class T>
		class MySqlMapper :
			public DataMapper<T>
		{
		private:
			std::shared_ptr<spdlog::logger> m_logger;

		public:
			MySqlMapper(QObject* Parent = nullptr) : DataMapper<T>(Parent),
				m_logger(spdlog::get("file_logger"))
			{

				QSqlDatabase db = QSqlDatabase::database();
				if (!db.isOpen())
				{

					db = QSqlDatabase::addDatabase("QMYSQL");
					db.setHostName("localhost");
					db.setPort(3306);
					db.setDatabaseName("remoteworkstation");
					db.setUserName("remoteUser");
					db.setPassword("schleissheimer");

					//Please see the link for QT5: http://seppemagiels.com/blog/create-mysql-driver-qt5-windows => qsqlmysql.dll and libmysql.dll
					//(and libmysql.lib, if your installation of MySQL has it) are needed
					db.open();
				}

			}
			~MySqlMapper(){}

			bool Insert(const T &Data){ return false; }
			bool Update(const T &Data){ return false; }

			T FindByID(const quint64 id, bool Flag){ return T(); }
			template<class Y> Y FindByID(const quint64 ID){
				MySqlMapper<Y> temp;
				return temp.FindByID(ID, true);
			}
			QList<T> FindAll(){ QList<T> m; return std::move(m); }

		};




		template<> bool MySqlMapper<LogEntry>::Insert(const LogEntry &Data)
		{
			LogEntry d(Data);

			QSqlQuery query;
			query.prepare(Insert_LogEntry);
			query.bindValue(":datetime", d.Date());
			query.bindValue(":message", d.Message());
			query.bindValue(":loglevel", d.LogLevel());
			query.bindValue(":threadId", d.ThreadID());
			query.bindValue(":errorId", d.ErrorID());
			query.bindValue(":type", d.Type());
			query.bindValue(":computerName", d.ComputerName());

			bool res = query.exec();
			if (!res)
			{
				qDebug() << query.lastError().text();
			}
			return res;
		}


		template<> bool MySqlMapper<RemoteWorkstation>::Insert(const RemoteWorkstation &Data)
		{
			RemoteWorkstation d(Data);

			QSqlQuery query;
			query.prepare(Insert_RemoteWorkstation);
			query.bindValue(":elementConfiguration", d.ElementCfg().ID());
			query.bindValue(":user", d.CurrentUser().ID());
			query.bindValue(":hostname", d.Hostname());
			query.bindValue(":mac", d.Mac());
			query.bindValue(":ip", d.Ip());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl remoteWorkstation insert failed. Error: {}", query.lastError().text().toStdString());
			}
			return res;
		}

		template<> bool MySqlMapper<ElementConfiguration>::Insert(const ElementConfiguration &Data)
		{
			ElementConfiguration d(Data);

			QSqlQuery query;
			query.prepare(Insert_ElementConfiguration);
			query.bindValue(":type", d.Type().ID());
			query.bindValue(":displayName", d.DisplayName());
			query.bindValue(":name", d.Name());
			query.bindValue(":groupName", d.GroupName());
			query.bindValue(":function", d.Function());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl elementConfiguration insert failed. Error: {}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<ElementType>::Insert(const ElementType &Data)
		{
			ElementType d = Data;

			QSqlQuery query;
			query.prepare(Insert_ElementType);
			query.bindValue(":type", (int)d.Type());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl elementType insert failed. Error: {}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<User>::Insert(const User &Data)
		{
			User d = Data;

			QSqlQuery query;
			query.prepare(Insert_User);

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl user insert failed. Error: {}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<Instruction>::Insert(const Instruction &Data)
		{
			Instruction d = Data;

			QSqlQuery query;
			query.prepare(Insert_Instruction);
			query.bindValue(":step", d.Step());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl instruction insert failed. Error: {}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<Recept>::Insert(const Recept &Data)
		{
			Recept d = Data;

			QSqlQuery query;
			query.prepare(Insert_Recept);
			query.bindValue(":receptName", d.ReceptName());
			query.bindValue(":orderNumber", d.OrderNumber());
			query.bindValue(":instructionID", d.Instruction().ID());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl recept insert failed. Error: ") << query.lastError().text().toStdString().c_str();
			}
			return res;
		}

		template<> bool MySqlMapper<Product>::Insert(const Product &Data)
		{
			Product d = Data;

			QSqlQuery query;
			query.prepare(Insert_Product);
			query.bindValue(":productName", d.ProductName());
			query.bindValue(":part", d.Part());
			query.bindValue(":receptID", d.Recept().ID());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl product insert failed. Error: {}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<RemoteWorkstation>::Update(const RemoteWorkstation &Data)
		{
			RemoteWorkstation d = Data;
			QSqlQuery query;
			query.prepare(Update_RemoteWorkstation);
			query.bindValue(":elementConfiguration", d.ElementCfg().ID());
			query.bindValue(":user", d.CurrentUser().ID());
			query.bindValue(":hostname", d.Hostname());
			query.bindValue(":mac", d.Mac());
			query.bindValue(":ip", d.Ip());

			ElementType m_Type;
			QString m_DisplayName;
			QString m_Name;
			QString m_groupName;
			QString m_Function;

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl remoteWorkstation update failed. Error: {}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<ElementConfiguration>::Update(const ElementConfiguration &Data)
		{
			ElementConfiguration d = Data;
			QSqlQuery query;
			query.prepare(Update_ElementConfiguration);
			query.bindValue(":type", d.Type().ID());
			query.bindValue(":displayName", d.DisplayName());
			query.bindValue(":name", d.Name());
			query.bindValue(":groupName", d.GroupName());
			query.bindValue(":function", d.Function());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl elementConfiguration update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<ElementType>::Update(const ElementType &Data)
		{
			ElementType d = Data;
			QSqlQuery query;
			query.prepare(Update_ElementType);
			query.bindValue(":type", (int)d.Type());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl elementType update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<Instruction>::Update(const Instruction &Data)
		{
			Instruction d = Data;
			QSqlQuery query;
			query.prepare(Update_ElementType);
			query.bindValue(":step", d.Step());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl instruction update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<Product>::Update(const Product &Data)
		{
			Product d = Data;
			QSqlQuery query;
			query.prepare(Update_ElementType);
			query.bindValue(":receptID", d.Recept().ID());
			query.bindValue(":productName", d.ProductName());
			query.bindValue(":part", d.Part());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl instruction update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> bool MySqlMapper<Recept>::Update(const Recept &Data)
		{
			Recept d = Data;
			QSqlQuery query;
			query.prepare(Update_ElementType);
			query.bindValue(":orderNumber", d.OrderNumber());
			query.bindValue(":receptName", d.ReceptName());
			query.bindValue(":instructionID", d.Instruction().ID());

			bool res = query.exec();
			if (!res)
			{
				m_logger->error("Tbl instruction update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return res;
		}

		template<> RemoteWorkstation MySqlMapper<RemoteWorkstation>::FindByID(const quint64 ID, bool Flag)
		{
			RemoteWorkstation d;
			QSqlQuery query;
			query.prepare(SelectById_RemoteWorkstation);
			query.bindValue(":idRemoteWorkstation", ID);
			bool res = query.exec();
			while (query.next())
			{
				d.SetElementCfg(FindByID<ElementConfiguration>(query.value("elementConfigurationID").toInt()));
				d.SetCurrentUser(FindByID<User>(query.value("userID").toInt()));
				d.SetIp(query.value("ip").toString());
				d.SetMac(query.value("mac").toString());
				d.SetHostname(query.value("hostname").toString());
			}

			if (!res)
			{
				m_logger->error("Tbl remoteWorkstation FindByID failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return d;
		}


		template<> ElementConfiguration MySqlMapper<ElementConfiguration>::FindByID(const quint64 ID, bool Flag)
		{
			ElementConfiguration d = ElementConfiguration();
			QSqlQuery query;
			query.prepare(SelectById_ElementConfiguration);
			query.bindValue(":idElementConfiguration", ID);
			bool res = query.exec();
			while (query.next())
			{
				d.SetType(FindByID<ElementType>(query.value("elementTypeID").toInt()));
				d.SetDisplayName(query.value("displayName").toString());
				d.SetName(query.value("name").toString());
				d.SetGroupName(query.value("groupName").toString());
				d.SetFunction(query.value("groupName").toString());
			}

			if (!res)
			{
				m_logger->error("Tbl elementConfiguration FindByID failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return d;
		}

		template<> ElementType MySqlMapper<ElementType>::FindByID(const quint64 ID, bool Flag)
		{
			ElementType d;
			QSqlQuery query;
			query.prepare(SelectById_ElememtType);
			query.bindValue(":idElementType", ID);
			bool res = query.exec();
			while (query.next())
			{
				// \!todo unschöne Konvertierung
				d.SetType((TypeOfElement)query.value("type").toInt());
			}

			if (!res)
			{
				m_logger->error("Tbl elementType FindByID failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return d;
		}


		template<> Instruction MySqlMapper<Instruction>::FindByID(const quint64 ID, bool Flag)
		{
			Instruction d;
			QSqlQuery query;
			query.prepare(SelectById_Instruction);
			query.bindValue(":idInstruction", ID);
			bool res = query.exec();

			while (query.next())
			{
				// \!todo unschöne Konvertierung
				d.SetStep(query.value("step").toString());
			}

			if (!res)
			{
				m_logger->error("Tbl instruction FindByID failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return d;
		}

		template<> Recept MySqlMapper<Recept>::FindByID(const quint64 ID, bool Flag)
		{
			Recept d;
			QSqlQuery query;
			query.prepare(SelectById_Recept);
			query.bindValue(":idRecept", ID);
			bool res = query.exec();

			while (query.next())
			{
				// \!todo unschöne Konvertierung
				d.SetOrderNumber(query.value("orderNumber").toInt());
				d.SetInstruction(FindByID<Instruction>(query.value("instructionID").toInt()));
				d.SetReceptName(query.value("receptName").toString());
			}

			if (!res)
			{
				m_logger->error("Tbl recept FindByID failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return d;
		}

		template<> Product MySqlMapper<Product>::FindByID(const quint64 ID, bool Flag)
		{
			Product d;
			QSqlQuery query;
			query.prepare(SelectById_Product);
			query.bindValue(":idProduct", ID);
			bool res = query.exec();

			while (query.next())
			{
				// \!todo unschöne Konvertierung
				d.SetProductName(query.value("productName").toString());
				d.SetRecept(FindByID<Recept>(query.value("receptID").toInt()));
				d.SetPart(query.value("part").toString());
			}

			if (!res)
			{
				m_logger->error("Tbl product FindByID failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return d;
		}

		template<> LogEntry MySqlMapper<LogEntry>::FindByID(const quint64 ID, bool Flag)
		{
			LogEntry d;
			QSqlQuery query;
			query.prepare(SelectById_LogEntry);
			query.bindValue(":idLogEntry", ID);
			bool res = query.exec();

			while (query.next())
			{
				// \!todo unschöne Konvertierung
				d.SetComputerName_(query.value("setComputerName").toString());
				d.SetType(query.value("type").toString());
				d.SetDate(query.value("date").toDateTime());
				d.SetThreadID(query.value("threadId").toInt());
				d.SetMessage(query.value("message").toString());
				d.SetLogLevel(query.value("logLevel").toString());
				d.SetErrorID(query.value("threadId").toInt());
			}

			if (!res)
			{
				m_logger->error("Tbl log FindByID failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return d;
		}

		template<> QList<RemoteWorkstation> MySqlMapper<RemoteWorkstation>::FindAll()
		{
			QList<RemoteWorkstation> list;
			QSqlQuery query;
			query.prepare(SelectAll_RemoteWorkstation);
			bool res = query.exec();
			while (query.next())
			{
				RemoteWorkstation d;
				d.SetElementCfg(FindByID<ElementConfiguration>(query.value("elementConfigurationID").toInt()));
				d.SetCurrentUser(FindByID<User>(query.value("userID").toInt()));
				d.SetIp(query.value("ip").toString());
				d.SetMac(query.value("mac").toString());
				d.SetHostname(query.value("hostname").toString());
				list << d;
			}

			if (!res)
			{
				m_logger->error("Tbl remoteWorkstation FindByID failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return list;
		}

		template<> QList<ElementConfiguration> MySqlMapper<ElementConfiguration>::FindAll()
		{
			QList<ElementConfiguration> list;
			QSqlQuery query;
			query.prepare(SelectAll_ElementConfiguration);
			bool res = query.exec();
			while (query.next())
			{
				ElementConfiguration d;
				d.SetType(FindByID<ElementType>(query.value("elementTypeID").toInt()));
				d.SetDisplayName(query.value("displayName").toString());
				d.SetName(query.value("name").toString());
				d.SetGroupName(query.value("groupName").toString());
				d.SetFunction(query.value("groupName").toString());
				list << d;
			}

			if (!res)
			{
				m_logger->error("Tbl elementConfiguration FindAll failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return list;
		}

		template<> QList<ElementType> MySqlMapper<ElementType>::FindAll()
		{
			QList<ElementType> list;
			QSqlQuery query;
			query.prepare(SelectAll_ElememtType);
			bool res = query.exec();
			while (query.next())
			{
				ElementType d;
				// \!todo unschöne Konvertierung
				d.SetType((TypeOfElement)query.value("type").toInt());
				list << d;
			}

			if (!res)
			{
				m_logger->error("Tbl elementType FindAll failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return list;
		}


		template<> QList<Instruction> MySqlMapper<Instruction>::FindAll()
		{
			QList<Instruction> list;
			QSqlQuery query;
			query.prepare(SelectAll_Instruction);
			bool res = query.exec();
			while (query.next())
			{
				Instruction d;
				// \!todo unschöne Konvertierung
				d.SetStep(query.value("step").toString());
				list << d;
			}

			if (!res)
			{
				m_logger->error("Tbl instruction FindAll failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return list;
		}
	
		template<> QList<Recept> MySqlMapper<Recept>::FindAll()
		{
			QList<Recept> list;
			QSqlQuery query;
			query.prepare(SelectAll_Recept);
			bool res = query.exec();
			while (query.next())
			{
				Recept d;
				// \!todo unschöne Konvertierung
				d.SetOrderNumber(query.value("orderNumber").toInt());
				d.SetInstruction(FindByID<Instruction>(query.value("instructionID").toInt()));
				d.SetReceptName(query.value("receptName").toString());
				list << d;
			}

			if (!res)
			{
				m_logger->error("Tbl recept FindAll failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return list;
		}

		template<> QList<Product> MySqlMapper<Product>::FindAll()
		{
			QList<Product> list;
			QSqlQuery query;
			query.prepare(SelectAll_Product);
			bool res = query.exec();
			while (query.next())
			{
				Product d;
				// \!todo unschöne Konvertierung
				d.SetProductName(query.value("productName").toString());
				d.SetRecept(FindByID<Recept>(query.value("receptID").toInt()));
				d.SetPart(query.value("part").toString());
				list << d;
			}

			if (!res)
			{
				m_logger->error("Tbl product FindAll failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return list;
		}


		template<> QList<LogEntry> MySqlMapper<LogEntry>::FindAll()
		{
			QList<LogEntry> list;
			QSqlQuery query;
			query.prepare(SelectAll_LogEntry);
			bool res = query.exec();
			while (query.next())
			{
				LogEntry d;
				// \!todo unschöne Konvertierung
				d.SetComputerName_(query.value("setComputerName").toString());
				d.SetType(query.value("type").toString());
				d.SetDate(query.value("date").toDateTime());
				d.SetThreadID(query.value("threadId").toInt());
				d.SetMessage(query.value("message").toString());
				d.SetLogLevel(query.value("logLevel").toString());
				d.SetErrorID(query.value("threadId").toInt());
				list << d;
			}

			if (!res)
			{
				m_logger->error("Tbl logEntry FindAll failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return list;
		}
	}
}