// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "GameModeBattle.h"
#include "ShipModule.h"
#include "ShipModuleConnector.h"
#include "OrderSpawnModule.h"




UOrderSpawnModule::UOrderSpawnModule()
{
	//StoredShipModule = nullptr;
	FlyInDirection = FVector(1.f, 0.f, 0.f);
	SpawnedModule = nullptr;
	TracedTargetLocation = FVector();
	TracedTargetConnectorLocation = FVector();
	bModuleCollisionDanger = false;
	bValidAttachHit = false;
}


UOrderSpawnModule::~UOrderSpawnModule()
{

}


void UOrderSpawnModule::SpawnModule()
{
	if (WorldRef)
	{
		AGameModeBattle* GameMode = Cast<AGameModeBattle>(WorldRef->GetAuthGameMode());
		if (GameMode)
		{
			SpawnedModule = GameMode->SpawnFlyInModule(ModuleClassToSpawn, X, Y, FlyInDirection, FVector(), Buyer);
		}
	}
}


void UOrderSpawnModule::TraceProjection()
{
	DEBUG_TracedLocations.Empty();
	bValidAttachHit = false;
	bModuleCollisionDanger = false;

	if (SpawnedModule == nullptr)
	{
		SpawnModule();
	}
	if (IsValid(SpawnedModule) && WorldRef)
	{
		FVector StartLocation = SpawnedModule->GetActorLocation();
		float GridTileSize = 100.f;
		
		AGameModeBattle* GameMode = Cast<AGameModeBattle>(WorldRef->GetAuthGameMode());
		if (GameMode)
		{
			GridTileSize = GameMode->GridTileSize;
		}

		// Loop tiles in directions (row/column)
		for (int i = 1; i < 30; i++)
		{
			FVector TraceLocation = SpawnedModule->GetActorLocation() + (GridTileSize * i * FlyInDirection);

			for (auto& Connector : SpawnedModule->Connectors)
			{
				if (!IsValid(Connector)) {
					return;
				}
				
				FVector ConnectorLocation = Connector->GetActorLocation() + (GridTileSize * i * FlyInDirection);
				
				// Trace in Location for module Use GridTileSize * 0.45 for radius for best chance of hitting any type of module

				// Trace for crash collision first, and then connectors?


				FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true);

				RV_TraceParams.bTraceComplex = true;
				RV_TraceParams.bTraceAsyncScene = true;
				RV_TraceParams.bReturnPhysicalMaterial = false;

				FHitResult RV_Hit(ForceInit); //~~ Re-initialize hit info ~~//

				//~~ Module trace for collision danger ~~//

				FVector LineTraceFrom = TraceLocation + FVector{ 0.f, 0.f, 1.f };
				FVector LineTraceTo = TraceLocation - FVector{ 0.f, 0.f, 1.f };
				TArray<FHitResult> HitOutModule;
				FCollisionResponseParams ExtraParams;

				WorldRef->SweepMultiByChannel(
					HitOutModule, LineTraceFrom, LineTraceTo,
					FQuat::Identity, ECC_Visibility,
					FCollisionShape::MakeSphere(GridTileSize * 0.45),
					RV_TraceParams, ExtraParams
				);

				for (auto& HitItem : HitOutModule)
				{
					AActor* HitActor = HitItem.GetActor();
					if (HitActor)
					{
						AShipModule* Module = Cast<AShipModule>(HitActor);
						if (Module && Module->CurrentState == EModuleState::STATE_Attached)
						{
							bModuleCollisionDanger = true;
							TracedTargetLocation = TraceLocation;
							return;
						}
					}
				}

				//~~ Connector trace for attach ~~//

				LineTraceFrom = ConnectorLocation + FVector{ 0.f, 0.f, 1.f };
				LineTraceTo = ConnectorLocation - FVector{ 0.f, 0.f, 1.f };
				TArray<FHitResult> HitOutConnectors;

				bool Hit = WorldRef->SweepMultiByChannel(
					HitOutConnectors, LineTraceFrom, LineTraceTo,
					FQuat::Identity, ECC_GameTraceChannel2,
					FCollisionShape::MakeSphere(20.f),
					RV_TraceParams, ExtraParams
				);

				DEBUG_TracedLocations.Add(LineTraceFrom);

				for (auto& HitItem : HitOutConnectors)
				{
					AActor* HitActor = HitItem.GetActor();
					if (HitActor)
					{
						AShipModuleConnector* ShipModuleConnector = Cast<AShipModuleConnector>(HitActor);
						if (ShipModuleConnector)
						{
							AShipModule* Module = Cast<AShipModule>(ShipModuleConnector->GetParentActor());
							if (Module && Module->CurrentState == EModuleState::STATE_Attached)
							{
								TracedTargetLocation = TraceLocation;
								TracedTargetConnectorLocation = ConnectorLocation;
								bValidAttachHit = true;
								return;
							}
						}
					}
				}

				// Trace for module blocking forward. Collision warning


				/*
				WorldRef->LineTraceSingleByChannel(RV_Hit, LineTraceFrom, LineTraceTo, ECC_GameTraceChannel2, RV_TraceParams);
				if (RV_Hit.bBlockingHit)
				{
					//RV_Hit.GetComponent()
				}
				*/
			}


			/*
			// Trace
			FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
			RV_TraceParams.bTraceComplex = true;
			RV_TraceParams.bTraceAsyncScene = true;
			RV_TraceParams.bReturnPhysicalMaterial = false;
			//RV_TraceParams.TraceTag = TraceTag;

			//~~ Re-initialize hit info ~~//
			FHitResult RV_Hit(ForceInit);

			FVector WorldLocation;
			FVector WorldDirection;
			this->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

			//FRotator currentCharacterRotation = this->GetActorRotation();
			//FRotator targetRotation = mouseDirection.Rotation();

			FVector LineTraceFrom = WorldLocation + FVector{ 1.f, 1.f, 0.f };
			FVector LineTraceTo = WorldDirection * 50000 + WorldLocation + FVector{ 1.f, 1.f, 0.f };

			//ECC_GameTraceChannel1

			//this->GetWorld()->LineTraceSingleByChannel(RV_Hit, LineTraceFrom, LineTraceTo, ChannelLandscape, RV_TraceParams);
			this->GetWorld()->LineTraceSingleByChannel(RV_Hit, LineTraceFrom, LineTraceTo, ECC_Pawn, RV_TraceParams);
			if (RV_Hit.bBlockingHit)
			{
				if (RV_Hit.GetActor())
				{
					AIslandTile* HitTile = Cast<AIslandTile>(RV_Hit.GetActor());
				}
			}
			*/
		}
	}

	// Spawn module for trace projection through connectors


	// Connector collision channel

	// Loop all connectors of spawned module, and trace collision in the location offset by loop tile index in row 1*100, 2*100, 3*100, etc. 
	// until hit connector of a parent module that is attached


}


// Called when the game starts or when spawned
void UOrderSpawnModule::ResolveOrder()
{
	Super::ResolveOrder();

	if (IsValid(SpawnedModule))
	{
		SpawnedModule->TargetMoveTo = TracedTargetLocation;
	}
	
	//SpawnModule();

	// Set Module 

	//!! UObject can't GetWorld Safely without path !!//
	/*
	AGameModeBattle* GameMode = Cast<AGameModeBattle>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->SpawnFlyInModule(ModuleClassToSpawn, X, Y, FlyInDirection, Buyer);
	}
	*/
}