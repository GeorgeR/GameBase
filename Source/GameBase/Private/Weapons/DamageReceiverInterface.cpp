#include "DamageReceiverInterface.h"

UDamageReceiverInterface::UDamageReceiverInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) { }

void IDamageReceiverInterface::ApplyDamage(const FDamageHit& InHit) { }

int32 IDamageReceiverInterface::GetHitPoints(uint8 InPart) { return -1; }

int32 IDamageReceiverInterface::GetMaxHitPoints(uint8 InPart) { return -1; }

int32 IDamageReceiverInterface::GetArmorPoints(uint8 InPart) { return -1; }

int32 IDamageReceiverInterface::GetMaxArmorPoints(uint8 InPart) { return -1; }

bool IDamageReceiverInterface::IsDestroyed() { return GetHitPoints() <= 0; }

void IDamageReceiverInterface::Suicide() { }