#pragma once

#include "DamageDealerInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable, MinimalAPI)
class UDamageDealerInterface
	: public UInterface
{
	GENERATED_BODY()
};

/* Interface for an object that can deal damage */
class GAMEBASE_API IDamageDealerInterface
{
	GENERATED_BODY()

public:
	/* Returns the name of the dealer, usually the player name. Useful for UI notifications. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	FName GetName();
	
	/* Returns the dealers team, if any (might return red, blue, or guild). */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	FName GetTeam();

	/* Returns the associated controller. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "GameBase|Damage")
	AController* GetController();
};