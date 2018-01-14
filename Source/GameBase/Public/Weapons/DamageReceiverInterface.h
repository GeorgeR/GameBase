#pragma once

#include "DamageInfo.h"
#include "Projectile.h"

#include "DamageReceiverInterface.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDamageReceiverDestroyed);

UINTERFACE(BlueprintType, Blueprintable, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UDamageReceiverInterface
	: public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class GAMEBASE_API IDamageReceiverInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual void Kill() { }

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual void ApplyDamage(const FDamageHit& InHit);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual int32 GetHitPoints(uint8 InPart = 0);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual int32 GetMaxHitPoints(uint8 InPart = 0);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual int32 GetArmorPoints(uint8 InPart = 0);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual int32 GetMaxArmorPoints(uint8 InPart = 0);

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual bool IsDestroyed();

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual void Suicide();

	virtual FOnDamageReceiverDestroyed& GetOnDamageReceiverDestroyed() = 0;
};