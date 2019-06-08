#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Materials/MaterialInterface.h"

#include "GameBaseEditorFunctionLibrary.generated.h"

UCLASS(BlueprintType)
class GAMEBASEEDITOR_API UGameBaseEditorFunctionLibrary 
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "GameBase|Editor")
	static UWorld* GetPIEWorld();

	UFUNCTION(BlueprintCallable, Category = "GameBase|Editor")
	static UMaterialFunctionInterface* ConvertMaterialToMaterialFunction(UMaterial* InSourceMaterial);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Editor")
	static FString GetPackageName(UObject* InObject);

	UFUNCTION(BlueprintCallable, Category = "GameBase|Editor", meta = (DisplayName = "GetPackageName"))
	static FString GetPackageName_Split(UObject* InObject, FString& OutPath, FString& OutFileName);

	template <typename TObject>
	static TObject* CreateAsset(TObject* InObject, FName InPath, bool bOverwrite = true)
	{
		check(InObject);
		check(InObject->GetClass()->IsChildOf(UObject::StaticClass()));

		// #todo Check if InPath is a valid path
		auto Package = CreatePackage(nullptr, *InPath.ToString());
		auto Asset = DuplicateObject(InObject, Package);

		FAssetRegistryModule::AssetCreated(Asset);

		Asset->MarkPackageDirty();

		return Cast<TObject>(Asset);
	}
};
