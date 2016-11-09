// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "ShipModule.h"
#include "GridTile.h"





UGridTile::UGridTile()
{
	StoredShipModule = nullptr;
	Column = -1;
	Row = -1;
	WorldLocation = FVector{0.f, 0.f, 0.f};
	bDebugMe = false;
}


UGridTile::~UGridTile()
{

}