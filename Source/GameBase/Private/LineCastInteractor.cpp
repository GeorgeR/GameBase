#include "LineCastInteractor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "InteractableInterface.h"
#include "GameBaseFunctionLibrary.h"

ULineCastInteractor::ULineCastInteractor()
{
	PrimaryComponentTick.bCanEverTick = true;

	Range = 1000.0f;
}

void ULineCastInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IInteractorInterface::Execute_TestInteract(this);
}

bool ULineCastInteractor::TestInteract_Implementation()
{
	FVector Location;
	FRotator Rotation;
	GetPlayerController()->PlayerCameraManager->GetCameraViewPoint(Location, Rotation);
	const auto Direction = Rotation.Vector();

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + (Direction * Range), ECollisionChannel::ECC_Visibility))
	{
		UObject* InterfaceObject;
		const auto Interactable = UGameBaseFunctionLibrary::GetActorOrComponent<IInteractableInterface>(HitResult.GetActor(), InterfaceObject);
		if (Interactable == nullptr)
			return false;

		IInteractableInterface::Execute_TestInteract(InterfaceObject, this);
		return true;
	}

	return false;
}

bool ULineCastInteractor::TryInteract_Implementation()
{
	FVector Location;
	FRotator Rotation;
	GetPlayerController()->PlayerCameraManager->GetCameraViewPoint(Location, Rotation);
	const auto Direction = Rotation.Vector();

	FHitResult HitResult;
	if(GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + (Direction * Range), ECollisionChannel::ECC_Visibility))
	{
		UObject* InterfaceObject;
		const auto Interactable = UGameBaseFunctionLibrary::GetActorOrComponent<IInteractableInterface>(HitResult.GetActor(), InterfaceObject);
		if (Interactable == nullptr)
			return false;

		if (IInteractableInterface::Execute_CanInteract(InterfaceObject, this))
		{
			IInteractableInterface::Execute_Interact(InterfaceObject, this);
			return true;
		}
	}

	return false;
}

FVector ULineCastInteractor::GetTraceOrigin_Implementation()
{
	FVector Location;
	FRotator Rotation;
	GetPlayerController()->PlayerCameraManager->GetCameraViewPoint(Location, Rotation);

	return Location;
}

APlayerController* ULineCastInteractor::GetPlayerController() const
{
	return Cast<APlayerController>(Cast<APawn>(GetOuter())->GetController());
}
