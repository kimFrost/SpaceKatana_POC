// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "ShipModuleConnector.h"
#include "ShipModule.h"


// Sets default values
AShipModule::AShipModule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 1000.f;
	Health = Health;

	bIsRoot = false;
	bIsConnectedToRoot = false;
	bHasBeenUpdated = false;
	bIsDestroyed = false;

	DistanceFromRoot = 0;
}



/******************** UpdateConnections *************************/
void AShipModule::UpdateConnections()
{
	ConnectedTo.Empty();
	for (auto& Connector : Connectors)
	{
		if (IsValid(Connector))
		{
			Connector->BoundTo = nullptr; //~~ Reset BoundTo ~~//
			TArray<AActor*> OverlappingActors;
			Connector->GetOverlappingActors(OverlappingActors, Connector->StaticClass());
			for (auto& Actor : OverlappingActors)
			{
				AShipModuleConnector* OtherConnector = Cast<AShipModuleConnector>(Actor);
				if (OtherConnector)
				{
					Connector->BoundTo = OtherConnector;
					AShipModule* OtherModule = Cast<AShipModule>(OtherConnector->GetParentActor());
					if (OtherModule)
					{
						ConnectedTo.Add(OtherModule);
					}
					break;
				}
			}
		}
		else
		{
			//Connectors.Remove(Connector);
		}
	}

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

