// Copyright 2025 Yuriy Agapov, All Rights Reserved.
#pragma once

#include <AttributeSet.h>

#include "EasyGasAttributeNotifier.h"
#include "EasyGasAttributeSet.generated.h"

class UEasyGasAttributeRuleBase;

/**
 * Extended AttributeSet with EasyGas rules support.
 *
 * UEasyGasAttributeSet extends UAttributeSet to support attribute rules
 * and provides notifications for attribute changes via FEasyGasAttributeNotifier.
 * 
 * Rules can be added to the `Rules` array to implement custom logic for attributes,
 * such as clamping, scaling, or other gameplay-specific modifications.
 */
UCLASS()
class EASYGASCORE_API UEasyGasAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	// begin UObject
	virtual void PostInitProperties() override;
	// end UObject

	// begin UAttributeSet
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void InitFromMetaDataTable(const UDataTable* DataTable) override;
	// end UAttributeSet

	/// Returns the notifier that manages attribute change delegates.
	FEasyGasAttributeNotifier& GetNotifier();

	void AddRule(UEasyGasAttributeRuleBase* InRule);

private:
	void Initialize();
	
	/// Rules that define custom logic for attribute changes (e.g., clamps, modifiers).
	UPROPERTY(EditDefaultsOnly, Instanced, Category="EasyGas|AttributeSet")
	TArray<UEasyGasAttributeRuleBase*> Rules;

	/// Notifier used internally to broadcast attribute change events.
	FEasyGasAttributeNotifier Notifier;

	mutable TSet<FString> AttributeChangeList;
};
