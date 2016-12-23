#pragma once
#include "Entity.h"

namespace RW{
	namespace SQL{

		class UserPrivate;
		class User :
			public Entity
		{
			Q_OBJECT
			//Q_PROPERTY(TypeOFElement Type READ Type WRITE SetType NOTIFY TypeChanged)
			Q_CLASSINFO("Version", "0.0.1")

		private:
			UserPrivate *d_ptr;
			Q_DECLARE_PRIVATE(User);
		public:
			User(Entity *Parent = nullptr);
			~User();

			User(const User& other);
			User& User::operator=(User& other);

			User(User&& other);
			User& User::operator=(User&& other);

			QString UserName() const;
			void SetUserName(QString UserName);

			QString Initials() const;
			void SetInitials(QString Initials);

			QString MKSUsername() const;
			void SetMKSUsername(QString Username);

			QString MKSPassword() const;
			void SetMKSPassword(QString Password);

			QString Password() const;
			void SetPassword(QString Password);

		signals:
			//void TypeChanged();
		};
	}
}