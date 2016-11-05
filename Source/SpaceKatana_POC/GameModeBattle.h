// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "DataHolder.h"
#include "GameModeBattle.generated.h"



//~~~~~ FORWARD DECLATIONS ~~~~~//
class AShip;
class AShipModule;


UCLASS()
class SPACEKATANA_POC_API AGameModeBattle : public AGameMode
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AGameModeBattle(const FObjectInitializer &ObjectInitializer);
	

	//Grid

	int GridSizeX;
	int GridSizeY;
	float GridTileSize;

	TArray<FST_GridTile> GridTiles;

	void ConstructGrid();

	//struct FST_GridTile& GetGridTile(FVector WorldLocation);
	UFUNCTION(BlueprintCallable, Category = Grid)
	void GetGridTile(UPARAM(ref) FST_GridTile& GridTile, FVector WorldLocation);


	bool IsValidShipLocation(AShip* Ship, FVector WorldLocation);

	bool RegisterOnTile(AShipModule* ShipModule);




};

