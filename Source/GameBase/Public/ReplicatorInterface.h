#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"

#include "ReplicatorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UReplicatorInterface 
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API IReplicatorInterface
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const = 0;
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const { return true; }
	inline virtual bool IsSupportedForNetworking() const { return true; }
};