#include "DamageDealerInterface.h"

UDamageDealerInterface::UDamageDealerInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) { }

FName IDamageDealerInterface::GetName() { return TEXT(""); }

int32 IDamageDealerInterface::GetTeamName() { return 0; }