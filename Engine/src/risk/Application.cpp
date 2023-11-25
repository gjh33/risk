#include "Application.h"

#include <filesystem>
#include <iostream>
#include <memory>

#include "Logging.h"

#include "debug/Log.h"
#include "RiskLogger.h"

#include "resources/Resource.h"
#include "RiskResources.h"

#include "Game.h"
#include "GameEngine.h"

#include "core/Terminal.h"
#include "TerminalPlayerDialogue.h"

#include "IUserInterface.h"
#include "TerminalUserInterface.h"

namespace risk {
	const std::string Application::ResourcesDirectoryName = "resources";
	
	std::string Application::s_ApplicationDirectory;
	std::string Application::s_ResourcesDirectory;
	
	Application::Application()
	{
		std::shared_ptr appLog = std::make_shared<debug::Log>(std::cout);
		appLog->SetLevelPermissable(debug::LogLevel::Debug);
		RiskLogger::SetLog(appLog);
		
		// NOTE: This gets the current working directory not the executable directory
		// The latter would take considerable multi platform effort or the inclusion of a 3rd party library
		LOG("Initializing Application");
		s_ApplicationDirectory = std::filesystem::current_path().string();
		LOG("Application directory: " + s_ApplicationDirectory);
		s_ResourcesDirectory = std::filesystem::current_path().append(ResourcesDirectoryName).string();
		LOG("Data directory: " + s_ResourcesDirectory);

		RiskResources::Init(s_ResourcesDirectory);
		LOG("Resources Initialized");
	}

	void Application::Run()
	{
		LOG("Starting Application");

		// Note: This could be abstracted into a TerminalApplication
		// allowing for a IMGUIApplication as well
		core::Terminal terminal;
		std::shared_ptr<TerminalPlayerDialogue> dialogue = std::make_shared<TerminalPlayerDialogue>(terminal);
		std::shared_ptr<IUserInterface> ui = std::make_shared<TerminalUserInterface>(dialogue);

		// We could support loading game saves here or in the actual game engine
		// For now we will just start a new game
		std::shared_ptr<Game> game = std::make_shared<Game>();
		
		GameEngine engine(ui);
		engine.LoadGame(game);
		engine.Run();

		LOG("Exiting Application");
	}

	const std::string& Application::GetApplicationDirectory()
	{
		return s_ApplicationDirectory;
	}

	const std::string& Application::GetResourcesDirectory()
	{
		return s_ResourcesDirectory;
	}
}
