#include "GameBaseFunctionLibrary.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Regex.h"
#include "EngineUtils.h"

FVector2D UGameBaseFunctionLibrary::GetMousePosition(UObject* InWorldContextObject)
{
	const auto PlayerController = GetPlayerControllerAs<APlayerController>(InWorldContextObject);

	auto X = 0.0f;
	auto Y = 0.0f;
	PlayerController->GetMousePosition(X, Y);

	return FVector2D(X, Y);
}

bool UGameBaseFunctionLibrary::GetMouseRay(UObject* InWorldContextObject, FVector& OutStart, FVector& OutDirection)
{
	const auto MousePosition = GetMousePosition(InWorldContextObject);
	return UGameplayStatics::DeprojectScreenToWorld(GetPlayerControllerAs<APlayerController>(InWorldContextObject), MousePosition, OutStart, OutDirection);
}

void UGameBaseFunctionLibrary::GetCenterScreenRay(UObject* InWorldContextObject, FVector& OutStart, FVector& OutDirection)
{
	const auto PlayerController = GetPlayerControllerAs<APlayerController>(InWorldContextObject);

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
	const FVector2D Size(Width, Height);

	TArray<FVector> Points;
	GetBoundsPoints(InActor, Points);

	auto bPartiallyOnScreen = false;
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
	const auto Center = InBounds.GetCenter();
	const auto Radius = InBounds.GetExtent().Size();

	const auto FOV = InFOV;
	const auto HalfFOV = FMath::DegreesToRadians(FOV / 2.0f);
	const auto DistanceFromSphere = Radius / FMath::Tan(HalfFOV);
	const auto CameraOffset = InOutTransform.GetRotation().Vector() * -DistanceFromSphere;
	InOutTransform.SetLocation(Center + CameraOffset);
}

FString UGameBaseFunctionLibrary::GetUppercaseChars(FString InString)
{
	static const FRegexPattern Regex(TEXT("([A-Z]+?)"));
	FRegexMatcher Matcher(Regex, InString);

	FString Result;
	while (Matcher.FindNext())
	{
		const auto Start = Matcher.GetMatchBeginning();
		const auto Count = Matcher.GetMatchEnding() - Start;

		Result += InString.Mid(Matcher.GetMatchBeginning(), Count);
	}

	return Result;
}

void UGameBaseFunctionLibrary::GetBoundsPoints(AActor* InActor, TArray<FVector>& OutVertices)
{
	const auto Bounds = InActor->GetComponentsBoundingBox();
	const auto Min = Bounds.Min;
	const auto Max = Bounds.Max;

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

APostProcessVolume* UGameBaseFunctionLibrary::GetMainPostProcessVolume(UObject* InWorldContextObject)
{
	check(InWorldContextObject);
	check(InWorldContextObject->GetWorld());

	static APostProcessVolume* Result = nullptr;
	if (Result != nullptr && IsValid(Result))
		return Result;

	for(TActorIterator<APostProcessVolume> Iterator(InWorldContextObject->GetWorld()); Iterator; ++Iterator)
	{
		if(Result == nullptr)
			Result = *Iterator;

		if ((*Iterator)->ActorHasTag(FName(TEXT("Main"))))
		{
			Result = *Iterator;
			break;
		}
	}

	return Result;
}

FBox UGameBaseFunctionLibrary::Encompass(const FBox& InSource, const FVector& InPoint) const
{
	auto Min = InSource.Min;
	auto Max = InSource.Max;

	Min.X = FMath::Min(Min.X, InPoint.X);
	Min.Y = FMath::Min(Min.Y, InPoint.Y);
	Min.Z = FMath::Min(Min.Z, InPoint.Z);

	Max.X = FMath::Max(Max.X, InPoint.X);
	Max.Y = FMath::Max(Max.Y, InPoint.Y);
	Max.Z = FMath::Max(Max.Z, InPoint.Z);

	return FBox(Min, Max);
}

FBox UGameBaseFunctionLibrary::Encompass(const FBox& InSource, const FBox& InOther) const
{
	auto Min = InSource.Min;
	auto Max = InSource.Max;

	Min.X = FMath::Min(Min.X, InOther.Min.X);
	Min.Y = FMath::Min(Min.Y, InOther.Min.Y);
	Min.Z = FMath::Min(Min.Z, InOther.Min.Z);

	Max.X = FMath::Max(Max.X, InOther.Max.X);
	Max.Y = FMath::Max(Max.Y, InOther.Max.Y);
	Max.Z = FMath::Max(Max.Z, InOther.Max.Z);

	return FBox(Min, Max);
}