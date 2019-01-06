#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractorInterface.h"

#include "LineCastInteractor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEBASE_API ULineCastInteractor 
	: public UActorComponent,
	public IInteractorInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interactor", meta = (Absolute))
	float Range;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interactor")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	ULineCastInteractor();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool TestInteract_Implementation(TScriptInterface<IInteractableInterface>& Interactable) override;
	bool TryInteract_Implementation(TScriptInterface<IInteractableInterface>& Interactable) override;
	bool GetTransform_Implementation(FVector& Location, FRotator& Rotation, FVector& Direction) const override;
	/*bool TestInteract_Implementation() override;
	bool TryInteract_Implementation() override;
	FVector GetTraceOrigin_Implementation() override;*/

private:
	APlayerController* GetPlayerController() const;

	bool DoLineTrace(TFunction<bool(FHitResult&)> Func, TScriptInterface<IInteractableInterface>& Interactable);
};
