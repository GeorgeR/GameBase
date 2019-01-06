#include "LineCastInteractor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "InteractableInterface.h"

ULineCastInteractor::ULineCastInteractor()
{
	PrimaryComponentTick.bCanEverTick = true;

	Range = 400.0f;
}

void ULineCastInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TScriptInterface<IInteractableInterface> Interactable;
	TestInteract(Interactable);
}

bool ULineCastInteractor::TestInteract_Implementation(TScriptInterface<IInteractableInterface>& Interactable)
{
	return DoLineTrace([this, &Interactable](FHitResult& HitResult) -> bool {
		if (Interactable->CanInteract(this))
			Interactable->Interact(this);

		return true;
	}, Interactable);
}

bool ULineCastInteractor::TryInteract_Implementation(TScriptInterface<IInteractableInterface>& Interactable)
{
	return DoLineTrace([this, &Interactable](FHitResult& HitResult) -> bool {
		return Interactable->TestInteract(this);
	}, Interactable);
}

bool ULineCastInteractor::GetTransform_Implementation(FVector& Location, FRotator& Rotation, FVector& Direction) const
{
	auto PlayerController = GetPlayerController();

	if (PlayerController != nullptr)
	{
		GetPlayerController()->PlayerCameraManager->GetCameraViewPoint(Location, Rotation);
		Direction = Rotation.Vector();

		return true;
	}

	return false;
}

APlayerController* ULineCastInteractor::GetPlayerController() const
{
	return Cast<APlayerController>(Cast<APawn>(GetOuter())->GetController());
}

bool ULineCastInteractor::DoLineTrace(TFunction<bool(FHitResult&)> Func, TScriptInterface<IInteractableInterface>& Interactable)
{
	FVector Location;
	FRotator Rotation;
	FVector Direction;
	if (!GetTransform(Location, Rotation, Direction))
		return nullptr;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + (Direction * Range), CollisionChannel))
	{
		/*UObject* InterfaceObject;
		Interactable = nullptr;*/
		// TODO
		//Interactable = UGameBaseFunctionLibrary::GetActorOrComponent<IInteractableInterface>(HitResult.GetActor(), InterfaceObject);
		if (Interactable == nullptr)
			return false;

		return Func(HitResult);
	}

	return false;
}
