#pragma once

#include "ModuleInterface.h"

class GAMEBASE_API IGameBaseModule 
	: public IModuleInterface
{
public:
	void StartupModule() override = 0;
	void ShutdownModule() override = 0;
};