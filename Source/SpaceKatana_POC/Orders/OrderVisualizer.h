// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DataHolder.h"
#include "Order.h"
#include "OrderVisualizer.generated.h"

UCLASS()
class SPACEKATANA_POC_API AOrderVisualizer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrderVisualizer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	EOrderType OrderType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	UOrder* Order;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
