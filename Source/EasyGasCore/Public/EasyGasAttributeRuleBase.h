// Copyright 2025 Yuriy Agapov, All Rights Reserved.
#pragma once

#include "EasyGasAttributeRuleBase.generated.h"

class UEasyGasAttributeSet;
struct FGameplayAttribute;
struct FEasyGasAttributeNotifier;

/**
 * Base class for an attribute rule that can be attached to an AttributeSet.
 * 
 * Attribute rules define custom logic for handling attribute value changes -
 * for example, clamping an attribute to a range, process relations, applying scaling, or other
 * game-specific constraints.
 * 
 * The rule is typically initialized with a reference to the owning AttributeSet,
 * and can optionally listen to attribute change notifications.
 * 
 * You can create Blueprint-derived rules by implementing `BP_InitRule`.
 */
UCLASS(EditInlineNew, Abstract)
class EASYGASCORE_API UEasyGasAttributeRuleBase : public UObject
{
	GENERATED_BODY()
public:
	/**
	 * Native initialization function for the rule.
	 * 
	 * Can be overridden in C++ to register callbacks, subscribe to attribute change notifications,
	 * or otherwise prepare the rule before it starts processing attribute changes.
	 *
	 * @param InAttributeSet  The AttributeSet this rule operates on.
	 */
	virtual void InitRule(UEasyGasAttributeSet* InAttributeSet);

	/**
	 * Returns the AttributeSet associated with this rule.
	 *
	 * @return The AttributeSet instance this rule is bound to.
	 */
	UFUNCTION(BlueprintCallable, Category="EasyGas|AttributeRuleBase")
	UEasyGasAttributeSet* GetAttributeSet() const;
	
protected:
	UPROPERTY(Transient)
	TObjectPtr<UEasyGasAttributeSet> AttributeSet;
};