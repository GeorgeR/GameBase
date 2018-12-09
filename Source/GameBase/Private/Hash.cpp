#include "Hash.h"

/* 1D */
float FHash::Hash1D(const float X)
{
    return FMath::Frac(1.0e4 * FMath::Sin(17.0f * X) * (0.1f + FMath::Abs(FMath::Sin(13.0f * X))));
}

float FHash::Hash1D(const int32 X)
{
    return FMath::Frac(1.0e4 * FMath::Sin(17.0f * X) * (0.1f + FMath::Abs(FMath::Sin(13.0f * X))));
}

/* 2D */
float FHash::Hash2D(const FVector2D Point)
{
    return Hash2D(Point.X, Point.Y);
}

float FHash::Hash2D(const float X, const float Y)
{
    return FMath::Frac(1.0e4 * FMath::Sin(17.0f * X + 0.1f * Y) * (0.1f + FMath::Abs(FMath::Sin(13.0f * Y + X))));
}

float FHash::Hash2D(const FIntPoint Point)
{
    return Hash2D(Point.X, Point.Y);
}

float FHash::Hash2D(const int32 X, const int32 Y)
{
    return FMath::Frac(1.0e4 * FMath::Sin(17.0f * X + 0.1f * Y) * (0.1f + FMath::Abs(FMath::Sin(13.0f * Y + X))));
}

/* 3D */
float FHash::Hash3D(const FVector Point)
{
    return Hash3D(Point.X, Point.Y, Point.Z);
}

float FHash::Hash3D(const float X, const float Y, const float Z)
{
    auto XY = Hash2D(X, Y);
    return Hash2D(XY, Z);
}

float FHash::Hash3D(const FIntVector Point)
{
    return Hash3D(Point.X, Point.Y, Point.Z);
}

float FHash::Hash3D(const int32 X, const int32 Y, const int32 Z)
{
    auto XY = Hash2D(X, Y);
    return Hash2D(XY, (float)Z);
}

/* 1D */
float UHashFunctionLibrary::Hash_1D_F(const float X)
{
    return FHash::Hash1D(X);
}

float UHashFunctionLibrary::Hash_1D_I(const int32 X)
{
    return FHash::Hash1D(X);
}

/* 2D */
float UHashFunctionLibrary::Hash_2D_Point_F(const FVector2D Point)
{
    return FHash::Hash2D(Point);
}

float UHashFunctionLibrary::Hash_2D_F(const float X, const float Y)
{
    return FHash::Hash2D(X, Y);
}

float UHashFunctionLibrary::Hash_2D_Point_I(const FIntPoint Point)
{
    return FHash::Hash2D(Point);
}

float UHashFunctionLibrary::Hash_2D_I(const int32 X, const int32 Y)
{
    return FHash::Hash2D(X, Y);
}

/* 3D */
float UHashFunctionLibrary::Hash_3D_Point_F(const FVector Point)
{
    return FHash::Hash3D(Point);
}

float UHashFunctionLibrary::Hash_3D_F(const float X, const float Y, const float Z)
{
    return FHash::Hash3D(X, Y, Z);
}

float UHashFunctionLibrary::Hash_3D_Point_I(const FIntVector Point)
{
    return FHash::Hash3D(Point);
}

float UHashFunctionLibrary::Hash_3D_I(const int32 X, const int32 Y, const int32 Z)
{
    return FHash::Hash3D(X, Y, Z);
}