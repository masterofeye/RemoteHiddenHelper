#include "User.h"
#include "User_p.h"

namespace RW{
	namespace SQL{

		UserPrivate::UserPrivate(User* Parent) : 
			QObject(Parent),
			q_ptr(Parent)
		{
		
		}

		UserPrivate::~UserPrivate()
		{}

		User::User(Entity *Parent) : Entity(Parent),
		d_ptr(new UserPrivate(this))
		{
		}


		User::~User()
		{
			delete d_ptr;
		}
	}
}