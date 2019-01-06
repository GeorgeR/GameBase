#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ActorExtensionsBP.generated.h"

UCLASS(BlueprintType)
class GAMEBASE_API UActorExtensions
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Returns the first object - the actor or one of it's components that implements or inherits TType */
	UFUNCTION(BlueprintCallable, Category = "GameBase|Actor")
	static UObject* GetActorOrComponent(const AActor* Actor, const TSubclassOf<UObject> Class);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Actor")
	static void GetBoundsPoints(const AActor* Actor, TArray<FVector>& Vertices);
};
