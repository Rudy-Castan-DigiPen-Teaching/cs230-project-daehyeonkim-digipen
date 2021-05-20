/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Project: CS230
Author: Daehyeon Kim
Creation date:4/19/2021
-----------------------------------------------------------------*/
#include "GameObjectManager.h"
#include "Engine.h"
#include "GameObject.h"
#include "TransformMatrix.h"

void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

CS230::GameObjectManager::~GameObjectManager()
{
	for(GameObject* unloadedObj : gameObjects)
	{
		delete unloadedObj;
	}
	gameObjects.clear();
}

void CS230::GameObjectManager::CollideTest()
{
	for(GameObject* testObj1 : gameObjects)
	{
		for(GameObject* testObj2 : gameObjects)
		{
			if(testObj1 != testObj2 && testObj1->DoesCollideWith(testObj2) == true)
			{
				Engine::GetLogger().LogEvent("Collision Detected: " + testObj1->GetObjectTypeName() + " and " + testObj2->GetObjectTypeName());
				testObj1->ResolveCollision(testObj2);
			}
		}
	}
}

void CS230::GameObjectManager::Update(double dt)
{
	std::list<GameObject*> NeedToRemoved{};
	for(GameObject* updatedObj : gameObjects)
	{
		updatedObj->Update(dt);
		if(updatedObj->IsDestroyed() == true)
		{
			NeedToRemoved.push_back(updatedObj);
		}
	}
	for(GameObject* removedObj : NeedToRemoved)
	{
		gameObjects.remove(removedObj);
		delete removedObj;
	}
	NeedToRemoved.clear();
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (GameObject* drewObj : gameObjects)
	{
		drewObj->Draw(cameraMatrix);
	}
}
