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
	Funds = 0.f;
	Income = 0.f;

}

/******************** AddModule *************************/
AShipModule* AShip::AddModule(AShipModule* Module)
{
	AShipModule* AttachedModule = nullptr;

	if (IsValid(Module))
	{
		//AddComponent(FName(""), false, FTransform(), NULL);

		//this->AddComponent("ChildActor");
		//Module->AttachToComponent();
		Module->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true), NAME_None);
		Module->CurrentState = EModuleState::STATE_Attached;
		UStaticMeshComponent* RootMesh = Cast<UStaticMeshComponent>(Module->GetRootComponent());
		if (RootMesh)
		{
			RootMesh->SetSimulatePhysics(false);
		}
		/*
		FVector Location = Module->GetActorLocation();
		FRotator Rotation;

		FActorSpawnParameters SpawnParameters;

		UWorld* const World = GetWorld();
		if (World)
		{
			AttachedModule = World->SpawnActor<AShipModule>(Module->GetClass(), Location, Rotation);
		}
		*/

	}
	return AttachedModule;
}

/******************** AddModuleOfClass *************************/
AShipModule * AShip::AddModuleOfClass(TSubclassOf<class AShipModule> ModuleClass, FVector WorldLocation, FRotator WorldRotation)
{

	return nullptr;
}


/******************** UpdateModules *************************/
void AShip::UpdateModules()
{
	Modules.Empty();


	// Get all child modules of class (Modules are no longer child components, so this won't work)
	/*
	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors, false);
	for (auto& Actor : ChildActors)
	{
		AShipModule* Module = Cast<AShipModule>(Actor);
		if (IsValid(Module))
		{
			if (Module->bIsDestroyed)
			{
				Module->DestroyModule();
			}
			else
			{
				Modules.Add(Module);
			}
		}
	}
	*/



	// Reset Modules
	/*
	for (auto& Module : Modules)
	{
		if (IsValid(Module))
		{
			Module->bIsConnectedToRoot = false;
			Module->bHasBeenUpdated = false;
			Module->DistanceFromRoot = -1;

			Module->CurrentState = EModuleState::STATE_Static;

			if (Module->bIsDestroyed)
			{
				//Modules.Remove(Module); // Will crash the engine. Cannot remove will in iteration
				continue;
			}

			if (Module->bIsRoot)
			{
				RootModule = Module;
				RootModule->bIsConnectedToRoot = true;
				RootModule->bHasBeenUpdated = true;
			}
		}
	}
	*/


	/*
	for (int32 Index = Modules.Num() - 1; Index >= 0; --Index)
	{
		if (!IsValid(Modules[Index]))
		{
			const bool bAllowShrinking = false;
			Modules.RemoveAt(Index, 1, bAllowShrinking);
		}
	}
	*/

	//~~ Update all ship's modules connections ~~//
	//UpdateConnections(); // Done in game mode now

	// A ship must always have a root module. If no root module, then not valid ship


	//~~ If ship has a root module (MUST) (Maybe multiple in future) ~~//
	if (IsValid(RootModule))
	{
		//RootModule->UpdateConnections(); // Done in game mode now

		TMap<int32, TArray<AShipModule*>> ModuleRangeMap;
		int MaxDistance = 100;

		//ModuleRangeMap.Empty();
		TArray<AShipModule*> VisitedModules;
		TArray<AShipModule*> Frontier;
		Frontier.Add(RootModule);
		ModuleRangeMap.Add(0, Frontier); //~~ Add base for the start ~~//
		VisitedModules.Add(RootModule); //~~ Add base to allready visited to prevent bounce back ~~//

		RootModule->DistanceFromRoot = 0;
		RootModule->CurrentState = EModuleState::STATE_Attached;
		RootModule->bIsConnectedToRoot = true;

		for (int32 k = 0; k < MaxDistance; k++)
		{
			TArray<AShipModule*> NewFrontier;
			ModuleRangeMap.Add(k + 1, NewFrontier);
			Frontier = ModuleRangeMap[k];
			//~~ Loop though all modules in current frontier ~~//
			for (int32 m = 0; m < Frontier.Num(); m++)
			{
				AShipModule* Module = Frontier[m];

				// Need to reset all modules before update on all ship. Can do it in update function. Would override all traced on update on second ship. how and where??


				/*
				if (Tile->TileCard.bBlockPath) {
					continue; //~~ Skip Tile ~~//
				}
				*/

				// Set all adjacent module to be attached if this module is attached

				//~~ Loop though all Paths connected to this tile to create the next frontier ~~//
				for (int32 l = 0; l < Module->ConnectedTo.Num(); l++)
				{
					AShipModule* NeighborModule = Module->ConnectedTo[l];
			
					if (NeighborModule && !VisitedModules.Contains(NeighborModule))
					{
						NeighborModule->bIsConnectedToRoot = true;
						NeighborModule->DistanceFromRoot = k + 1;
						NeighborModule->bHasBeenUpdated = true;
						NeighborModule->CurrentState = EModuleState::STATE_Attached;
						
						//NeighborModule->UpdateConnections(); // Instead make the game mode update connections on every module in play. Better for handling modules that are not connected to a ship.
						
						Modules.Add(NeighborModule); // Add module to ship's modules array

						ModuleRangeMap[k + 1].Add(NeighborModule); //~~ Add Neighbor module to the next frontier ~~//
						VisitedModules.Add(NeighborModule); //~~ Add to visited, so that neighbors don't overlap each other. ~~//
					}
				}
			}
		}

	}

	// Set all modules bIsConnectedToRoot = false; (DONE)

	// Flood fill from root module (DONE)

	// Detach all that still are bIsConnectedToRoot == false (TODO)

	/* Cannot not be connected to root, since modules no longer are chilren of ship
	for (auto& Module : Modules)
	{
		if (IsValid(Module) && !Module->bIsConnectedToRoot)
		{
			Module->DestroyModule();
		}
	}
	*/
}

/******************** UpdateConnections *************************/
void AShip::UpdateConnections()
{
	// Won't work since connection need to be update for us to get the list of modules
	//!! Is done in game mode now instead !!//
	/*/
	for (auto& Module : Modules)
	{
		if (IsValid(Module))
		{
			Module->UpdateConnections();
		}
	}
	*/
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