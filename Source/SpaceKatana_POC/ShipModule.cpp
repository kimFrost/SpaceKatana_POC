// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
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
	CurrentState = EModuleState::STATE_FlyIn;
	FlyInDirection = FVector(1, 0, 0);

	DistanceFromRoot = -1;
}


/******************** DestroyModule *************************/
void AShipModule::DestroyModule()
{
	//Module->Destroy();
	//DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	bIsConnectedToRoot = false;
	CurrentState = EModuleState::STATE_Destroyed;
	DistanceFromRoot = -1;

	for (auto& Connector : Connectors)
	{
		if (IsValid(Connector))
		{
			Connector->SetActorEnableCollision(false);
		}
	}

	UpdateConnections();

	OnShipModuleDestroyed.Broadcast(this);
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
					AShipModule* OtherModule = Cast<AShipModule>(OtherConnector->GetParentActor());
					if (OtherModule)
					{
						if (GetParentActor() == OtherModule->GetParentActor())
						{
							Connector->BoundTo = OtherConnector;
							ConnectedTo.Add(OtherModule);
						}
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

