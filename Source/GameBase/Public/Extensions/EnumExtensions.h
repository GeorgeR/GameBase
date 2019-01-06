#pragma once

#include "CoreMinimal.h"

class GAMEBASE_API FEnumExtensions
{
public:
	template <typename TEnum>
	static FName GetEnumName(const FName EnumName, const TEnum Value);

	template <typename TEnum>
	FORCEINLINE static bool HasFlag(TEnum Value, TEnum Flag) { return HasFlag<TEnum, TEnum>(Value, Flag); }

	template <typename TEnum1, typename TEnum2>
	FORCEINLINE static bool HasFlag(TEnum1 Value, TEnum2 Flag);

	template <typename TEnum>
	FORCEINLINE static bool HasntFlag(TEnum Value, TEnum Flag) { return HasntFlag<TEnum, TEnum>(Value, Flag); }

	template <typename TEnum1, typename TEnum2>
	FORCEINLINE static bool HasntFlag(TEnum1 Value, TEnum2 Flag);

	template <typename TEnum>
	FORCEINLINE static void AddFlag(TEnum Value, TEnum Flag) { return AddFlag<TEnum, TEnum>(Value, Flag); }

	template <typename TEnum1, typename TEnum2>
	FORCEINLINE static void AddFlag(TEnum1 Value, TEnum2 Flag);

	template <typename TEnum>
	FORCEINLINE static void RemoveFlag(TEnum Value, TEnum Flag) { return RemovedFlag<TEnum, TEnum>(Value, Flag); }

	template <typename TEnum1, typename TEnum2>
	FORCEINLINE static void RemoveFlag(TEnum1 Value, TEnum2 Flag);
};

template <typename TEnum>
FName FEnumExtensions::GetEnumName(const FName EnumName, const TEnum Value)
{
	const auto Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName.ToString(), true);
	check(Enum);
	if (Enum == nullptr)
		return TEXT("");

	auto EnumNameStr = Enum->GetFName().ToString();
	EnumNameStr.RemoveFromStart(TEXT("E"), ESearchCase::CaseSensitive);
	const auto UppercaseChars = GetUppercaseChars(EnumNameStr);

	auto ValueName = Enum->GetNameStringByIndex(StaticCast<uint8>(Value));
	ValueName.RemoveFromStart(UppercaseChars + TEXT("_"));
	const FName Result = *ValueName;

	return Result;
}

template <typename TEnum1, typename TEnum2>
bool FEnumExtensions::HasFlag(TEnum1 Value, TEnum2 Flag)
{
	// TODO: Check that its an actual enum

	return ((Value & StaticCast<uint8>(Flag))) == StaticCast<uint8>(Flag);
}

template <typename TEnum1, typename TEnum2>
bool FEnumExtensions::HasntFlag(TEnum1 Value, TEnum2 Flag)
{
	return ((Value & StaticCast<uint8>(Flag))) == 0;
}

template <typename TEnum1, typename TEnum2>
void FEnumExtensions::AddFlag(TEnum1 Value, TEnum2 Flag)
{
	return Value |= StaticCast<uint8>(Flag);
}

template <typename TEnum1, typename TEnum2>
void FEnumExtensions::RemoveFlag(TEnum1 Value, TEnum2 Flag)
{
	Value &= ~StaticCast<uint8>(Flag);
}
