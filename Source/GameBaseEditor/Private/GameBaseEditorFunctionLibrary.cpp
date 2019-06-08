#include "GameBaseEditorFunctionLibrary.h"

#include "Editor.h"
#include "Materials/Material.h"
#include "Materials/MaterialFunction.h"
#include "Materials/MaterialFunctionInterface.h"
#include "Materials/MaterialExpressionMakeMaterialAttributes.h"
#include "Materials/MaterialInstance.h"
#include "MaterialEditingLibrary.h"
#include "Paths.h"
#include "Materials/MaterialExpressionFunctionOutput.h"
#include "Engine/Engine.h"

UWorld* UGameBaseEditorFunctionLibrary::GetPIEWorld()
{
	return GEditor->GetEditorWorldContext().World();
}

/* NOTE: Incomplete */
UMaterialFunctionInterface* UGameBaseEditorFunctionLibrary::ConvertMaterialToMaterialFunction(UMaterial* InSourceMaterial)
{
	check(InSourceMaterial);

	// #todo Iterate over base Node and get all inputs
	auto AmbientOcclusion = InSourceMaterial->AmbientOcclusion;
	auto BaseColor = InSourceMaterial->BaseColor;
	auto ClearCoat = InSourceMaterial->ClearCoat;
	auto ClearCoatRoughness = InSourceMaterial->ClearCoatRoughness;
	auto CustomizedUVs = InSourceMaterial->CustomizedUVs;
	auto EmissiveColor = InSourceMaterial->EmissiveColor;
	auto Metallic = InSourceMaterial->Metallic;
	auto Normal = InSourceMaterial->Normal;
	auto Opacity = InSourceMaterial->Opacity;
	auto OpacityMask = InSourceMaterial->OpacityMask;
	auto PixelDepthOffset = InSourceMaterial->PixelDepthOffset;
	auto Refraction = InSourceMaterial->Refraction;
	auto Roughness = InSourceMaterial->Roughness;
	auto Specular = InSourceMaterial->Specular;
	auto SubsurfaceColor = InSourceMaterial->SubsurfaceColor;
	auto TessellationMultiplier = InSourceMaterial->TessellationMultiplier;
	auto WorldDisplacement = InSourceMaterial->WorldDisplacement;
	auto WorldPositionOffset = InSourceMaterial->WorldPositionOffset;

	FString Path;
	FString FileName;
	GetPackageName_Split(InSourceMaterial, Path, FileName);

	auto PackageName = Path + "MF_" + FileName;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *PackageName);
	
	auto Package = CreatePackage(nullptr, *PackageName);

	auto DestinationFunction = NewObject<UMaterialFunction>(Package, FName(*FileName), EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);

	auto MakeMaterialAttributesExpression = Cast<UMaterialExpressionMakeMaterialAttributes>(UMaterialEditingLibrary::CreateMaterialExpressionInFunction(DestinationFunction, UMaterialExpressionMakeMaterialAttributes::StaticClass()));
	MakeMaterialAttributesExpression->AmbientOcclusion = AmbientOcclusion;
	MakeMaterialAttributesExpression->BaseColor = BaseColor;
	MakeMaterialAttributesExpression->ClearCoat = ClearCoat;
	MakeMaterialAttributesExpression->ClearCoatRoughness = ClearCoatRoughness;
	//MakeMaterialAttributesExpression->CustomizedUVs = CustomizedUVs;
	MakeMaterialAttributesExpression->EmissiveColor = EmissiveColor;
	MakeMaterialAttributesExpression->Metallic = Metallic;
	MakeMaterialAttributesExpression->Normal = Normal;
	MakeMaterialAttributesExpression->Opacity = Opacity;
	MakeMaterialAttributesExpression->OpacityMask = OpacityMask;
	MakeMaterialAttributesExpression->PixelDepthOffset = PixelDepthOffset;
	MakeMaterialAttributesExpression->Refraction = Refraction;
	MakeMaterialAttributesExpression->Roughness = Roughness;
	MakeMaterialAttributesExpression->Specular = Specular;
	MakeMaterialAttributesExpression->SubsurfaceColor = SubsurfaceColor;
	MakeMaterialAttributesExpression->TessellationMultiplier = TessellationMultiplier;
	MakeMaterialAttributesExpression->WorldDisplacement = WorldDisplacement;
	MakeMaterialAttributesExpression->WorldPositionOffset = WorldPositionOffset;

	auto OutputExpression = Cast<UMaterialExpressionFunctionOutput>(UMaterialEditingLibrary::CreateMaterialExpressionInFunction(DestinationFunction, UMaterialExpressionFunctionOutput::StaticClass()));

	OutputExpression->GetInput(0)->Connect(0, MakeMaterialAttributesExpression);
	
	UMaterialEditingLibrary::UpdateMaterialFunction(DestinationFunction);

	DestinationFunction->MarkPackageDirty();

	auto FilePath = PackageName.Replace(TEXT("/Game/"), *FPaths::ProjectContentDir()) + *FPackageName::GetAssetPackageExtension();
	// BUG: This crashes here "Graph is linked to private object(s) in an external package."
	//bool bSuccess = UPackage::SavePackage(Package, DestinationFunction, EObjectFlags::RF_Standalone, *FilePath);

	return DestinationFunction;
}

FString UGameBaseEditorFunctionLibrary::GetPackageName(UObject* InObject)
{
	FString Path;
	FString FileName;

	return GetPackageName_Split(InObject, Path, FileName);
}

FString UGameBaseEditorFunctionLibrary::GetPackageName_Split(UObject* InObject, FString& OutPath, FString& OutFileName)
{
	auto FullPathName = InObject->GetFullName(nullptr);
	auto PathName = FPaths::GetPath(FullPathName);
	auto FileName = FPaths::GetBaseFilename(FullPathName);

	FString Left;
	FString Right;
	if (PathName.Split(TEXT(" "), &Left, &Right))
		PathName = Right;

	//if (PathName.StartsWith(TEXT("/Game/")))
	//	PathName = PathName.Replace(TEXT("/Game/"), *FPaths::ProjectContentDir());

	OutPath = PathName + "/";
	OutFileName = FileName;

	return OutPath + OutFileName;
}
