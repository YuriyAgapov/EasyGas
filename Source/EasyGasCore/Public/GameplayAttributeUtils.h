// Copyright 2025 Yuriy Agapov, All Rights Reserved.

#pragma once

#include "Containers/UnrealString.h"

class UAttributeSet;
struct FGameplayAttribute;

/**
 * Utility functions for working with FGameplayAttribute.
 *
 * Provides helper methods for validation, serialization, and type checking
 * of gameplay attributes.
 */
namespace GameplayAttributeUtils
{
    /// Safe checks whether the given FGameplayAttribute is valid, even if UAttributeSet was removed.
	EASYGASCORE_API bool IsValid(const FGameplayAttribute& InAttribute);

	/// Converts the FGameplayAttribute to a string representation.
	EASYGASCORE_API FString ExportToString(const FGameplayAttribute& InAttribute);

	/// Converts a string representation back to an FGameplayAttribute.
	EASYGASCORE_API FGameplayAttribute ImportFromString(const FString& InStr);

	/// Checks whether the given FProperty is a valid attribute type.
	EASYGASCORE_API bool IsAttributeType(const FProperty* InProperty);
}
