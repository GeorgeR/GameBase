#pragma once

#include "CoreMinimal.h"
#include "DamageDealerInterface.h"

#include "FiringInterface.generated.h"

UINTERFACE(MinimalAPI)
class UFiringInterface : public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IFiringInterface
{
	GENERATED_BODY()

public:
	virtual void StartFire(const TScriptInterface<IDamageDealerInterface>& InDamageDealer) { }
	virtual void StopFire() { }
	virtual void Fire() { }
	virtual bool IsFiring() { return false; }
	virtual bool CanFire() { return false; }
};