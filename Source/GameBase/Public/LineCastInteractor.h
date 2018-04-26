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
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Range;

	ULineCastInteractor();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool TestInteract_Implementation() override;
	bool TryInteract_Implementation() override;
	FVector GetTraceOrigin_Implementation() override;

private:
	APlayerController* GetPlayerController() const;
};