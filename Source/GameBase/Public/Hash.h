#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Hash.generated.h"

struct GAMEBASE_API FHash
{
public:
    /* 1D */
    static float Hash1D(const float X);
    static float Hash1D(const int32 X);

    /* 2D */
    static float Hash2D(const FVector2D Point);
    static float Hash2D(const float X, const float Y);
    
    static float Hash2D(const FIntPoint Point);
    static float Hash2D(const int32 X, const int32 Y);
    
    /* 3D */
    static float Hash3D(const FVector Point);
    static float Hash3D(const float X, const float Y, const float Z);

    static float Hash3D(const FIntVector Point);
    static float Hash3D(const int32 X, const int32 Y, const int32 Z);
};

UCLASS(BlueprintType)
class GAMEBASE_API UHashFunctionLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* 1D */

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash1D"))
    static float Hash_1D_F(const float X);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash1D"))
    static float Hash_1D_I(const int32 X);

    /* 2D */

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash2D"))
    static float Hash_2D_Point_F(const FVector2D Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash2D"))
    static float Hash_2D_F(const float X, const float Y);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash2D"))
    static float Hash_2D_Point_I(const FIntPoint Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash2D"))
    static float Hash_2D_I(const int32 X, const int32 Y);

    /* 3D */

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash3D"))
    static float Hash_3D_Point_F(const FVector Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash3D"))
    static float Hash_3D_F(const float X, const float Y, const float Z);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash3D"))
    static float Hash_3D_Point_I(const FIntVector Point);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|Hash", meta = (DisplayName = "Hash3D"))
    static float Hash_3D_I(const int32 X, const int32 Y, const int32 Z);
};