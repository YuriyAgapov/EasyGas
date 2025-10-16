#pragma once

#include "EasyGasAttributeRuleBase.h"

#include <AttributeSet.h>

#include "EasyGasAttributeBindingRule.generated.h"


/**
 * Attribute rule that binds a Gameplay Attribute to a numeric property of a specified actor's component class.
 * 
 * When the bound attribute changes, the rule updates the corresponding property on the target object.
 * This allows exposing internal Gameplay Attribute values (e.g., Health, Energy, Speed)
 * to external components such as visuals, audio, or movement logic.
 *
 * The binding is one-way: from AttributeSet -> Component property.
 *
 * Example usage:
 *   - Bind Speed to a MovementComponent’s MaxSpeed for fatigue effects.
 *
 * Notes:
 *   - The target class and property are resolved using `ClassPath` and `PropertyName` of an actor's component.
 *   - Only numeric (float/int) properties are supported.
 *   - Runtime value propagation occurs when the attribute changes.
 */
UCLASS(EditInlineNew, DisplayName = "Binding")
class UEasyGasAttributeBindingRule : public UEasyGasAttributeRuleBase
{
	GENERATED_BODY()
public:
	/** 
	 * The attribute whose value will be propagated to the target property.
	 * 
	 * This rule subscribes to updates from this attribute and mirrors its value to the target.
	 * The attribute must exist within the AttributeSet that owns this rule.
	 */
	UPROPERTY(EditDefaultsOnly, Category="EasyGas|Binding", meta=(OwnerAttributesOnly))
	FGameplayAttribute Attribute;

	/**
	 * Soft reference to the class that owns the property being updated.
	 * 
	 * Typically this is a component type that exists within the same owner context as the AttributeSet.
	 * The class is resolved at runtime to find an appropriate target instance.
	 */
	UPROPERTY(EditDefaultsOnly, Category="EasyGas|Binding")
	FSoftClassPath ClassPath;

	/**
	 * The name of the numeric property on the target class that will receive the attribute's value.
	 * 
	 * Must correspond to a float or integer property that is writable at runtime.
	 */
	UPROPERTY(EditDefaultsOnly, Category="EasyGas|Binding")
	FName PropertyName;

	// begin UEasyGasAttributeRuleBase
	virtual void InitRule(UEasyGasAttributeSet* InAttributeSet) override;
	// end UEasyGasAttributeRuleBase

private:
	/**
	 * Applies the attribute value to the resolved target property.
	 * 
	 * Called automatically when the attribute changes.
	 * Performs type checking and writes to numeric properties only.
	 */
	void SetValue(const float Value);

	/** Cached class pointer resolved from ClassPath. */
	UPROPERTY(Transient)
	UClass* TargetClass;

	/** Weak reference to the runtime object whose property will be updated. */
	UPROPERTY(Transient)
	TWeakObjectPtr<UObject> TargetObject;

	/** Cached numeric property pointer for fast assignment. */
	FNumericProperty* TargetProperty = nullptr;
};
