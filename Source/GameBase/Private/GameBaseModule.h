#pragma once

#include "IGameBaseModule.h"

class FGameBaseModule 
	: public IGameBaseModule
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};