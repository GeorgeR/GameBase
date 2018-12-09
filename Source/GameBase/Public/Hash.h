#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Hash.generated.h"

struct GAMEBASE_API FHash
{
public:
    static float Hash(const FVector2D Point);
    static float Hash(const float X, const float Y);
    
    static float Hash(const FVector Point);
    static float Hash(const float X, const float Y, const float Z);
};

UCLASS(BlueprintType)
class GAMEBASE_API UHashFunctionLibrary
    : UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash"))
    static float Hash_2D_Point(const FVector2D Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash"))
    static float Hash_2D(const float X, const float Y);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash"))
    static float Hash_3D_Point(const FVector Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash"))
    static float Hash_3D(const float X, const float Y, const float Z);
};