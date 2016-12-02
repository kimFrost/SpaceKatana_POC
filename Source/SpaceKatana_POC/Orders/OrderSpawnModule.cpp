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
		//~~ Destroy placeholder ~~//
		PlaceholderModule->Destroy();
	}
}

void UOrderSpawnModule::SpawnPlaceholderModule()
{
	if (WorldRef)
	{
		// Create module placeholder
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FRotator Rotation;
		Rotation.Yaw = -90.f;
		Rotation.Pitch = 0;
		Rotation.Roll = 0;

		PlaceholderModule = WorldRef->SpawnActor<AShipModule>(ModuleClassToSpawn, OrderLocation, Rotation);
		if (PlaceholderModule)
		{
			PlaceholderModule->CurrentState = EModuleState::STATE_Placeholder;
			PlaceholderModule->InitModule(); // InitModule is implemented in blueprint with _implemented
		}
	}
}


void UOrderSpawnModule::TraceProjection()
{
	DEBUG_TracedLocations.Empty();
	bValidAttachHit = false;
	bModuleCollisionDanger = false;

	if (PlaceholderModule == nullptr)
	{
		SpawnPlaceholderModule();
	}

	if (IsValid(PlaceholderModule) && WorldRef)
	{
		FVector StartLocation;
		float GridTileSize = 100.f;
		
		AGameModeBattle* GameMode = Cast<AGameModeBattle>(WorldRef->GetAuthGameMode());
		if (GameMode)
		{
			GridTileSize = GameMode->GridTileSize;
			StartLocation = GameMode->CoordsToWorldLocation(X, Y) + FVector(GridTileSize / 2, GridTileSize / 2, 0);
		}
		else
		{
			return;
		}

		// Loop tiles in directions (row/column)
		for (int i = 1; i < 30; i++)
		{
			FVector TraceLocation = StartLocation + (GridTileSize * i * FlyInDirection);

			//~~ New tracing method (Placeholder overlap) ~~//

			// Set Placeholder world location and sweep location with root mesh
			PlaceholderModule->SetActorLocation(TraceLocation);

			/*
			FHitResult HitResult;
			if (PlaceholderModule->SetActorLocation(TraceLocation, true, &HitResult) == false)
			{
				bModuleCollisionDanger = true;
				TracedTargetLocation = TraceLocation;
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TracedTargetLocation.ToString());
				return;
			}
			*/

			// Trace base mesh overlap other module mesh
			UStaticMeshComponent* RootMesh = Cast<UStaticMeshComponent>(PlaceholderModule->GetRootComponent());
			if (RootMesh)
			{
				TArray<AActor*> OverlappingActors;
				RootMesh->GetOverlappingActors(OverlappingActors);
				//RootMesh->GetOverlappingActors(OverlappingActors, AShipModule::StaticClass());
				//TArray<UPrimitiveComponent*> OverlappingComponents;
				//RootMesh->GetOverlappingComponents(OverlappingComponents);

				for (auto& Actor : OverlappingActors)
				{
					AShipModule* OtherModule = Cast<AShipModule>(Actor);
					if (OtherModule)
					{
						if (OtherModule->CurrentState == EModuleState::STATE_Attached) //TODO: Placeholder on placeholder
						{
							bModuleCollisionDanger = true;
							TraceLocation = StartLocation + (GridTileSize * (i - 1) * FlyInDirection); // Pull trace location one back, so error doesn't show inside other module
							PlaceholderModule->SetActorLocation(TraceLocation);
							TracedTargetLocation = TraceLocation; //TODO: Properly not correct
							return;
						}
					}
				}
			}

			for (auto& Connector : PlaceholderModule->Connectors)
			{
				if (!IsValid(Connector)) {
					return;
				}

				FVector ConnectorLocation = Connector->GetActorLocation() + (GridTileSize * i * FlyInDirection);

				TArray<AActor*> OverlappingActors;
				Connector->GetOverlappingActors(OverlappingActors, Connector->StaticClass());
				for (auto& Actor : OverlappingActors)
				{
					AShipModuleConnector* OtherConnector = Cast<AShipModuleConnector>(Actor);
					if (OtherConnector)
					{
						AShipModule* Module = Cast<AShipModule>(OtherConnector->GetParentActor());
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


			//~~ Old Tracing method (SweepMultiByChannel) ~~//
			/*
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
			}
			*/
	
		}
	}

}


// Called when the game starts or when spawned
void UOrderSpawnModule::ResolveOrder()
{
	Super::ResolveOrder();

	SpawnModule();

	if (IsValid(SpawnedModule))
	{
		if (bValidAttachHit) 
		{
			SpawnedModule->TargetMoveTo = TracedTargetLocation;
		}
	}

	// WorldRef
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