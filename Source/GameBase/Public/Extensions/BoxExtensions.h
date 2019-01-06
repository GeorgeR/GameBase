#pragma once

#include "CoreMinimal.h"

class GAMEBASE_API FBoxExtensions
{
public:
	static FBox Encompass(const FBox& Source, const FVector& Point);
	static FBox Encompass(const FBox& Source, const FBox& Other);
};
