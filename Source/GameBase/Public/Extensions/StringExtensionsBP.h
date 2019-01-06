#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "StringExtensionsBP.generated.h"

UCLASS(BlueprintType)
class GAMEBASE_API UStringExtensions
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GameBase|String")
	static FString GetUppercaseChars(const FString& String);
};
