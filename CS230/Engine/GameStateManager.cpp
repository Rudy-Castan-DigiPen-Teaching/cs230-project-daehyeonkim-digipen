/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#pragma once
#include "GameStateManager.h"
#include "Engine.h"
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

void CS230::GameStateManager::Update()
{
	switch (state)
	{
	case State::START:
		if (gameStates.empty() == true)
		{
			Engine::GetLogger().LogError("Error");
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
			state = State::UNLOAD;
		} else
		{
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());
			currGameState->Update();
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
		Engine::GetLogger().LogEvent("Engine Shutdown");
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