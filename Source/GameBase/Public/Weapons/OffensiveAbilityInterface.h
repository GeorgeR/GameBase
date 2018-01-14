#pragma once

#include "CoreMinimal.h"
#include "VulnerabilityInterface.h"

#include "OffensiveAbilityInterface.generated.h"

UINTERFACE(MinimalAPI)
class UOffensiveAbilityInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IOffensiveAbilityInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	uint8 GetOffensiveAbilities();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool Matches(const TScriptInterface<IVulnerabilityInterface>& InVulnerability);
};