// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Orders/Order.h"
#include "DataHolder.h"
#include "OrderSpawnModule.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPACEKATANA_POC_API UOrderSpawnModule : public UOrder
{
	GENERATED_BODY()
	
public:
	UOrderSpawnModule();
	~UOrderSpawnModule();

	TSubclassOf<class AShipModule> ModuleClassToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	FVector FlyInDirection;


};
