#include "TargetPointComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BillboardComponent.h"

UTargetPointComponent::UTargetPointComponent()
{
#if WITH_EDITORONLY_DATA
	Sprite = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));

	ConstructorHelpers::FObjectFinder<UTexture2D> SpriteFinder(TEXT("/Engine/EditorMaterials/TargetIcon"));
	if (SpriteFinder.Succeeded())
		Sprite->Sprite = SpriteFinder.Object;

	Sprite->RelativeScale3D = FVector(0.35f, 0.35f, 0.35f);
	Sprite->SpriteInfo.Category = TEXT("TargetPoint");
	Sprite->bIsScreenSizeScaled = true;
	Sprite->SetupAttachment(this);
#endif

	bHiddenInGame = true;
}