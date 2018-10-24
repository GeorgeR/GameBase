using UnrealBuildTool;

public class GameBase : ModuleRules
{
	public GameBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			});

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			});

	    if (Target.bBuildEditor == true)
	        PrivateDependencyModuleNames.AddRange(
	            new string[]
	            {
	                "UnrealEd",
	                "ContentBrowser"
	            });
    }
}