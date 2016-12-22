#pragma once
#include <qobject.h>

namespace RW{
	namespace SQL{

		class User;
		class UserPrivate: public QObject
		{
			Q_OBJECT
				Q_DISABLE_COPY(UserPrivate)
				Q_DECLARE_PUBLIC(User)
		private:
			User * const q_ptr;
		public:
			UserPrivate(User *Parent);
			~UserPrivate();
		};
	}
}