// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "GameModeBattle.h"
#include "ModulePowerComponent.h"



// Sets default values for this component's properties
UModulePowerComponent::UModulePowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	StorageCapacity = 0.f;
	PowerUpkeep = 0.f;
	PowerGenerated = 0.f;

	StoredPower = 0.f;
	SurplusPower = 0.f;
}



void UModulePowerComponent::GeneratePower()
{
	if (PowerGenerated > 0.f)
	{
		if (PowerGenerated + StoredPower > StorageCapacity)
		{
			// Store in self

		}
		else
		{
			// Store in self and rest to ship for distribution


			// First distribute to upkeeps, then to storage


			// Ship distribution system??

		}

		OnPowerGeneration.Broadcast(PowerGenerated);
	}
}


// Called when the game starts
void UModulePowerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(Module))
	{
		AGameModeBattle* GameMode = Cast<AGameModeBattle>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{

		}
	}
}


// Called every frame
void UModulePowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

