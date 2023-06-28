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




	void Update()
	{
		for (int i = 0; i < mActors.size(); i++)
		{
			if(mActors[i])
				mActors[i]->Update();
		}
	}

	std::vector<std::shared_ptr<Actor>> GetActors() const
	{
		return mActors;
	}


private:
	ActorManager(){}
	static ActorManager* mInstance;
	std::vector<std::shared_ptr<Actor>> mActors;
};


