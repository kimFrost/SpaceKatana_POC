// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DataHolder.h"
#include "Order.generated.h"


//~~~~~ FORWARD DECLATIONS ~~~~~//
//class AShip;



UCLASS()
class SPACEKATANA_POC_API UOrder : public UObject
{
	GENERATED_BODY()

public:
	UOrder();
	~UOrder();

	//AShip* Commander;

	//float Cost;

	//EResource CostType;

	//int TurnExcTime;

	//int TurnsLeft;

	//FVector OrderLocation;


	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	//AShipModule* StoredShipModule;

	//UFUNCTION(BlueprintCallable, Category = Grid)
	//bool RegisterOnTile(AShipModule* ShipModule);

};
