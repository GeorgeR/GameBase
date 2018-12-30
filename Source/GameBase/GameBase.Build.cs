using UnrealBuildTool;

public class GameBase : ModuleRules
{
	public GameBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        /* Use Gameplay Abilities */
        PublicDefinitions.Add("WITH_ABILITIES=1");

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

        if (PublicDefinitions.Contains("WITH_ABILITIES=1"))
        {
            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "GameplayAbilities"
                });
        }

        if (Target.bBuildEditor == true)
	        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "ContentBrowser" });
    }
}
