#pragma once

#include "Modules/ModuleInterface.h"

class GAMEBASEEDITOR_API IGameBaseEditorModule 
	: public IModuleInterface
{
public:
	void StartupModule() override = 0;
	void ShutdownModule() override = 0;
};
