#include "MathExtensionsBP.h"

#include "MathExtensions.h"

void UMathExtensions::FitViewToBounds(const FBox& Bounds, float& FOV, FTransform& Transform)
{
	FMathExtensions::FitViewToBounds(Bounds, FOV, Transform);
}
