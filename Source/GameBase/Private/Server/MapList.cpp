#include "MapList.h"

FMapList::FMapList()
	: CurrentMapIndex(0)
{
	Order = EMapOrder::MO_InOrder;

	MapNames = {TEXT("/Game/Empires/Maps/TestMap")};
}

FName FMapList::GetNextMap()
{
	// TODO
	return MapNames[0];
}

void FMapList::ResolveMapPaths()
{
	// TODO
	MapPaths = MapNames;
}