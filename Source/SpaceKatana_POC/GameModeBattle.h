// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "DataHolder.h"
#include "GameModeBattle.generated.h"



//~~~~~ FORWARD DECLATIONS ~~~~~//
class AShip;
class AShipModule;
class UGridTile;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float GridTileSize;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<UGridTile*> GridTiles;
	//TArray<FST_GridTile> GridTiles;

	UFUNCTION(BlueprintCallable, Category = Grid)
	void ConstructGrid();

	UFUNCTION(BlueprintCallable, Category = Grid)
	FVector CoordsToWorldLocation(int X, int Y);

	UFUNCTION(BlueprintCallable, Category = Grid)
	FVector2D WorldLocationToCoords(FVector WorldLocation, bool bRoundOutOfBounds);


	//struct FST_GridTile& GetGridTile(FVector WorldLocation);
	UFUNCTION(BlueprintCallable, Category = Grid)
	UGridTile* GetGridTile(FVector WorldLocation, bool bRoundOutOfBounds);
	//void GetGridTile(UPARAM(ref) FST_GridTile& GridTile, FVector WorldLocation);

	UFUNCTION(BlueprintCallable, Category = Grid)
	AShipModule* SpawnFlyInModule(TSubclassOf<class AShipModule> ModuleClass, int X, int Y, AShip* Buyer);

	bool IsValidShipLocation(AShip* Ship, FVector WorldLocation);



};

