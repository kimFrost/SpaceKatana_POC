// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "ModuleComponent.h"
#include "ShipModule.h"
#include "ModuleThrustComponent.h"


// Sets default values for this component's properties
UModuleThrustComponent::UModuleThrustComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ThrustAmount = 1.f;

}


// Called when the game starts
void UModuleThrustComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(Module))
	{

	}
}


// Called every frame
void UModuleThrustComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

}

