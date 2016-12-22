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

		const QString Insert_RemoteWorkstation = "INSERT INTO remoteWorkstation (elementConfiguration,user,hostname,mac, ip) VALUES (:elementConfiguration,:user,:hostname,:mac,:ip)";
		const QString Insert_User = "INSERT INTO user (elementConfiguration,user,hostname,mac, ip) VALUES (:elementConfiguration,:user,:hostname,:mac,:ip)";
		const QString Insert_ElementConfiguration = "INSERT INTO elementConfiguration (type,displayName,name,group, function) VALUES (:type,:displayName,:name,:group,:function)";
		const QString Insert_ElementType = "INSERT INTO elementType (Type) VALUES (:type)";
		const QString Insert_Instruction = "INSERT INTO instruction (step) VALUES (:step)";
		const QString Insert_Recept = "INSERT INTO recept (receptName,orderNumber,instructionID) VALUES (:receptName,:orderNumber,:instructionID)";
		const QString Insert_Product = "INSERT INTO product (productName,part,receptID) VALUES (:productName,:part,:receptID)";
		const QString Insert_LogEntry = "INSERT INTO log (date,message,loglevel,threadId,errorId,type,computerName) VALUES (:datetime,:message,:loglevel,:threadId,:errorId,:type,:computerName)";

		const QString Update_RemoteWorkstation = "UPDATE remoteWorkstation SET elementConfiguration=:elementConfiguration,user=:user,hostname=:hostname,mac=:mac,ip=:ip WHERE idRemoteWorkstation=:id";
		const QString Update_ElementConfiguration = "UPDATE elementConfiguration SET type=:type,displayName=:displayName,name=:name,group=:group,function=:function";
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
			MySqlMapper(QObject* Parent = nullptr) : DataMapper<T>(Parent)
			{
				QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
				db.setHostName("localhost");
				db.setPort(3306);
				db.setDatabaseName("remoteworkstation");
				db.setUserName("remoteUser");
				db.setPassword("schleissheimer");

				//Please see the link for QT5: http://seppemagiels.com/blog/create-mysql-driver-qt5-windows => qsqlmysql.dll and libmysql.dll
				//(and libmysql.lib, if your installation of MySQL has it) are needed
				db.open();

			}
			~MySqlMapper(){}

			bool Insert(const T &Data){ return false; }
			bool Update(const T &Data){ return false; }

			T&& FindByID(const quint64 id){ return nullptr; }
			QList<T>&& FindAll(){ QList<T> m;return std::move(m);}

			template<class Y> Y&& FindByID(quint64 ID, bool Flag);
			


			//bool Insert(const Entity &Data);
			//bool Update(const Entity &Data);
			//Entity&& FindByID(const quint64 id);
			//QList<Entity>&& FindAll();
		};


		template <class T> template<class Y> Y&& MySqlMapper<T>::FindByID(quint64 ID, bool Flag)
		{
			this->FindByID<Y>(ID);
		}

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
			query.bindValue(":group", d.Group());
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
				m_logger->error("Tbl instruction insert failed. Error: {}" ,query.lastError().text().toStdString().c_str());
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
			QString m_Group;
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
			query.bindValue(":group", d.Group());
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

		template<> RemoteWorkstation&& MySqlMapper<RemoteWorkstation>::FindByID(const quint64 ID)
		{
			RemoteWorkstation d;
			QSqlQuery query;
			query.prepare(SelectById_RemoteWorkstation);
			query.bindValue(":idRemoteWorkstation", ID);
			bool res = query.exec();
			while (query.next())
			{
				d.SetElementCfg(FindByID<ElementConfiguration>(ID, true));
				d.SetCurrentUser(FindByID<User>(ID, true));
				d.SetIp(query.value("ip").toString());
				d.SetMac(query.value("mac").toString());
				d.SetHostname(query.value("hostname").toString());
			}

			if (!res)
			{
				m_logger->error("Tbl instruction update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return std::move(d);
		}


		template<> ElementConfiguration&& MySqlMapper<ElementConfiguration>::FindByID(const quint64 ID)
		{
			ElementConfiguration d;
			QSqlQuery query;
			query.prepare(SelectById_ElementConfiguration);
			query.bindValue(":idElementConfiguration", ID);
			bool res = query.exec();
			while (query.next())
			{
				d.SetType(FindByID<ElementType>(ID, true));
				d.SetDisplayName(query.value("displayName").toString());
				d.SetName(query.value("name").toString());
				d.SetGroup(query.value("group").toString());
				d.SetFunction(query.value("group").toString());
			}

			if (!res)
			{
				m_logger->error("Tbl instruction update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return std::move(d);
		}

		template<> ElementType&& MySqlMapper<ElementType>::FindByID(const quint64 ID)
		{
			ElementType d;
			QSqlQuery query;
			query.prepare(SelectById_ElememtType);
			query.bindValue(":idElementType", ID);
			bool res = query.exec();
			while (query.next())
			{
				// \!todo unschöne Konvertierung
				d.SetType((TypeOfElement) query.value("type").toInt());
			}

			if (!res)
			{
				m_logger->error("Tbl instruction update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return std::move(d);
		}


		template<> Instruction&& MySqlMapper<Instruction>::FindByID(const quint64 ID)
		{
			Instruction d;
			QSqlQuery query;
			query.prepare(SelectById_ElememtType);
			query.bindValue(":idElementType", ID);
			bool res = query.exec();

			while (query.next())
			{
				// \!todo unschöne Konvertierung
				d.SetStep(query.value("step").toString());
			}

			if (!res)
			{
				m_logger->error("Tbl instruction update failed. Error:{}", query.lastError().text().toStdString().c_str());
			}
			return std::move(d);
		}

	}
}