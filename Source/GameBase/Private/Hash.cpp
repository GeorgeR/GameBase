#include "Hash.h"

float FHash::Hash(const FVector2D Point)
{
    return Hash(Point.X, Point.Y);
}

float FHash::Hash(const float X, const float Y)
{
    return FMath::Frac(1.0e4 * FMath::Sin(17.0f * X + 0.1f * Y) * (0.1f + FMath::Abs(FMath::Sin(13.0f * Y + X))));
}

float FHash::Hash(const FVector Point)
{
    return Hash(Point.X, Point.Y, Point.Z);
}

float FHash::Hash(const float X, const float Y, const float Z)
{
    auto XY = Hash(X, Y);
    return Hash(XY, Z);
}

float UHashFunctionLibrary::Hash_2D_Point(const FVector2D Point)
{
    return FHash::Hash(Point);
}

float UHashFunctionLibrary::Hash_2D(const float X, const float Y)
{
    return FHash::Hash(X, Y);
}

float UHashFunctionLibrary::Hash_3D_Point(const FVector Point)
{
    return FHash::Hash(Point);
}

float UHashFunctionLibrary::Hash_3D(const float X, const float Y, const float Z)
{
    return FHash::Hash(X, Y, Z);
}