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
	TArray<AShipModule*> AttachedModules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<AShipModule*> ConnectedModules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	AShipModule* RootModule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float Funds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float Income;

	// Orders from planning stored in ship?
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	//TArray<FST_Order> Orders;

	UFUNCTION(BlueprintCallable, Category = "Ship")
	AShipModule* AddModule(AShipModule* Module);

	UFUNCTION(BlueprintCallable, Category = "Ship")
	AShipModule* AddModuleOfClass(TSubclassOf<class AShipModule> ModuleClass, FVector WorldLocation, FRotator WorldRotation);

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
