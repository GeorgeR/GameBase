#include "PlayerControllerExtensions.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFrameworkExtensions.h"
#include "ActorExtensions.h"

FVector2D FPlayerControllerExtensions::GetMousePosition(UObject* WorldContextObject)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	const auto PlayerController = FGameFrameworkExtensions::GetPlayerControllerAs<APlayerController>(WorldContextObject);

	return GetMousePosition_FromPlayerController(PlayerController);
}

FVector2D FPlayerControllerExtensions::GetMousePosition_FromPlayerController(APlayerController* PlayerController)
{
	check(PlayerController);

	auto X = 0.0f;
	auto Y = 0.0f;
	PlayerController->GetMousePosition(X, Y);

	return FVector2D(X, Y);
}

bool FPlayerControllerExtensions::GetMouseRay(UObject* WorldContextObject, FVector& Start, FVector& Direction)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	const auto PlayerController = FGameFrameworkExtensions::GetPlayerControllerAs<APlayerController>(WorldContextObject);
	
	return GetMouseRay_FromPlayerController(PlayerController, Start, Direction);
}

bool FPlayerControllerExtensions::GetMouseRay_FromPlayerController(APlayerController* PlayerController, FVector& Start, FVector& Direction)
{
	check(PlayerController);

	const auto MousePosition = GetMousePosition_FromPlayerController(PlayerController);
	
	return UGameplayStatics::DeprojectScreenToWorld(PlayerController, MousePosition, Start, Direction);
}

void FPlayerControllerExtensions::GetCenterScreenRay(UObject* WorldContextObject, FVector& Start, FVector& Direction)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());

	const auto PlayerController = FGameFrameworkExtensions::GetPlayerControllerAs<APlayerController>(WorldContextObject);

	GetCenterScreenRay_FromPlayerController(PlayerController, Start, Direction);
}

void FPlayerControllerExtensions::GetCenterScreenRay_FromPlayerController(APlayerController* PlayerController, FVector& Start, FVector& Direction)
{
	check(PlayerController);

	FRotator Rotator;
	PlayerController->PlayerCameraManager->GetCameraViewPoint(Start, Rotator);

	Start = Start;
	Direction = Rotator.Vector();
}

bool FPlayerControllerExtensions::GetScreenspaceBounds(UObject* WorldContextObject, AActor* Actor, FBox2D& Bounds)
{
	check(WorldContextObject);
	check(WorldContextObject->GetWorld());
	check(Actor);

	const auto PlayerController = FGameFrameworkExtensions::GetPlayerControllerAs<APlayerController>(WorldContextObject);

	return GetScreenspaceBounds_FromPlayerController(PlayerController, Actor, Bounds);
}

bool FPlayerControllerExtensions::GetScreenspaceBounds_FromPlayerController(APlayerController* PlayerController, AActor* Actor, FBox2D& Bounds)
{
	check(PlayerController);
	check(Actor);

	Bounds = FBox2D(EForceInit::ForceInitToZero);

	int32 Width, Height;
	PlayerController->GetViewportSize(Width, Height);
	const FVector2D Size(Width, Height);

	TArray<FVector> Points;

	FActorExtensions::GetBoundsPoints(Actor, Points);

	auto bPartiallyOnScreen = false;
	for (auto i = 0; i < Points.Num(); i++)
	{
		FVector2D Point2D;
		if (PlayerController->ProjectWorldLocationToScreen(Points[i], Point2D))
			if (Point2D.X > 0 && Point2D.X <= Width && Point2D.Y > 0 && Point2D.Y <= Height)
				bPartiallyOnScreen = true;

		Bounds += Point2D / Size;
	}

	return bPartiallyOnScreen;
}
