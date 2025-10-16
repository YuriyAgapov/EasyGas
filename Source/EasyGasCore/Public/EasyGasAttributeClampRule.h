// Copyright 2025 Yuriy Agapov, All Rights Reserved.
#pragma once

#include "EasyGasAttributeRuleBase.h"
#include "EasyGasValueSource.h"

#include <AttributeSet.h>

#include "EasyGasAttributeClampRule.generated.h"

/**
 * Policy used when the attribute range changes.
 *
 * Defines how an attribute value should behave when its clamping range (min/max) is modified.
 */
UENUM(BlueprintType)
enum class FEasyGasAttributeClampPolicy : uint8
{
	/// Do not change the attribute value when the range changes.
	KeepAbsolute,

	/// Rescale the current value proportionally to fit the new range.
	KeepRelative,

	/// Reset the attribute to the new minimum value.
	UseMin,

	/// Reset the attribute to the new maximum value.
	UseMax,
};

/**
 * Attribute clamp rule.
 *
 * This rule clamps a specified gameplay attribute within a defined range.
 * It supports dynamic min/max values and a configurable clamp policy.
 */
UCLASS(EditInlineNew, DisplayName = "Clamp")
class EASYGASCORE_API UEasyGasAttributeClampRule : public UEasyGasAttributeRuleBase
{
	GENERATED_BODY()
public:
	/// The attribute that this clamp rule operates on.
	UPROPERTY(EditDefaultsOnly, Category="EasyGas|Clamp", meta=(OwnerAttributesOnly))
	FGameplayAttribute Attribute;

	/// Minimum value for clamping (can be a fixed value or calculated dynamically).
	UPROPERTY(EditAnywhere, Category="EasyGas|Clamp")
	FEasyGasValueSource MinValue;

	/// Maximum value for clamping (can be a fixed value or calculated dynamically).
	UPROPERTY(EditAnywhere, Category="EasyGas|Clamp")
	FEasyGasValueSource MaxValue;

	/// The policy defining how the clamp should be applied.
	UPROPERTY(EditAnywhere, Category="EasyGas|Clamp")
	FEasyGasAttributeClampPolicy Policy = FEasyGasAttributeClampPolicy::KeepAbsolute;

	// begin UEasyGasAttributeRuleBase
	virtual void InitRule(UEasyGasAttributeSet* InAttributeSet) override;
	// end UEasyGasAttributeRuleBase
	
private:
	/// Updates range and rescale value if needed 
	void UpdateRange(const float InMinValue, const float InMaxValue);
};