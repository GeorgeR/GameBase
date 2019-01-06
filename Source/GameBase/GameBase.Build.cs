using UnrealBuildTool;

public class GameBase : ModuleRules
{
	public GameBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        if (Target.Version.MinorVersion <= 19)
	    {
            PublicIncludePaths.AddRange(
			    new string[] {
				    "GameBase/Public"
			    });

		    PrivateIncludePaths.AddRange(
			    new string[] {
				    "GameBase/Private",
			    });
        }

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			});

        if (Target.bBuildEditor == true)
	        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "ContentBrowser" });
    }
}
