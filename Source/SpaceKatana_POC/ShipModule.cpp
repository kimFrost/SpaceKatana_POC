// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "ShipModule.h"


// Sets default values
AShipModule::AShipModule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 1000.f;
	Health = Health;
}


/******************** UpdateConnected *************************/
void AShipModule::UpdateConnected()
{

	// Loop all modules connected to this module.

	// Pass self and list to connected module?


}

// Called when the game starts or when spawned
void AShipModule::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipModule::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

