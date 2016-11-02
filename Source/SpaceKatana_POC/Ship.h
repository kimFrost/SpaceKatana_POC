// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ShipModule.h"
#include "Ship.generated.h"

UCLASS()
class SPACEKATANA_POC_API AShip : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<AShipModule*> Modules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	AShipModule* RootModule;

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void UpdateModules();

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void UpdateConnections();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
};
