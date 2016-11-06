// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "ShipModule.h"
#include "GridTile.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPACEKATANA_POC_API UGridTile : public UObject
{
	GENERATED_BODY()
	
public:
	UGridTile();
	~UGridTile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	AShipModule* ShipModule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FVector WorldLocation;
};
