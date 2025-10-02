// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class GameEngineDesign : ModuleRules
{
	public GameEngineDesign(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine" });

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDelayLoadDLLs.Add("MyMod.dll");

            // Project module example:
            string ProjectDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../"));
            string DllSource = Path.Combine(ProjectDir, "Binaries", "Win64", "MyMod.dll");

            // Plugin module example:
            // string PluginDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "../.."));
            // string DllSource = Path.Combine(PluginDir, "ThirdParty", "MyMod", "Win64", "MyMod.dll");

            if (File.Exists(DllSource))
            {
                RuntimeDependencies.Add("$(TargetOutputDir)/MyMod.dll", DllSource);
            }
            else
            {
                System.Console.WriteLine("WARNING: MyMod.dll not found at " + DllSource + " — skipping staging.");
            }
        }
    }
}
