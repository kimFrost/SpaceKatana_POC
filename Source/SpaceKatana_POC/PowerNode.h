// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "PowerNode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPACEKATANA_POC_API UPowerNode : public UObject
{
	GENERATED_BODY()

public:
	UPowerNode();
	~UPowerNode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	bool bIsAllocated;
	
};
