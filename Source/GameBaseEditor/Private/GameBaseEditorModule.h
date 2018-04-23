#pragma once

#include "IGameBaseEditorModule.h"

class FGameBaseEditorModule 
	: public IGameBaseEditorModule
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};