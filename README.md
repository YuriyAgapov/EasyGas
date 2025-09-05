# Overview
<b>EasyGas</b> allows to use <b>Gameplay Ability System</b> (GAS) `AttributeSet` created in Blueprint without having to write additional C++ code or restart the editor.
The plugin works exclusively at the Unreal Engine Editor level and does not add game logic or new data types.

The main goal of creating <b>EasyGas</b> is to unlock the potential of GAS at the Blueprints level without diving into the C++ API.
If the plugin proves to be in demand, We plan to develop it further. I have many ideas for creating tools for developers and game designers that will help speed up prototyping and development at the Blueprints level.

# Table of content
- [How to Install](#How-to-Install)
- [How to Use](#How-to-Use)
- [Settings](#Settings)
- [How it works](#How-it-works)
- [Contact](#Contact)

# How to Install
To install <b>EasyGas</b>, clone the [EasyGas](https://github.com/YuriyAgapov/EasyGas.git) repository or download the [ZIP archive](https://github.com/YuriyAgapov/EasyGasPlugin/archive/refs/heads/main.zip) and unpack into your project's `Plugins` directory.

# How to Use
To work with GAS attributes, it is now sufficient to create an `AttributeSet` with the necessary attributes (`GameplayAttributeData`) and compile it.

![AttributeSet](./Docs/AttributeSet.png "Custom AttributeSet")

After that, the attributes from it will become available for selection when editing variable values:

![DetailsView](./Docs/DetailsView.png "DetailsView")

When editing the pin value in EventGraph (short format is used, configured in settings):

![EventGraph](./Docs/EventGraph.png "Custom AttributeSet")

When editing modifiers in GE (example of implementing the gameplay effect ‘damage over time’):

![GE_DoT](./Docs/GE_DoT.png "Damage over time")

⚠️Warning: Due to the implementation of GameplayAttribute, it may not be safe to delete an AttributeSet that is used somewhere. I plan to add tools for safely deleting and renaming attributes and AttributeSets in future updates.

<i>Note</i>: <b>EasyGas</b> tries to use different colours for different `AttributeSet`'s to visually separate them

# Settings
The plugin has settings (Project -> Plugins -> EasyGas):
* Use Easy Gas Editor - allows to return to the standard attribute editors without restarting the editor (you will need to reopen or recompile the asset for the editor to update its UI)

| ✔ Enabled |  | Disabled |
| --- | --- | --- |
| ![Enable](./Docs/EasyGasDefaultView.png) | <-> | ![Disabled](./Docs/UseEasyGasDisabled.png) |

* Hide Generated Class Suffix - hides the '_C' suffix for generated classes when displaying attributes

| Enabled |  | ✔ Disabled |
| --- | --- | --- |
| ![Enable](./Docs/HideGenClassSuffixEnabled.png) | <-> | ![Disabled](./Docs/EasyGasDefaultView.png) |

* Hide Class in Pins - hides the AttributeSet name when displayed in EventGraph to make nodes more compact

| Enabled |  | ✔ Disabled |
| --- | --- | --- |
| ![Enable](./Docs/HideClassPinsEnabled.png) | <-> | ![Disabled](./Docs/HideClassPinsDisabled.png) |

# How it works
<b>EasyGas</b> operates at the Unreal Engine Editor level, replacing the GAS's attribute editors with its own.

The plugin allows to select attributes from the generated `AttributeSet` and `AbilitySystemComponent` classes.
When changes are made to these classes, <b>EasyGas</b> will attempt to preserve references to their attributes. The exception is when attributes have been renamed or removed from `AttributeSet`.

Note: Even with <b>EasyGas</b> installed, you can always revert to the standard GAS editors without rebooting by disabling the plugin in the settings (Project -> Plugins -> EasyGas). 

⚠️Warning: Please note, the "Hide Generated Class Suffix" setting hides the '_C' suffix only when displayed in <b>EasyGas</b> widgets, this is done solely for convenience. In `DataTable`, you must write the full name of the generated class and the attribute name - 'BP_MyAttributeSet_C.MyAttribute'. For your convenience, in the context menu of <b>EasyGas</b> widgets there is a "Copy Path" item, which allows you to copy the path to the attribute to the clipboard.

# Contact
Email: agapov.yi@gmail.com

Welcome any feedback!