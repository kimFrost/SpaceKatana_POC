// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "ShipModule.h"
#include "ModuleComponent.h"


// Sets default values for this component's properties
UModuleComponent::UModuleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Module = nullptr;
	bCanToggle = true;
	bIsOn = true;
}


bool UModuleComponent::ToggleOn()
{

	return bIsOn;
}

// Called when the game starts
void UModuleComponent::BeginPlay()
{
	Super::BeginPlay();

	AShipModule* ShipModule = Cast<AShipModule>(GetOwner());
	if (ShipModule)
	{
		Module = ShipModule;
	}

}


// Called every frame
void UModuleComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

