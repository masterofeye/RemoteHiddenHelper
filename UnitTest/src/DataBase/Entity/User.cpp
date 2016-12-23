#include "User.h"
#include "User_p.h"

#include "qdebug.h"
namespace RW{
	namespace SQL{

		UserPrivate::UserPrivate(User* Parent) : 
			//QObject(Parent),
			q_ptr(Parent)
		{
		}

		UserPrivate::~UserPrivate()
		{
		}


		User::User(const User& other)
		{
		}
		User& User::operator=(User& other)
		{
			return *this;
		}


		User::User(User&& other)
		{
		}

		User& User::operator=(User&& other)
		{
			return *this;
		}

		User::User(Entity *Parent) : Entity(Parent),
		d_ptr(new UserPrivate(this))
		{
		}


		User::~User()
		{
		}


		QString User::UserName() const
		{
			Q_D(const User);
			return d->m_UserName;
		}

		void User::SetUserName(QString Username)
		{
			Q_D(User);
			d->m_UserName = Username;
		}

		QString User::Initials() const
		{
			Q_D(const User);
			return d->m_Initials;
		}

		void User::SetInitials(QString Initials)
		{
			Q_D(User);
			d->m_Initials = Initials;
		}

		QString User::MKSUsername() const
		{
			Q_D(const User);
			return d->m_MKSUsername;
		}


		void User::SetMKSUsername(QString Username)
		{
			Q_D(User);
			d->m_MKSUsername = Username;
		}

		QString User::MKSPassword() const
		{
			Q_D(const User);
			return d->m_MKSPassword;
		}

		void User::SetMKSPassword(QString Password)
		{
			Q_D(User);
			d->m_MKSPassword = Password;
		}

		QString User::Password() const
		{
			Q_D(const User);
			return d->m_Password;
		}

		void User::SetPassword(QString Password)
		{
			Q_D(User);
			d->m_Password = Password;
		}
	}
}