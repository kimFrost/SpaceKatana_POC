// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "ShipModule.h"
#include "ShipModuleConnector.h"


// Sets default values
AShipModuleConnector::AShipModuleConnector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


/******************** Join *************************/
void AShipModuleConnector::Join(AShipModuleConnector* ConnectTo, bool bUpdateTransform, bool bUpdateOther)
{
	if (ConnectTo)
	{
		if (BoundTo != ConnectTo)
		{

			/*
			AShipModule* Module = Cast<AShipModule>(GetParentActor());
			if (Module)
			{
				AShipModule* OtherModule = Cast<AShipModule>(ConnectTo->GetParentActor());
				if (OtherModule)
				{
					FVector Location = Module->GetActorLocation();
					FVector ForwardVector = GetActorForwardVector();
					FVector NewLocation = Location + (ForwardVector * 100);
					OtherModule->SetActorLocation(NewLocation);
				}
			}

			ConnectTo->Join(this, false, false);
			*/
		}
	}

	//AngleInDegrees = RadToDeg * ACos( Normal( VectorA ) dot Normal( VectorB ) );
	//MedianRotation = RLerp( Rotator( VectorA ), Rotator( VectorB ), 0.5, true );
	//Rotator( PointB - PointA );
}


// Called when the game starts or when spawned
void AShipModuleConnector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipModuleConnector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

