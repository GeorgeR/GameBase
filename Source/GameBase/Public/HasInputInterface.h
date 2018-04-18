#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "HasInputInterface.generated.h"

class UInputComponent;

UINTERFACE(MinimalAPI)
class UHasInputInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IHasInputInterface
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) = 0;
};