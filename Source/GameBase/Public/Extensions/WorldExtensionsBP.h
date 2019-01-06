#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "WorldExtensionsBP.generated.h"

class APostProcessVolume;

UCLASS(BlueprintType)
class GAMEBASE_API UWorldExtensions
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameBase|World", meta = (WorldContext = "WorldContextObject"))
	static AActor* GetFirst(UObject* WorldContextObject, TSubclassOf<UObject> Class);

	UFUNCTION(BlueprintCallable, Category = "GameBase|World", meta = (WorldContext = "WorldContextObject"))
	static APostProcessVolume* GetMainPostProcessVolume(UObject* WorldContextObject);
};
