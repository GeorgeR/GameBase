#pragma once

#include "NetTypes.generated.h"

/* Stores a float in the range of 0.0-1.0 as a byte (0-255). */
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

/* Stores a float in the range -1.0-1.0 as a signed byte (-127-127) */
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

/* Stores a Quaternion as a quantized normalized vector, and a normalized float */
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