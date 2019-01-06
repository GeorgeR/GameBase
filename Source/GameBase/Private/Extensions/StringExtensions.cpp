#include "StringExtensions.h"

#include "Regex.h"

FString FStringExtensions::GetUppercaseChars(const FString& String)
{
	static const FRegexPattern Regex(TEXT("([A-Z]+?)"));
	FRegexMatcher Matcher(Regex, String);

	FString Result;
	while (Matcher.FindNext())
	{
		const auto Start = Matcher.GetMatchBeginning();
		const auto Count = Matcher.GetMatchEnding() - Start;

		Result += String.Mid(Matcher.GetMatchBeginning(), Count);
	}

	return Result;
}
