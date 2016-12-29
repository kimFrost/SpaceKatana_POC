// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ShipModule.h"
#include "ModuleComponent.generated.h"

//~~ Forward declarations ~~//
//class AShipModule;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEKATANA_POC_API UModuleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UModuleComponent();

	UPROPERTY(BlueprintReadWrite, Category = "Module")
	AShipModule* Module;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
