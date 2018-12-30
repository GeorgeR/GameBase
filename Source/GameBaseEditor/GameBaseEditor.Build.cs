using UnrealBuildTool;

public class GameBaseEditor : ModuleRules
{
	public GameBaseEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

	    if (Target.Version.MinorVersion <= 19)
	    {
            PublicIncludePaths.AddRange(
			    new string[] {
				    "GameBaseEditor/Public"
			    });

		    PrivateIncludePaths.AddRange(
			    new string[] {
				    "GameBaseEditor/Private",
			    });
        }

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "AssetRegistry",
                "CoreUObject",
				"Engine",
                "MaterialEditor",
				"Slate",
				"SlateCore",
				"UnrealEd"
			});
    }
}