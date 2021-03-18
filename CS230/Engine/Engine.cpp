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
	fpsCalcTime = lastTick;
}

void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
}

void Engine::Update()
{
	if(frameCount >= FPS_IntervalFrameCount)
	{
		const double averageFrameRate = frameCount / std::chrono::duration<double>(lastTick - fpsCalcTime).count();
		logger.LogEvent("FPS:\t" + std::to_string(averageFrameRate));
		frameCount = 0;
		fpsCalcTime = lastTick;
	}
	if (std::chrono::duration<double>(std::chrono::system_clock::now() - lastTick).count() >= 1 / Target_FPS)
	{
		frameCount++;
		gameStateManager.Update(std::chrono::duration<double>(std::chrono::system_clock::now() - lastTick).count());
		logger.LogVerbose("Update GameStateManager");
		input.Update();
		logger.LogVerbose("Update Input");
		window.Update();
		logger.LogVerbose("Update Window");
		lastTick = std::chrono::system_clock::now();
	}
}

bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();	
}

Engine::Engine() : lastTick(std::chrono::system_clock::now()), frameCount(0),
#ifdef _DEBUG				
	logger(CS230::Logger::Severity::Debug, true, lastTick)
#else 						
	logger(CS230::Logger::Severity::Event, false, lastTick)
#endif
{}

Engine::~Engine() {}
