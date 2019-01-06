#include "BoxExtensions.h"

FBox FBoxExtensions::Encompass(const FBox& Source, const FVector& Point)
{
	auto Min = Source.Min;
	auto Max = Source.Max;

	Min.X = FMath::Min(Min.X, Point.X);
	Min.Y = FMath::Min(Min.Y, Point.Y);
	Min.Z = FMath::Min(Min.Z, Point.Z);

	Max.X = FMath::Max(Max.X, Point.X);
	Max.Y = FMath::Max(Max.Y, Point.Y);
	Max.Z = FMath::Max(Max.Z, Point.Z);

	return FBox(Min, Max);
}

FBox FBoxExtensions::Encompass(const FBox& Source, const FBox& Other)
{
	auto Min = Source.Min;
	auto Max = Source.Max;

	Min.X = FMath::Min(Min.X, Other.Min.X);
	Min.Y = FMath::Min(Min.Y, Other.Min.Y);
	Min.Z = FMath::Min(Min.Z, Other.Min.Z);

	Max.X = FMath::Max(Max.X, Other.Max.X);
	Max.Y = FMath::Max(Max.Y, Other.Max.Y);
	Max.Z = FMath::Max(Max.Z, Other.Max.Z);

	return FBox(Min, Max);
}
