/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include <iostream>    // cout.rdbuf
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool useConsole) : minLevel(severity), outStream("Trace.log") {
	if (useConsole == true) {
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

CS230::Logger::~Logger() {
	outStream.flush();
	outStream.close();
}

void CS230::Logger::Log(CS230::Logger::Severity severity, std::string message) {
	if(severity >= minLevel)
	{
		switch (severity)
		{
		case Severity::Error:
			std::cout << "Error";
			break;
		case Severity::Event:
			std::cout << "Event";
			break;
		case Severity::Debug:
			std::cout << "Debug";
			break;
		case Severity::Verbose:
			std::cout << "Verb";
			break;
		}
		std::cout << '\t' << message << std::endl;
	}
}
