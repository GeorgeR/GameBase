#include "NetTypes.h"

void FSingle_Normalized::SetValue(float InValue)
{
	Value = (uint8)(InValue * 255);
}

float FSingle_Normalized::GetValue() const
{
	return (float)(Value / 255);
}

void FSingle_SignedNormalized::SetValue(float InValue)
{
	Value = (int8)(InValue * 127);
}

float FSingle_SignedNormalized::GetValue() const
{
	return (float)(Value / 127);
}

void FQuat_NetQuantize::SetValue(FQuat InValue)
{
	Value.X = InValue.X;
	Value.Y = InValue.Y;
	Value.Z = InValue.Z;
	W = InValue.W;
}

FQuat FQuat_NetQuantize::GetValue() const
{
	FQuat Result(Value.X, Value.Y, Value.Z, W.GetValue());
	return Result;
}