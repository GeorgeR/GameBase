#pragma once

#include "CoreMinimal.h"
#include "TreeNodeInterface.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UTreeNodeInterface
	: public UInterface
{
	GENERATED_BODY()
};

class GAMEBASE_API ITreeNodeInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual void GetChildren(TArray<TScriptInterface<ITreeNodeInterface>>& OutChildren) { }

	UFUNCTION(BlueprintCallable, Category = "GameBase")
	virtual int32 GetChildCount() { return -1; }
};