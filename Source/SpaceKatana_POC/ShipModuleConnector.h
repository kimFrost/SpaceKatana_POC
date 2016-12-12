// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ShipModuleConnector.generated.h"

UCLASS()
class SPACEKATANA_POC_API AShipModuleConnector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipModuleConnector();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connector")
	AShipModuleConnector* BoundTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connector")
	bool bIsHazard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connector")
	bool bIsConnectable;

	UFUNCTION(BlueprintCallable, Category = "Data")
	void Join(AShipModuleConnector* ConnectTo, bool bUpdateTransform, bool bUpdateOther);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

};
