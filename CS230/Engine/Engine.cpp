/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021	
-----------------------------------------------------------------*/
#include "Engine.h"

void Engine::Init(std::string windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(windowName);
}

void Engine::Shutdown()
{
	gameStateManager.Shutdown();
	logger.LogEvent("Engine Shutdown");
}

void Engine::Update()
{
	gameStateManager.Update();
	logger.LogVerbose("GameStateManager Update");
	input.Update();
	logger.LogVerbose("Input Update");
	window.Update();
	logger.LogVerbose("Window Update");
}

bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();	
}

Engine::Engine() :
#ifdef _DEBUG				
	logger(CS230::Logger::Severity::Debug, true)
#else 						
	logger(CS230::Logger::Severity::Event, false)
#endif
{}

Engine::~Engine() {}
