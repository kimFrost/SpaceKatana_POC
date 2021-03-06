// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DataHolder.h"
#include "Orders/OrderSpawnModule.h"
#include "ShipModuleConnector.h"
#include "ShipModule.generated.h"


//~~~~~ Delegates/Event dispatcher ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShipModuleDestroyed, AShipModule*, Module);



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
	EModuleState CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FVector FlyInDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	bool bHasBeenUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	bool bIsDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int DistanceFromRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FVector TargetMoveTo;

	// Ship ref? // No. Just set the location and then the ship will find it though pathing??

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<AShipModuleConnector*> Connectors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<AShipModule*> ConnectedTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<AShipModule*> AttachedTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	UOrderSpawnModule* SpawnOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	UMaterialInstanceDynamic* PlaceholderDynamicMaterialInstance;


	UFUNCTION(BlueprintCallable, Category = "Ship")
	void DestroyModule();

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void UpdateModule();

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void UpdateConnections();

	// Init module function
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ship")
	void InitModule();

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FShipModuleDestroyed OnShipModuleDestroyed;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	
	
};
