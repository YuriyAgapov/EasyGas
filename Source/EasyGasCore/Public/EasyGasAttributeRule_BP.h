#pragma once

#include "EasyGasAttributeRuleBase.h"

#include "EasyGasAttributeRule_BP.generated.h"


/**
 * Blueprint-based attribute rule for EasyGas.
 * 
 * This class allows you to implement custom attribute behavior entirely in Blueprint.
 * All lifecycle hooks (pre/post attribute change, initialization, etc.) are exposed
 * as Blueprint events.
 *
 * Important:
 * - Attribute notifications start working **only after you subscribe** to them
 *   using Subscribe().
 * - Attribute values should be **set only from inside event handlers**
 *   (like BP_OnPreAttributeChange or BP_OnPostAttributeChange),
 *   otherwise you may cause recursion or inconsistent state.
 *
 * TODO: migrate functional tests from EasySandbox
 */
UCLASS(Abstract, Blueprintable)
class UEasyGasAttributeRule_BP : public UEasyGasAttributeRuleBase
{
	GENERATED_BODY()
public:
	/**
	 * Blueprint event for initializing the rule.
	 * 
	 * Called when the rule is first set up by EasyGasAttributeSet, giving Blueprint logic a chance
	 * to initialize any internal state or perform setup using the provided
	 * AttributeSet.
	 *
	 * @param InAttributeSet The AttributeSet instance this rule is attached to. 
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="EasyGas|AttributeRule", meta = (DisplayName = "InitRule"))
	void BP_InitRule(UEasyGasAttributeSet* InAttributeSet);

	/**
	 * Blueprint event for initializing individual attributes.
	 * 
	 * Called (if Subscribed) for each attribute when it's registered in the AttributeSet.
	 * Allows you to process metadata (from DataTable or prepare per-attribute state.
	 *
	 * @param Attribute  The attribute being initialized.
	 * @param MetaData   Metadata describing the attribute (min/max/default values, etc.).
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="EasyGas|AttributeRule", meta = (DisplayName = "InitAttribute"))
	void BP_InitAttribute(const FGameplayAttribute& Attribute, const FAttributeMetaData& MetaData);

	/**
	 * Forwarded from UAttributeSet::PreAttributeBaseChange.
	 * 
	 * Called (if Subscribed) just before any modification happens to an attribute's base value
	 * (when an attribute aggregator exists).
	 * 
	 * Use this to enforce clamping or validation of the base value.
	 * Avoid triggering gameplay-related events here — do that in BP_OnPreAttributeChange.
	 *
	 * @param Attribute The attribute being modified.
	 * @param NewValue  The new base value before being applied.
	 * @return The (optionally) modified value to apply.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="EasyGas|AttributeRule", meta = (DisplayName = "OnPreAttributeBaseChange"))
	float BP_OnPreAttributeBaseChange(const FGameplayAttribute& Attribute, float NewValue);

	/**
	 * Forwarded from UAttributeSet::PreAttributeChange.
	 * 
	 * Called (if Subscribed) just before any modification happens to an attribute's final value.
	 * This is where you typically apply clamping logic such as:
	 *     Health = Clamp(Health, 0, MaxHealth)
	 *
	 * This function should NOT trigger gameplay effects — it’s purely for enforcing value constraints.
	 *
	 * @param Attribute The attribute being modified.
	 * @param NewValue  The new (mutable) value before being applied.
	 * @return The modified or clamped value.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="EasyGas|AttributeRule", meta = (DisplayName = "OnPreAttributeChange"))
	float BP_OnPreAttributeChange(const FGameplayAttribute& Attribute, float NewValue);

	/**
	 * Forwarded from UAttributeSet::PostAttributeChange.
	 * 
	 * Called (if Subscribed) immediately after any modification happens to an attribute.
	 * Use this to react to value changes (e.g. trigger death when Health <= 0).
	 *
	 * @param Attribute The attribute that changed.
	 * @param OldValue  The previous value before the change.
	 * @param NewValue  The new value after the change.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="EasyGas|AttributeRule", meta = (DisplayName = "OnPostAttributeChange"))
	void BP_OnPostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue);

	/**
	 * Subscribes this rule to notifications for the given attribute.
	 * 
	 * Notifications (Init, PreChange, PostChange, etc.) will only be delivered
	 * for attributes that have been explicitly subscribed to via this method.
	 *
	 * @param Attribute      The attribute to subscribe to.
	 * @param bInit          If true, BP_InitAttribute will be called for this attribute.
	 * @param bPreChangeBase If true, BP_OnPreAttributeBaseChange will be called for this attribute.
	 * @param bPreChange     If true, BP_OnPreAttributeChange will be called for this attribute.
	 * @param bPostChange    If true, BP_OnPostAttributeChange will be called for this attribute.
	 */
	UFUNCTION(BlueprintCallable, Category="EasyGas|AttributeRule")
	void Subscribe(
		const FGameplayAttribute& Attribute,
		bool bInit = false,
		bool bPreChangeBase = false,
		bool bPreChange = false,
		bool bPostChange = false);

	/**
	 * Returns the current value of the specified attribute.
	 *
	 * @param Attribute The attribute whose value to get.
	 * @return The current float value.
	 */
	UFUNCTION(BlueprintCallable, Category="EasyGas|AttributeRule")
	float GetAttributeValue(const FGameplayAttribute& Attribute) const;

	/**
	 * Sets a new value for the specified attribute.
	 *
	 * Warning: This method should only be called **from within event handlers**
	 * (such as BP_OnPreAttributeChange or BP_OnPostAttributeChange),
	 * otherwise you may cause recursive updates or inconsistent state.
	 *
	 * @param Attribute The attribute to modify.
	 * @param NewValue  The new value to assign.
	 */
	UFUNCTION(BlueprintCallable, Category="EasyGas|AttributeRule")
	void SetAttributeValue(const FGameplayAttribute& Attribute, float NewValue);

	UFUNCTION(BlueprintCallable, Category="EasyGas|AttributeRule")
	void SetAttributeBaseValue(const FGameplayAttribute& Attribute, float NewValue);
	
	/// Returns OwningActor of AttributeSet
	UFUNCTION(BlueprintCallable, Category="EasyGas|AttributeRule")
	AActor* GetOwningActor() const;
	
	// begin UEasyGasAttributeRuleBase
	virtual void InitRule(UEasyGasAttributeSet* InAttributeSet) override;
	// end UEasyGasAttributeRuleBase
};
