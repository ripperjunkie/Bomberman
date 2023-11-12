#pragma once

#include "Engine/Public/Utils.h"
#include "Engine/GameFramework/Actor.h"
#include <type_traits>



#define ACTOR_MANAGER ActorManager::GetInstance()


class Actor;

class ActorManager
{
public:
	static ActorManager* GetInstance()
	{
		if (!mInstance)
		{
			mInstance = new ActorManager();
		}
		return mInstance;
	}


	/* Spawn actor and its derived classes and call their start method */
	template<std::derived_from<Actor> T, typename... Args>
	std::shared_ptr<T> SpawnActor(Args... arguments)
	{
		std::shared_ptr<T> newObject = std::make_shared<T>(arguments...);
		mActors.push_back(newObject);

		if (newObject)
		{
			newObject->Start();		
		}
		return newObject;
	}

	/* Call update in all registered actors */
	void Update()
	{
		for (unsigned int i = 0; i < mActors.size(); i++)
		{
			if (mActors[i])
				mActors[i]->Update();
		}
	}

	/* Safe getter to retrieve all registered actors in the level. */
	const std::vector<std::shared_ptr<Actor> > GetActors() const
	{
		return mActors;
	}

private:
	ActorManager(){}
	static ActorManager* mInstance;
	std::vector<std::shared_ptr<Actor>> mActors;

};


