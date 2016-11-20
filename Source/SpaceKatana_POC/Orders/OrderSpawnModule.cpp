// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "GameModeBattle.h"
#include "OrderSpawnModule.h"




UOrderSpawnModule::UOrderSpawnModule()
{
	//StoredShipModule = nullptr;
	FlyInDirection = FVector(1.f, 0.f, 0.f);
}


UOrderSpawnModule::~UOrderSpawnModule()
{

}


// Called when the game starts or when spawned
void UOrderSpawnModule::ResolveOrder()
{
	Super::ResolveOrder();

	//!! UObject can't GetWorld Safely without path !!//
	/*
	AGameModeBattle* GameMode = Cast<AGameModeBattle>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->SpawnFlyInModule(ModuleClassToSpawn, X, Y, FlyInDirection, Buyer);
	}
	*/
}