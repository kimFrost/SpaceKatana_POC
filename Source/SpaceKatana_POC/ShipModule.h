// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ShipModuleConnector.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	bool bIsRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	bool bIsConnectedToRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	bool bHasBeenUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int DistanceFromRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<AShipModuleConnector*> Connectors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<AShipModule*> ConnectedTo;

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void UpdateConnections();

	// Flood fill from Core

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
