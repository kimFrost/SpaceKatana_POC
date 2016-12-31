// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ModuleComponent.h"
#include "ModulePowerComponent.generated.h"



//~~ DELEGATES ~~//
//DECLARE_MULTICAST_DELEGATE_OneParam(FPowerPulse, float);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPowerPulse, float, Amount);



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPACEKATANA_POC_API UModulePowerComponent : public UModuleComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UModulePowerComponent();

	//~~ Options variables ~~//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module")
	float StorageCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module")
	float PowerUpkeep;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module")
	float PowerGenerated;

	//~~ Runtime variables ~~//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module")
	float StoredPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module")
	float SurplusPower;
	

	UFUNCTION(BlueprintCallable, Category = "Ship")
	void GeneratePower();


	UPROPERTY(BlueprintAssignable, Category = "Power|Module")
	FPowerPulse OnPowerGeneration;


	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
