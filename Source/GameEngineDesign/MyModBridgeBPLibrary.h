#pragma once
// Ensures the file is only included once by the compiler during a build

#include "CoreMinimal.h"
// Gives access to all of Unreal's core types (FString, UObject, logging, etc.)

#include "Kismet/BlueprintFunctionLibrary.h"
// Allows us to make a static function library that can expose C++ functions to Blueprints

#include "MyModBridgeBPLibrary.generated.h"
// Required by Unreal Header Tool (UHT). Must always be the last include in a UCLASS header.


// Declare a new Blueprint Function Library class
UCLASS()
class GAMEENGINEDESIGN_API UMyModBridgeBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    // Expands to boilerplate code Unreal needs to support reflection and Blueprints.

public:
    // Blueprint-callable function to load the DLL into memory.
    // Returns true if loaded successfully, false otherwise.
    UFUNCTION(BlueprintCallable, Category = "MyMod|DLL")
    static bool LoadMyModDLL();

    // Blueprint-callable function to set the preferred language inside the DLL.
    // Example: SetPreferredLanguage("fr")
    UFUNCTION(BlueprintCallable, Category = "MyMod|Language", DisplayName = "MyMod Set Preferred Language")
    static void SetPreferredLanguage(const FString& LangCode);

    // Blueprint-callable function to get the currently stored preferred language from the DLL.
    // Example: returns "fr" after the above call.
    UFUNCTION(BlueprintCallable, Category = "MyMod|Language", DisplayName = "MyMod Get Preferred Language")
    static FString GetPreferredLanguage();

    // Blueprint-pure function (doesn’t need exec pin) to scale a speed value by a multiplier using the DLL.
    // Example: ScaleSpeed(600, 1.5) → 900
    UFUNCTION(BlueprintPure, Category = "MyMod|Gameplay", DisplayName = "MyMod Scale Speed")
    static float ScaleSpeed(float BaseSpeed, float Multiplier);

private:
    // Handle to the loaded DLL in memory (returned by FPlatformProcess::GetDllHandle).
    static void* DllHandle;

    // Typedefs for the function signatures we expect inside the DLL.
    // These mirror the exported C functions in MyMod.dll.
    typedef void        (*SetLangFn)(const char*);        // Sets the language
    typedef const char* (*GetLangFn)();                   // Gets the language
    typedef float       (*ScaleSpeedFn)(float, float);     // Scales a float

    // Function pointers we’ll assign when the DLL is loaded.
    static SetLangFn    pSetLang;
    static GetLangFn    pGetLang;
    static ScaleSpeedFn pScaleSpeed;
};
