// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "ShipModule.h"
#include "Orders/Order.h"
#include "Ship.generated.h"

//~~~~~ Delegates/Event dispatcher ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourcesUpdated);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourcesUpdated, AShipModule*, Module);


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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	float PowerMaxStorage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	float PowerAvailable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	float PowerUpkeep;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resources")
	TArray<UOrder*> OrderQue;

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

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void ParseProduction();

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void ParseStorage();

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void ParseUpkeep();


	UPROPERTY(BlueprintAssignable, Category = "Order")
	FOnResourcesUpdated OnResourcesUpdated;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	

};
