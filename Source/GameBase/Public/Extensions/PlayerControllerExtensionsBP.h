#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "PlayerControllerExtensionsBP.generated.h"

UCLASS(BlueprintType)
class GAMEBASE_API UPlayerControllerExtensions
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameBase|Player Controller", meta = (WorldContext = "WorldContextObject"))
	static FVector2D GetMousePosition(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Player Controller", meta = (DisplayName = "GetMousePosition"))
	static FVector2D GetMousePosition_FromPlayerController(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Player Controller", meta = (WorldContext = "WorldContextObject"))
	static bool GetMouseRay(UObject* WorldContextObject, FVector& Start, FVector& Direction);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Player Controller", meta = (DisplayName = "GetMouseRay"))
	static bool GetMouseRay_FromPlayerController(APlayerController* PlayerController, FVector& Start, FVector& Direction);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Player Controller", meta = (WorldContext = "WorldContextObject"))
	static void GetCenterScreenRay(UObject* WorldContextObject, FVector& Start, FVector& Direction);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Player Controller", meta = (DisplayName = "GetCenterScreenRay"))
	static void GetCenterScreenRay_FromPlayerController(APlayerController* PlayerController, FVector& Start, FVector& Direction);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Player Controller", meta = (WorldContext = "WorldContextObject"))
	static bool GetScreenspaceBounds(UObject* WorldContextObject, AActor* Actor, FBox2D& Bounds);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Player Controller", meta = (DisplayName = "GetScreenspaceBounds"))
	static bool GetScreenspaceBounds_FromPlayerController(APlayerController* PlayerController, AActor* Actor, FBox2D& Bounds);
};
