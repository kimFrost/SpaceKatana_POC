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
		//Rotation.Yaw = -90.f;
		Rotation.Yaw = 0.f;
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		PlaceholderModule = WorldRef->SpawnActor<AShipModule>(ModuleClassToSpawn, OrderLocation, Rotation);
		if (PlaceholderModule)
		{
			PlaceholderModule->CurrentState = EModuleState::STATE_Placeholder;
			PlaceholderModule->SpawnOrder = this;
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
			StartLocation = GameMode->CoordsToWorldLocation(X, Z) + FVector(GridTileSize / 2, 0.f, GridTileSize / 2);
		}
		else
		{
			return;
		}

		// Reset placeholder material color
		if (PlaceholderModule->PlaceholderDynamicMaterialInstance)
		{
			PlaceholderModule->PlaceholderDynamicMaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.54f, 0.f, 0.019449f, 1.f));
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


			// Trace base mesh overlap other module mesh (Using connector overlap and rotation instead with bIsHazard and bIsFragile)
			/*
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
						if (OtherModule->CurrentState == EModuleState::STATE_Attached || 
							OtherModule->CurrentState == EModuleState::STATE_Connected ||
							OtherModule->CurrentState == EModuleState::STATE_Static ||
							OtherModule->CurrentState == EModuleState::STATE_Placeholder) //TODO: Placeholder on placeholder
						{
							bModuleCollisionDanger = true;
							TraceLocation = StartLocation + (GridTileSize * (i - 1) * FlyInDirection); // Pull trace location one back, so error doesn't show inside other module
							PlaceholderModule->SetActorLocation(TraceLocation);
							//RootMesh->GetMaterial(0)->
							TracedTargetLocation = TraceLocation; //TODO: Properly not correct
							return;
						}
					}
				}
			}
			*/

			//bModuleCollisionDanger

			for (auto& Connector : PlaceholderModule->Connectors)
			{
				if (!IsValid(Connector)) {
					return;
				}

				FVector ConnectorLocation = Connector->GetActorLocation() + (GridTileSize * i * FlyInDirection);
				//FVector ConnectorDirection = Connector->GetActorRotation().Vector();
				FVector ConnectorDirection = Connector->GetActorForwardVector();
				bool bIsConnectorInFront = false;
				if (ConnectorDirection.Equals(FlyInDirection, 0.1f)) {
					bIsConnectorInFront = true;
				}

				//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, ConnectorDirection.Equals(FlyInDirection, 0.1f) ? "True" : "False");

				TArray<AActor*> OverlappingActors;
				Connector->GetOverlappingActors(OverlappingActors, Connector->StaticClass());
				for (auto& Actor : OverlappingActors) 
				{
					AShipModuleConnector* OtherConnector = Cast<AShipModuleConnector>(Actor);
					if (OtherConnector)
					{
						FVector InversedForwardVector = OtherConnector->GetActorForwardVector() * -1;
						bool bIsOtherConnectorOpposite = InversedForwardVector.Equals(ConnectorDirection, 0.1f);

						//if (bIsConnectorInFront && bIsOtherConnectorOpposite) {
						if (bIsConnectorInFront) {
							if (OtherConnector->bIsFragile || OtherConnector->bIsHazard || Connector->bIsFragile || Connector->bIsHazard)
							{
								bModuleCollisionDanger = true;
								TracedTargetLocation = TraceLocation;
								TracedTargetConnectorLocation = ConnectorLocation;
								if (PlaceholderModule->PlaceholderDynamicMaterialInstance)
								{
									PlaceholderModule->PlaceholderDynamicMaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.9f, 0.01f, 0.01f, 1.f));
								}
							}
						}

						// If front facing connectors overlap a fragile/hazard connector, then on danger collision course.
						// Then a valid attach/connect connector, can override the collision, if caught in this loop, else break.

						if (OtherConnector->bIsFragile || OtherConnector->bIsHazard)
						{
							// If two ore more connectors touch the same parent module of fragile/hazard connectors, can I assume that our trace module are inside a fragile/hazard area?
							// No. What if the fragile part is a window of a coridor. Only one fragile part. I need connectors facing the same direction as FlyInDirection.

						}

						if (!bValidAttachHit)
						{
							if (OtherConnector->bAllowAttachment || OtherConnector->bAllowConnection)
							{
								AShipModule* Module = Cast<AShipModule>(OtherConnector->GetParentActor());

								//if (Module && Module->CurrentState == EModuleState::STATE_Connected ||
								//	Module && Module->CurrentState == EModuleState::STATE_Attached)
								//{
									TracedTargetLocation = TraceLocation;
									TracedTargetConnectorLocation = ConnectorLocation;
									bValidAttachHit = true;
									if (PlaceholderModule->PlaceholderDynamicMaterialInstance)
									{
										PlaceholderModule->PlaceholderDynamicMaterialInstance->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.220919f, 0.7f, 0.125622f, 1.f));
									}
									return;
								//}
							}
						}
					}
				}
			} //~~ Loop Connectors (END) ~~//
			if (bModuleCollisionDanger && !bValidAttachHit)
			{
				return;
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
	
	if (!bIsCancelled)
	{
		SpawnModule();

		if (IsValid(SpawnedModule))
		{
			SpawnedModule->TargetMoveTo = TracedTargetLocation;
			/*
			if (bValidAttachHit)
			{
				SpawnedModule->TargetMoveTo = TracedTargetLocation;
			}
			*/
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


void UOrderSpawnModule::CancelOrder()
{
	Super::CancelOrder();

	if (IsValid(PlaceholderModule))
	{
		PlaceholderModule->Destroy();
		PlaceholderModule = nullptr;
	}

}