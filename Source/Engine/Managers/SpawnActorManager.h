#pragma once

#include "Engine/Public/Utils.h"
#include "Engine/GameFramework/Actor.h"
#include <type_traits>


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

	void Update();


	template<std::derived_from<Actor> T, typename... Args>
	std::shared_ptr<T> SpawnActor(Args... arguments)
	{
		std::shared_ptr<T> newObject = std::make_shared<T>(arguments...);
		mActors.push_back(newObject);
		if(newObject)
			newObject->Start();

		return newObject;
	}

private:
	ActorManager(){}
	static ActorManager* mInstance;
	std::vector<std::shared_ptr<Actor>> mActors;
};


void ActorManager::Update()
{

}

ActorManager* ActorManager::mInstance = nullptr;