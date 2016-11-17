// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "OrderVisualizer.h"


// Sets default values
AOrderVisualizer::AOrderVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OrderType = EOrderType::SpawnModule;
	Order = nullptr;
}

// Called when the game starts or when spawned
void AOrderVisualizer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrderVisualizer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

