// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "ShipModule.h"
#include "GridTile.h"





UGridTile::UGridTile()
{
	ShipModule = nullptr;
	Column = -1;
	Row = -1;
	WorldLocation = FVector{0.f, 0.f, 0.f};

}


UGridTile::~UGridTile()
{

}