/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "GameStateManager.h"
#include "Engine.h"
#include "GameObjectManager.h"

CS230::GameStateManager::GameStateManager()
{
	state = State::START;
	currGameState = nullptr;
	nextGameState = nullptr;
}

void CS230::GameStateManager::AddGameState(GameState& gameState)
{
	gameStates.push_back(&gameState);
}

void CS230::GameStateManager::Update(double dt)
{
	switch (state)
	{
	case State::START:
		if (gameStates.empty() == true)
		{
			Engine::GetLogger().LogError("Error: Cannot load the GameState");
			state = State::SHUTDOWN;
		}
		else
		{
			nextGameState = gameStates.front();
			state = State::LOAD;
		}
		break;
	case State::LOAD:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		state = State::UPDATE;
		break;
	case State::UPDATE:
		if(nextGameState != currGameState)
		{
			Engine::GetTextureManager().Unload();
			state = State::UNLOAD;
		} else
		{
			currGameState->Update(dt);
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());
			if(GetGSComponent<GameObjectManager>() != nullptr)
			{
				currGameState->GetGSComponent<GameObjectManager>()->CollideTest();
			}
			currGameState->Draw();
		}
		break;
	case State::UNLOAD:
		currGameState->Unload();
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		currGameState = nullptr;
		if (nextGameState == nullptr)
		{
			state = State::SHUTDOWN;
		}
		else
		{
			state = State::LOAD;
		}
		break;

	case State::SHUTDOWN:
		state = State::EXIT;
		break;
	case State::EXIT:
		break;
	}
}

void CS230::GameStateManager::SetNextState(int initState)
{
	nextGameState = gameStates[initState];
}

void CS230::GameStateManager::Shutdown()
{
	nextGameState = nullptr;
}

void CS230::GameStateManager::ReloadState()
{
	state = State::UNLOAD;
}