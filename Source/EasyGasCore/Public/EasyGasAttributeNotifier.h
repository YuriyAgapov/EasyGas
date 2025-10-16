// Copyright 2025 Yuriy Agapov, All Rights Reserved.
#pragma once

#include "AttributeSet.h"

#include "EasyGasAttributeNotifier.generated.h"

struct FAttributeMetaData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreAttributeBaseChange, float&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreAttributeeChange, float&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostAttributeChange, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInitAttribute, const FAttributeMetaData&);

/**
 * Attribute change notification hub for EasyGasAttributeSet.
 *
 * FEasyGasAttributeNotifier manages a set of delegates bound to specific attributes
 * and broadcasts notifications during different stages of an attribute’s lifecycle:
 * - Initialization
 * - Pre-base change
 * - Pre-change
 * - Post-change
 *
 * It acts as a bridge between UAttributeSet and custom attribute rules (UEasyGasAttributeRuleBase),
 * allowing systems to respond to attribute value changes in a unified way.
 */
USTRUCT(BlueprintType)
struct EASYGASCORE_API FEasyGasAttributeNotifier
{
	GENERATED_BODY()
public:	
	/// @name Delegate Access
	/// Returns a reference to the delegate for the specified attribute (creates it if it doesn't exist).

	/**
	 * Returns the delegate for the attribute initialization event.
	 *
	 * @param InAttribute  The attribute for which to get the delegate.
	 * @return Reference to the delegate triggered when the attribute is initialized.
	 */
	FOnInitAttribute& GetOnInitAttributeDelegate(const FGameplayAttribute& InAttribute);

	/**
	 * Returns the delegate for the pre-base-change event.
	 *
	 * @param InAttribute  The attribute for which to get the delegate.
	 * @return Reference to the delegate triggered before the base value of the attribute changes.
	 */
	FOnPreAttributeBaseChange& GetOnPreAttributeBaseChangeDelegate(const FGameplayAttribute& InAttribute);

	/**
	 * Returns the delegate for the pre-change event.
	 *
	 * @param InAttribute  The attribute for which to get the delegate.
	 * @return Reference to the delegate triggered before the current value of the attribute changes.
	 */
	FOnPreAttributeeChange& GetOnPreAttributeChangeDelegate(const FGameplayAttribute& InAttribute);

	/**
	 * Returns the delegate for the post-change event.
	 *
	 * @param InAttribute  The attribute for which to get the delegate.
	 * @return Reference to the delegate triggered after the attribute value has changed.
	 */
	FOnPostAttributeChange& GetOnPostAttributeChangeDelegate(const FGameplayAttribute& InAttribute);
	/// @}

	/// @name Attribute Change Notifications

	/**
	 * Broadcasts an initialization event for the specified attribute.
	 *
	 * @param InAttribute  The attribute being initialized.
	 * @param InData       Metadata describing the attribute being initialized.
	 */
	void NotifyInitAttribute(const FGameplayAttribute& InAttribute, const FAttributeMetaData& InData) const;
	
	/**
	 * Broadcasts a pre-base-change event.
	 *
	 * @param InAttribute   The attribute whose base value is changing.
	 * @param OutNewValue   The new value that can be modified by listeners.
	 */
	void NotifyPreAttributeBaseChange(const FGameplayAttribute& InAttribute, float& OutNewValue) const;
	
	/**
	 * Broadcasts a pre-change event for the attribute.
	 *
	 * @param InAttribute   The attribute whose value is changing.
	 * @param OutNewValue   The new value that can be modified by listeners.
	 */
	void NotifyPreAttributeChange(const FGameplayAttribute& InAttribute, float& OutNewValue) const;
	
	/**
	 * Broadcasts a post-change event after the attribute value has been updated.
	 *
	 * @param InAttribute  The attribute that was changed.
	 * @param InOldValue   The old value of the attribute before the change.
	 * @param InNewValue   The new value of the attribute after the change.
	 */
	void NotifyPostAttributeChange(const FGameplayAttribute& InAttribute, float InOldValue, float InNewValue) const;
	/// @}

private:
	/// Delegates triggered when attributes are initialized.
	TMap<FGameplayAttribute, FOnInitAttribute> OnInitAttributeDelegates;

	/// Delegates triggered before the base value of attributes changes.
	TMap<FGameplayAttribute, FOnPreAttributeBaseChange> OnPreAttributeBaseChangeDelegates;

	/// Delegates triggered before the current value of attributes changes.
	TMap<FGameplayAttribute, FOnPreAttributeeChange> OnPreAttributeChangeDelegates;

	/// Delegates triggered after attributes have been changed.
	TMap<FGameplayAttribute, FOnPostAttributeChange> OnPostAttributeChangeDelegates;
};
