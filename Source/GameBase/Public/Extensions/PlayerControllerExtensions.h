#pragma once

#include "CoreMinimal.h"

class GAMEBASE_API FPlayerControllerExtensions
{
public:
	static FVector2D GetMousePosition(UObject* WorldContextObject);
	static FVector2D GetMousePosition_FromPlayerController(APlayerController* PlayerController);

	static bool GetMouseRay(UObject* WorldContextObject, FVector& Start, FVector& Direction);
	static bool GetMouseRay_FromPlayerController(APlayerController* PlayerController, FVector& Start, FVector& Direction);

	static void GetCenterScreenRay(UObject* WorldContextObject, FVector& Start, FVector& Direction);
	static void GetCenterScreenRay_FromPlayerController(APlayerController* PlayerController, FVector& Start, FVector& Direction);

	static bool GetScreenspaceBounds(UObject* WorldContextObject, AActor* Actor, FBox2D& Bounds);
	static bool GetScreenspaceBounds_FromPlayerController(APlayerController* PlayerController, AActor* Actor, FBox2D& Bounds);
};
