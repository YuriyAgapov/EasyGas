// Copyright 2025 Yuriy Agapov, All Rights Reserved.

using UnrealBuildTool;

public class EasyGasCore : ModuleRules
{
	public EasyGasCore(ReadOnlyTargetRules Target) : base(Target)
	{
		bUsePrecompiled = true;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Projects",
			"ApplicationCore",
			"GameplayAbilities",
		});
	}
}