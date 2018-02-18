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

/* Paired with VulnerabilityInterface, useful for AI */
class GAMEBASE_API IOffensiveAbilityInterface
{
	GENERATED_BODY()

public:
	/* Returns a bitflag enum with offensive capabilities. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Weapons")
	uint8 GetOffensiveAbilities();

	/* Checks if this object has offensive capabilites that match a targets vulnerabilities, and returns that set of offensive abilities (it might not be all of them). */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase")
	bool MatchesVulnerability(const TScriptInterface<IVulnerabilityInterface>& InVulnerability, uint8 OutOffensiveAbilities);
};