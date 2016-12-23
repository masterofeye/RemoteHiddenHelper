#include "User.h"
#include "User_p.h"

#include "qdebug.h"
namespace RW{
	namespace SQL{

		UserPrivate::UserPrivate(User* Parent) : 
			//QObject(Parent),
			q_ptr(Parent)
		{
			qDebug() << "ctor UserPrivate";
		}

		UserPrivate::~UserPrivate()
		{
			qDebug() << "~ctor UserPrivate";
		}


		User::User(const User& other)
		{
			qDebug() << "copy User";
		}
		User& User::operator=(User& other)
		{
			qDebug() << "copy operator User";
			return *this;
		}


		User::User(User&& other)
		{
			qDebug() << "move User";
		}

		User& User::operator=(User&& other)
		{
			qDebug() << "move operator User";
			return *this;
		}

		User::User(Entity *Parent) : Entity(Parent),
		d_ptr(new UserPrivate(this))
		{
			qDebug() << "ctor User";
		}


		User::~User()
		{
			qDebug() << "~ctor User";
		}
	}
}