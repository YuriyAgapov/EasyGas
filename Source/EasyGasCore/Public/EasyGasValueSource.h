// Copyright 2025 Yuriy Agapov, All Rights Reserved.
#pragma once

#include <AttributeSet.h>

#include "EasyGasValueSource.generated.h"

/**
 * Source type for obtaining a gameplay attribute value.
 *
 * Defines whether the value comes from a constant, another attribute, or a DataTable.
 */
UENUM(BlueprintType)
enum class EEasyGasValueSourceType : uint8
{
	/// Use a constant numeric value.
	Constant,

	/// Retrieve the value from a DataTable.
	DataTable,

	/// Use the value of another attribute.
	Attribute
};

/**
 * Flexible value source for gameplay attributes.
 *
 * FEasyGasValueSource allows using a constant value, linking to another attribute,
 * or retrieving a value from a DataTable. This is commonly used for min/max
 * values, scaling factors, or other dynamic attribute logic.
 */
USTRUCT(BlueprintType)
struct EASYGASCORE_API FEasyGasValueSource
{
	GENERATED_BODY()

	/// Specifies the source type for this value (Constant, Attribute, DataTable).
	UPROPERTY(EditDefaultsOnly, Category="EasyGas|ValueSource")
	EEasyGasValueSourceType Type = EEasyGasValueSourceType::DataTable;

	/// Constant value (used when Type == Constant, if Type == Attribute used as Cache).
	UPROPERTY(EditDefaultsOnly, Category="EasyGas|ValueSource", meta=(EditCondition="Type == EEasyGasValueSourceType::Constant", EditConditionHides))
	float Value = 0.f;

	/// Attribute reference (used when Type == Attribute).
	UPROPERTY(EditDefaultsOnly, Category="EasyGas|ValueSource", meta=(EditCondition="Type == EEasyGasValueSourceType::Attribute", EditConditionHides, OwnerAttributesOnly))
	FGameplayAttribute Attribute;

	FEasyGasValueSource() = default;

	/// Constructor for a constant value.
	FEasyGasValueSource(const float Value) : Type(EEasyGasValueSourceType::Constant), Value(Value) {}

	/// Constructor for an attribute value.
	FEasyGasValueSource(FGameplayAttribute Attribute) : Type(EEasyGasValueSourceType::Attribute), Attribute(MoveTemp(Attribute)) {}

	/**
	 * Retrieves the numeric value based on the current source type.
	 *
	 * @param AttributeSet  The AttributeSet used when the source is an attribute.
	 * @return The resolved float value.
	 */
	float GetValue(const UAttributeSet* AttributeSet) const;
};