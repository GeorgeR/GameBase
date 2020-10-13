#include "TargetPointComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BillboardComponent.h"

UTargetPointComponent::UTargetPointComponent()
{
#if WITH_EDITORONLY_DATA
	Sprite = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));

    if (Sprite)
    {
        ConstructorHelpers::FObjectFinder<UTexture2D> SpriteFinder(TEXT("/Engine/EditorMaterials/TargetIcon"));
        if (SpriteFinder.Succeeded())
            Sprite->Sprite = SpriteFinder.Object;

#if ENGINE_MINOR_VERSION <= 24
        Sprite->RelativeScale3D = FVector(0.35f, 0.35f, 0.35f);
#else
        Sprite->SetRelativeScale3D({ 0.35f, 0.35f, 0.35f });
#endif
        Sprite->SpriteInfo.Category = TEXT("TargetPoint");
        Sprite->bIsScreenSizeScaled = true;
        Sprite->SetupAttachment(this);
    }
#endif

	bHiddenInGame = true;
}