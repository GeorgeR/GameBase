#pragma once

#include "DamageDealerInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UDamageDealerInterface
	: public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class GAMEBASE_API IDamageDealerInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameBase|Damage")
	virtual FName GetName() = 0;
	
	UFUNCTION(BlueprintCallable, Category = "GameBase|Damage")
	virtual int32 GetTeamName() = 0;

	template <typename TTeamName>
	TTeamName GetTeamNameAs();
};

template <typename TTeamName>
TTeamName IDamageDealerInterface::GetTeamNameAs()
{
	return static_cast<TTeamName>(GetTeamName());
}