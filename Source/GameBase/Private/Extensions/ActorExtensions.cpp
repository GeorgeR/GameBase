#include "Extensions/ActorExtensions.h"

#include "GameFramework/Actor.h"

void FActorExtensions::GetBoundsPoints(const AActor* Actor, TArray<FVector>& Vertices)
{
	const auto Bounds = Actor->GetComponentsBoundingBox();
	const auto Min = Bounds.Min;
	const auto Max = Bounds.Max;

	Vertices.Empty();
	Vertices = {
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
