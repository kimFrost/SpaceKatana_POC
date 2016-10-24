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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connector")
	AShipModuleConnector* BoundTo;
	
	UFUNCTION(BlueprintCallable, Category = "Data")
	void Join(AShipModuleConnector* ConnectTo, bool bUpdateTransform, bool bUpdateOther);


};
