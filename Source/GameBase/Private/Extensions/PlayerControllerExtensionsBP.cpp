#include "PlayerControllerExtensionsBP.h"

#include "PlayerControllerExtensions.h"

FVector2D UPlayerControllerExtensions::GetMousePosition(UObject* WorldContextObject)
{
	return FPlayerControllerExtensions::GetMousePosition(WorldContextObject);
}

FVector2D UPlayerControllerExtensions::GetMousePosition_FromPlayerController(APlayerController* PlayerController)
{
	return FPlayerControllerExtensions::GetMousePosition_FromPlayerController(PlayerController);
}

bool UPlayerControllerExtensions::GetMouseRay(UObject* WorldContextObject, FVector& Start, FVector& Direction)
{
	return FPlayerControllerExtensions::GetMouseRay(WorldContextObject, Start, Direction);
}

bool UPlayerControllerExtensions::GetMouseRay_FromPlayerController(APlayerController* PlayerController, FVector& Start, FVector& Direction)
{
	return FPlayerControllerExtensions::GetMouseRay_FromPlayerController(PlayerController, Start, Direction);
}

void UPlayerControllerExtensions::GetCenterScreenRay(UObject* WorldContextObject, FVector& Start, FVector& Direction)
{
	return FPlayerControllerExtensions::GetCenterScreenRay(WorldContextObject, Start, Direction);
}

void UPlayerControllerExtensions::GetCenterScreenRay_FromPlayerController(APlayerController* PlayerController, FVector& Start, FVector& Direction)
{
	return FPlayerControllerExtensions::GetCenterScreenRay_FromPlayerController(PlayerController, Start, Direction);
}

bool UPlayerControllerExtensions::GetScreenspaceBounds(UObject* WorldContextObject, AActor* Actor, FBox2D& Bounds)
{
	return FPlayerControllerExtensions::GetScreenspaceBounds(WorldContextObject, Actor, Bounds);
}

bool UPlayerControllerExtensions::GetScreenspaceBounds_FromPlayerController(APlayerController* PlayerController, AActor* Actor, FBox2D& Bounds)
{
	return FPlayerControllerExtensions::GetScreenspaceBounds_FromPlayerController(PlayerController, Actor, Bounds);
}

