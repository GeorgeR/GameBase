#include "Extensions/MathExtensions.h"

void FMathExtensions::FitViewToBounds(const FBox& Bounds, float& FOV, FTransform& Transform)
{
	const auto Center = Bounds.GetCenter();
	const auto Radius = Bounds.GetExtent().Size();

	const auto HalfFOV = FMath::DegreesToRadians(FOV / 2.0f);
	const auto DistanceFromSphere = Radius / FMath::Tan(HalfFOV);
	const auto CameraOffset = Transform.GetRotation().Vector() * -DistanceFromSphere;
	Transform.SetLocation(Center + CameraOffset);
}
