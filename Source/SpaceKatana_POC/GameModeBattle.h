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


//~~~~~ Delegates/Event dispatcher ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndTurn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewTurn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepChange, ETurnStep, NewStep);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTimeUpdated, float, Time, float, TimeProgressed);


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

	// VARIABLES - TIME 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float PlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float PlayingLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float PlaningLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float TurnTimeLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	bool bPlayerOneReady;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	bool bPlayerTwoReady;


	// FUNCTIONS

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

	UFUNCTION(BlueprintCallable, Category = Turn)
	void SetPlayRate(float TimeRate, float DilationRate);

	UFUNCTION(BlueprintCallable, Category = Turn)
	void EndTurn(int ShipIndex);

	UFUNCTION(BlueprintCallable, Category = Turn)
	void NewTurn();

	UFUNCTION(BlueprintCallable, Category = Turn)
	void ProgressTime(float Amount);


	//struct FST_GridTile& GetGridTile(FVector WorldLocation);
	UFUNCTION(BlueprintCallable, Category = Grid)
	UGridTile* GetGridTile(FVector WorldLocation, bool bRoundOutOfBounds);
	//void GetGridTile(UPARAM(ref) FST_GridTile& GridTile, FVector WorldLocation);

	UFUNCTION(BlueprintCallable, Category = Grid)
	AShipModule* SpawnFlyInModule(TSubclassOf<class AShipModule> ModuleClass, int X, int Y, FVector Direction, FVector Target, AShip* Buyer);

	UFUNCTION(BlueprintCallable, Category = Grid)
	bool IsValidShipLocation(AShip* Ship, FVector WorldLocation);




	//DELEGATES

	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnEndTurn OnEndTurn;

	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnNewTurn OnNewTurn;

	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnStepChange OnStepChange;

	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnTimeUpdated OnTimeUpdated;


	//OVERRIDES

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};

