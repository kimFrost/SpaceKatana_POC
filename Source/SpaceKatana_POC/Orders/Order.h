// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DataHolder.h"
#include "Order.generated.h"


//~~~~~ FORWARD DECLATIONS ~~~~~//
class AShip;
class AShipModule;

//~~~~~ Delegates/Event dispatcher ~~~~~//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTimeUpdated, float, Time, float, TimeProgressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOrderResolved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOrderCancelled);
//DECLARE_DYNAMIC_DELEGATE(FOrderResolved);
//DECLARE_EVENT_OneParam( UActionManager, FEventSignature, AActor* )
//DECLARE_EVENT(FOrderResolved, EventName)


UCLASS(Blueprintable, BlueprintType)
class SPACEKATANA_POC_API UOrder : public UObject
{
	GENERATED_BODY()

public:
	UOrder();
	~UOrder();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	AShip* Buyer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	AShipModule* Module;

	float PowerCost;

	float PRCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	bool bIsResolved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	bool bIsCancelled;

	int TurnExcTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int TurnsLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int Z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	FVector OrderLocation;

	//EResource CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	UWorld* WorldRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Order")
	int Sequence;



	UFUNCTION(BlueprintCallable, Category = "Order")
	virtual void ResolveOrder();

	UFUNCTION(BlueprintCallable, Category = "Order")
	virtual void CancelOrder();

	UPROPERTY(BlueprintAssignable, Category = "Order")
	FOrderResolved OnOrderResolved;

	UPROPERTY(BlueprintAssignable, Category = "Order")
	FOrderCancelled OnOrderCancelled;
	
};
