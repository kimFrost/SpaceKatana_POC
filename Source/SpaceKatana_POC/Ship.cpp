// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "ShipModule.h"
#include "Ship.h"


// Sets default values
AShip::AShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootModule = nullptr;

}


/******************** UpdateModules *************************/
void AShip::UpdateModules()
{
	// Get all child modules of class
	for (auto& Module : Modules)
	{
		if (IsValid(Module))
		{
			Module->bIsConnectedToRoot = false;
			Module->bHasBeenUpdated = false;
			Module->DistanceFromRoot = -1;
			if (Module->bIsRoot)
			{
				RootModule = Module;
			}
		}
		else
		{
			Modules.Remove(Module);
		}
	}

	//~~ Update all ship's modules connections ~~//
	UpdateConnections();

	//~~ If ship has a root module (MUST) (Maybe multiple in future) ~~//
	if (RootModule)
	{
		TMap<int32, TArray<AShipModule*>> ModuleRangeMap;
		int MaxDistance = 100;

		//ModuleRangeMap.Empty();
		TArray<AShipModule*> VisitedModules;
		TArray<AShipModule*> Frontier;
		Frontier.Add(RootModule);
		ModuleRangeMap.Add(0, Frontier); //~~ Add base for the start ~~//
		VisitedModules.Add(RootModule); //~~ Add base to allready visited to prevent bounce back ~~//

		RootModule->DistanceFromRoot = 0;

		for (int32 k = 0; k < MaxDistance; k++)
		{
			TArray<AShipModule*> NewFrontier;
			ModuleRangeMap.Add(k + 1, NewFrontier);
			Frontier = ModuleRangeMap[k];
			//~~ Loop though all modules in current frontier ~~//
			for (int32 m = 0; m < Frontier.Num(); m++)
			{
				AShipModule* Module = Frontier[m];

				/*
				if (Tile->TileCard.bBlockPath) {
					continue; //~~ Skip Tile ~~//
				}
				*/

				//~~ Loop though all Paths connected to this tile to create the next frontier ~~//
				for (int32 l = 0; l < Module->ConnectedTo.Num(); l++)
				{
					AShipModule* NeighborModule = Module->ConnectedTo[l];
			
					if (NeighborModule && !VisitedModules.Contains(NeighborModule))
					{
						NeighborModule->DistanceFromRoot = k + 1;
						ModuleRangeMap[k + 1].Add(NeighborModule); //~~ Add Neighbor module to the next frontier ~~//
						VisitedModules.Add(NeighborModule); //~~ Add to visited, so that neighbors don't overlap each other. ~~//
					}
				}
			}
		}

	}

	// Set all modules bIsConnectedToRoot = false; (DONE)

	// Flood fill from root module (TODO)

	// Detach all that still are bIsConnectedToRoot == false (TODO)

}

/******************** UpdateConnections *************************/
void AShip::UpdateConnections()
{
	for (auto& Module : Modules)
	{
		if (IsValid(Module))
		{
			Module->UpdateConnections();
		}
	}
}


// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}