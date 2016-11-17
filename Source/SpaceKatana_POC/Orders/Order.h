// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DataHolder.h"
#include "Order.generated.h"


//~~~~~ FORWARD DECLATIONS ~~~~~//
class AShip;



UCLASS(Blueprintable, BlueprintType)
class SPACEKATANA_POC_API UOrder : public UObject
{
	GENERATED_BODY()

public:
	UOrder();
	~UOrder();

	AShip* Buyer;

	float Cost;

	int TurnExcTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int TurnsLeft;

	int X;

	int Y;

	FVector OrderLocation;

	//EResource CostType;


	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	//AShipModule* StoredShipModule;

	//UFUNCTION(BlueprintCallable, Category = Grid)
	//bool RegisterOnTile(AShipModule* ShipModule);

};
