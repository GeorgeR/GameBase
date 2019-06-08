#pragma once

#include "CoreMinimal.h"

#include "WeaponInfoInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponInfoInterface 
	: public UInterface
{
	GENERATED_BODY()
};

// #todo Weapon metadata (not the actor)
class GAMEBASE_API IWeaponInfoInterface
{
	GENERATED_BODY()
};
