// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "ShipModule.generated.h"

UCLASS()
class SPACEKATANA_POC_API AShipModule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipModule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float MaxHealth;

	// Connections

	// Flood fill from Core
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void UpdateConnected();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
