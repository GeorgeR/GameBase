#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "HasSizeInBytesInterface.generated.h"

class UInputComponent;

UINTERFACE(MinimalAPI)
class UHasSizeInBytesInterface
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IHasSizeInBytesInterface
{
	GENERATED_BODY()

public:
	virtual size_t GetSizeInBytes() = 0;
};