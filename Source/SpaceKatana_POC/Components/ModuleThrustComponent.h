// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ModuleComponent.h"
#include "ModuleThrustComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEKATANA_POC_API UModuleThrustComponent : public UModuleComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UModuleThrustComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module")
	float ThrustAmount;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
};
