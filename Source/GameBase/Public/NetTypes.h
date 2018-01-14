#pragma once

#include "NetTypes.generated.h"

USTRUCT(BlueprintType)
struct GAMEBASE_API FSingle_Normalized
{
	GENERATED_BODY()

public:
	UPROPERTY()
	uint8 Value = 0;

	FORCEINLINE FSingle_Normalized() { }

	FORCEINLINE FSingle_Normalized(float InValue)
	{
		SetValue(InValue);
	}

	void SetValue(float InValue);
	float GetValue() const;
};

USTRUCT(BlueprintType)
struct GAMEBASE_API FSingle_SignedNormalized
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int8 Value = 0;

	FORCEINLINE FSingle_SignedNormalized() { }

	FORCEINLINE FSingle_SignedNormalized(float InValue)
	{
		SetValue(InValue);
	}

	void SetValue(float InValue);
	float GetValue() const;
};

USTRUCT(BlueprintType)
struct GAMEBASE_API FQuat_NetQuantize
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FVector_NetQuantizeNormal Value;

	UPROPERTY()
	FSingle_Normalized W;

	FORCEINLINE FQuat_NetQuantize() { }

	FORCEINLINE FQuat_NetQuantize(FQuat InValue) 
	{
		SetValue(InValue);
	}

	void SetValue(FQuat InValue);
	FQuat GetValue() const;
};