// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "DataHolder.h"
#include "GameModeBattle.generated.h"



//~~~~~ FORWARD DECLATIONS ~~~~~//
class AShip;
class AShipModule;
class UGridTile;
class UOrder;


UCLASS()
class SPACEKATANA_POC_API AGameModeBattle : public AGameMode
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AGameModeBattle(const FObjectInitializer &ObjectInitializer);
	
	// Settings


	//Grid

	int GridSizeX;
	int GridSizeY;
	int GridSizeZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float GridTileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TArray<UGridTile*> GridTiles;
	//TArray<FST_GridTile> GridTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	ETurnStep CurrentStep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	TArray<UOrder*> Orders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int HighestSequence;

	TSubclassOf<class AOrderVisualizer> OrderVisulizerBlueprint;



	UFUNCTION(BlueprintCallable, Category = "Order")
	UOrderSpawnModule* AddOrder_SpawnModule(TSubclassOf<class AShipModule> ModuleClass, int X, int Z, FVector Direction, AShip* Buyer);

	UFUNCTION(BlueprintCallable, Category = "Order")
	void UpdateOrders(EOrderType OrderType);

	UFUNCTION(BlueprintCallable, Category = Grid)
	void ConstructGrid();

	UFUNCTION(BlueprintCallable, Category = Grid)
	FVector CoordsToWorldLocation(int X, int Y);

	UFUNCTION(BlueprintCallable, Category = Grid)
	FVector WorldLocationToCoords(FVector WorldLocation, bool bRoundOutOfBounds);

	UFUNCTION(BlueprintCallable, Category = Ship)
	void UpdateAllModules();

	UFUNCTION(BlueprintCallable, Category = Turn)
	ETurnStep ProgressTurnStep();

	//struct FST_GridTile& GetGridTile(FVector WorldLocation);
	UFUNCTION(BlueprintCallable, Category = Grid)
	UGridTile* GetGridTile(FVector WorldLocation, bool bRoundOutOfBounds);
	//void GetGridTile(UPARAM(ref) FST_GridTile& GridTile, FVector WorldLocation);

	UFUNCTION(BlueprintCallable, Category = Grid)
	AShipModule* SpawnFlyInModule(TSubclassOf<class AShipModule> ModuleClass, int X, int Y, FVector Direction, FVector Target, AShip* Buyer);

	bool IsValidShipLocation(AShip* Ship, FVector WorldLocation);



};

