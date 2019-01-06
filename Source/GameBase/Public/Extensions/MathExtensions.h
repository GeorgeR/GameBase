#pragma once

#include "CoreMinimal.h"

class GAMEBASE_API FMathExtensions
{
public:
	static void FitViewToBounds(const FBox& Bounds, float& FOV, FTransform& Transform);
};
