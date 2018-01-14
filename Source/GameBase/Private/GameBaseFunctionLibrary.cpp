#include "GameBaseFunctionLibrary.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Regex.h"

FVector2D UGameBaseFunctionLibrary::GetMousePosition(UObject* InWorldContextObject)
{
	APlayerController* PlayerController = GetPlayerControllerAs<APlayerController>(InWorldContextObject);
	
	float X = 0.0f;
	float Y = 0.0f;
	PlayerController->GetMousePosition(X, Y);

	return FVector2D(X, Y);
}

bool UGameBaseFunctionLibrary::GetMouseRay(UObject* InWorldContextObject, FVector& OutStart, FVector& OutDirection)
{
	FVector2D MousePosition = GetMousePosition(InWorldContextObject);
	return UGameplayStatics::DeprojectScreenToWorld(GetPlayerControllerAs<APlayerController>(InWorldContextObject), MousePosition, OutStart, OutDirection);
}

void UGameBaseFunctionLibrary::GetCenterScreenRay(UObject* InWorldContextObject, FVector& OutStart, FVector& OutDirection)
{
	APlayerController* PlayerController = GetPlayerControllerAs<APlayerController>(InWorldContextObject);

	FVector Start;
	FRotator Rotator;
	PlayerController->PlayerCameraManager->GetCameraViewPoint(Start, Rotator);

	OutStart = Start;
	OutDirection = Rotator.Vector();
}

bool UGameBaseFunctionLibrary::GetScreenspaceBounds(APlayerController* InPlayerController, AActor* InActor, FBox2D& OutBounds)
{
	OutBounds = FBox2D(EForceInit::ForceInitToZero);

	int32 Width, Height;
	InPlayerController->GetViewportSize(Width, Height);
	FVector2D Size(Width, Height);

	TArray<FVector> Points;
	GetBoundsPoints(InActor, Points);
	
	bool bPartiallyOnScreen = false;
	for (auto i = 0; i < Points.Num(); i++)
	{
		FVector2D Point2D;
		if (InPlayerController->ProjectWorldLocationToScreen(Points[i], Point2D))
			if (Point2D.X > 0 && Point2D.X <= Width && Point2D.Y > 0 && Point2D.Y <= Height)
				bPartiallyOnScreen = true;

		OutBounds += Point2D / Size;
	}

	return bPartiallyOnScreen;
}

void UGameBaseFunctionLibrary::FitViewToBounds(const FBox& InBounds, float& InFOV, FTransform& InOutTransform)
{
	FVector Center = InBounds.GetCenter();
	float Radius = InBounds.GetExtent().Size();

	float FOV = InFOV;
	float HalfFOV = FMath::DegreesToRadians(FOV / 2.0f);
	float DistanceFromSphere = Radius / FMath::Tan(HalfFOV);
	FVector CameraOffset = InOutTransform.GetRotation().Vector() * -DistanceFromSphere;
	InOutTransform.SetLocation(Center + CameraOffset);
}

FString UGameBaseFunctionLibrary::GetUppercaseChars(FString InString)
{
	static const FRegexPattern Regex(TEXT("([A-Z]+?)"));
	FRegexMatcher Matcher(Regex, InString);

	FString Result;
	while (Matcher.FindNext())
	{
		int32 Start = Matcher.GetMatchBeginning();
		int32 Count = Matcher.GetMatchEnding() - Start;

		Result += InString.Mid(Matcher.GetMatchBeginning(), Count);
	}

	return Result;
}

void UGameBaseFunctionLibrary::GetBoundsPoints(AActor* InActor, TArray<FVector>& OutVertices)
{
	FBox Bounds = InActor->GetComponentsBoundingBox();
	FVector Min = Bounds.Min;
	FVector Max = Bounds.Max;

	OutVertices.Empty();
	OutVertices = {
		Min,
		FVector(Min.X, Max.Y, Min.Z),
		FVector(Max.X, Max.Y, Min.Z),
		FVector(Max.X, Min.Y, Min.Z),
		FVector(Min.X, Max.Y, Max.Z),
		FVector(Min.X, Min.Y, Max.Z),
		FVector(Max.X, Min.Y, Max.Z),
		Max
	};
}