// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Orders/Order.h"
#include "DataHolder.h"
#include "OrderSpawnModule.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPACEKATANA_POC_API UOrderSpawnModule : public UOrder
{
	GENERATED_BODY()
	
public:
	UOrderSpawnModule();
	~UOrderSpawnModule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	TSubclassOf<class AShipModule> ModuleClassToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	AShipModule* SpawnedModule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	AShipModule* PlaceholderModule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	FVector FlyInDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	FVector TracedTargetLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	FVector TracedTargetConnectorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int TracedTargetX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int TracedTargetY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	bool bModuleCollisionDanger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	bool bValidAttachHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	TArray<FVector> DEBUG_TracedLocations;


	UFUNCTION(BlueprintCallable, Category = "Order")
	void SpawnModule();

	UFUNCTION(BlueprintCallable, Category = "Order")
	void SpawnPlaceholderModule();

	UFUNCTION(BlueprintCallable, Category = "Order")
	void TraceProjection();


private:
	// Called when the order gets resolved
	virtual void ResolveOrder() override;


};
