// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Ship.h"
#include "ShipModule.h"
#include "GridTile.h"
#include "Orders/OrderSpawnModule.h"
#include "Orders/OrderVisualizer.h"
#include "GameModeBattle.h"



// Sets default values
AGameModeBattle::AGameModeBattle(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	GridSizeX = 20;
	GridSizeY = 15;
	GridSizeZ = 15;
	GridTileSize = 100.f;
	CurrentStep = ETurnStep::Planning;
	HighestSequence = 0;

	Time = 0.f;
	PlayRate = 1.f;
	PlayingLength = 3.f; // Not used
	PlaningLength = 60.f;
	TurnTimeLeft = PlaningLength;

	bPlayerOneReady = false;
	bPlayerTwoReady = false;

	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/SpaceKatana/Blueprints/BP_OrderVisualizer.BP_OrderVisualizer'"));
	if (ItemBlueprint.Object) {
		OrderVisulizerBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}
}



/******************** AddOrder_SpawnModule *************************/
UOrderSpawnModule* AGameModeBattle::AddOrder_SpawnModule(TSubclassOf<class AShipModule> ModuleClass, int X, int Z, FVector Direction, AShip* Buyer)
{
	UOrderSpawnModule* Order = NewObject<UOrderSpawnModule>();
	if (Order) 
	{
		Order->ModuleClassToSpawn = ModuleClass;
		Order->FlyInDirection = Direction;
		Order->X = X;
		Order->Z = Z;
		Order->OrderLocation = CoordsToWorldLocation(X, Z) + FVector(GridTileSize / 2, 0.f, GridTileSize / 2); // Add half grid size??
		//Order->OnOrderResolved.AddDynamic();
		Order->WorldRef = GetWorld();

		HighestSequence++;
		Order->Sequence = HighestSequence;

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FRotator Rotation = Direction.Rotation();

		/*
		UWorld* const World = GetWorld();
		if (World)
		{
			//AItem* DroppedItem = World->SpawnActor<ASurItem>(MyItemBlueprint, Location, Rotation, SpawnParams);
			//AOrderVisualizer* OrderVisualizer = World->SpawnActor<AOrderVisualizer>(ModuleClass, Order->OrderLocation, FRotator());
			AOrderVisualizer* OrderVisualizer = World->SpawnActor<AOrderVisualizer>(OrderVisulizerBlueprint, Order->OrderLocation, Rotation);
			if (OrderVisualizer)
			{
				OrderVisualizer->OrderType = EOrderType::SpawnModule; // Might be redundant. The Order can't be cast instead
				OrderVisualizer->Order = Order;
				OrderVisualizer->Init();
			}
		}
		*/

		Orders.Add(Order);
	}
	return Order;
}


/******************** UpdateOrders *************************/
void AGameModeBattle::UpdateOrders(EOrderType OrderType)
{
	//TODO: switch on which orders to cast and update and resolve
	for (auto& Order : Orders)
	{
		if (IsValid(Order))
		{
			if (Order->TurnsLeft <= 1)
			{
				Order->ResolveOrder();
			}
		}
	}
	//~~ Clean array of resolved orders ~~//
	for (int i = Orders.Num() - 1; i >= 0; i--)
	{
		UOrder* Order = Orders[i];
		if ((IsValid(Order) && Order->bIsResolved) || !Order)
		{
			Orders.RemoveAt(i);
		}
	}
}


/******************** ConstructGrid *************************/
void AGameModeBattle::ConstructGrid()
{

	for (int Z = 0; Z < GridSizeZ; Z++)
	{
		for (int X = 0; X < GridSizeX; X++)
		{
			FVector TileWorldLocation;
			TileWorldLocation.X = GridTileSize * X - (GridTileSize * GridSizeX / 2);
			//TileWorldLocation.X = GridTileSize * X - (GridTileSize * GridSizeX / 2) - GridTileSize / 2;
			TileWorldLocation.Y = 0.f; //TileWorldLocation.Y = GridTileSize * Y - (GridTileSize * GridSizeY / 2);
			//TileWorldLocation.Y = GridTileSize * Y - (GridTileSize * GridSizeY / 2) - GridTileSize / 2;
			TileWorldLocation.Z = TileWorldLocation.Z = GridTileSize * Z - (GridTileSize * GridSizeZ / 2);

			//FST_GridTile Tile = FST_GridTile(nullptr, X, Y, TileWorldLocation);
			UGridTile* Tile = NewObject<UGridTile>();
			if (Tile)
			{
				Tile->WorldLocation = TileWorldLocation;
				Tile->Row = Z;
				Tile->Column = X;
			}
			
			GridTiles.Add(Tile);
		}
	}
}


/******************** CoordsToWorldLocation *************************/
FVector AGameModeBattle::CoordsToWorldLocation(int X, int Z)
{
	return FVector(X * GridTileSize - (GridTileSize * GridSizeX / 2), 0.f, Z * GridTileSize - (GridTileSize * GridSizeZ / 2));
}


/******************** WorldLocationToCoords *************************/
FVector AGameModeBattle::WorldLocationToCoords(FVector WorldLocation, bool bRoundOutOfBounds)
{
	FVector RelativeLocation = WorldLocation + FVector{ (GridTileSize * GridSizeX / 2), 0.f, (GridTileSize * GridSizeZ / 2) };

	if (bRoundOutOfBounds)
	{
		RelativeLocation.X = FMath::Clamp(RelativeLocation.X, 0.f, (GridSizeX - 1) * GridTileSize);
		RelativeLocation.Z = FMath::Clamp(RelativeLocation.Z, 0.f, (GridSizeZ - 1) * GridTileSize);
	}

	float TileXGuess = RelativeLocation.X / GridTileSize;
	float TileZGuess = RelativeLocation.Z / GridTileSize;

	int TileX = FMath::FloorToInt(TileXGuess);
	int TileZ = FMath::FloorToInt(TileZGuess);

	return (FVector(TileX, 0.f, TileZ));
}


/******************** UpdateAllModules *************************/
void AGameModeBattle::UpdateAllModules()
{
	/*
	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors, false);
	for (auto& Actor : ChildActors)
	{
		AShipModule* Module = Cast<AShipModule>(Actor);
		if (IsValid(Module))
		{

		}
	}
	*/

	//~~ Reset and update all modules ~~//
	for (TActorIterator<AShipModule> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		AShipModule* Module = *ActorItr;
		if (IsValid(Module))
		{
			Module->UpdateModule();
		}
	}
}


/******************** ProgressTurnStep *************************/
ETurnStep AGameModeBattle::ProgressTurnStep()
{
	if (CurrentStep == ETurnStep::Planning)
	{
		CurrentStep = ETurnStep::Moving;
	}
	else if (CurrentStep == ETurnStep::Moving)
	{
		CurrentStep = ETurnStep::Shooting;
	}
	else if (CurrentStep == ETurnStep::Shooting)
	{
		CurrentStep = ETurnStep::SpawningModules;
	}
	else if (CurrentStep == ETurnStep::SpawningModules)
	{
		CurrentStep = ETurnStep::Maneuvering;
	}
	else if (CurrentStep == ETurnStep::Maneuvering)
	{
		CurrentStep = ETurnStep::Planning;
	}
	return CurrentStep;
}


/******************** SetPlayRate *************************/
void AGameModeBattle::SetPlayRate(float TimeRate, float DilationRate)
{
	UWorld* World = GetWorld();
	if (World)
	{
		PlayRate = TimeRate;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DilationRate);
		//World->GetWorldSettings()->TimeDilation = 1 / UGameplayStatics::GetGlobalTimeDilation(World);
		CustomTimeDilation = 1 / UGameplayStatics::GetGlobalTimeDilation(World);

		//FString TheFloatStr = FString::SanitizeFloat(UGameplayStatics::GetGlobalTimeDilation(World));
		//UE_LOG(YourLog, Warning, TEXT("MyCharacter's Health is %f"), UGameplayStatics::GetGlobalTimeDilation(World));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(UGameplayStatics::GetGlobalTimeDilation(World)));


	}
}


/******************** EndTurn *************************/
void AGameModeBattle::EndTurn(int ShipIndex)
{
	if (ShipIndex == 0)
	{
		bPlayerOneReady = true;
	}
	else if (ShipIndex == 1)
	{
		bPlayerTwoReady = true;
	}
	if (bPlayerOneReady && bPlayerTwoReady)
	{
		TurnTimeLeft = 0.f;
	}
}


/******************** NewTurn *************************/
void AGameModeBattle::NewTurn()
{
	bPlayerOneReady = false;
	bPlayerTwoReady = false;
	HighestSequence = 0;

	for (auto& Order : Orders)
	{
		if (IsValid(Order))
		{
			Order->TurnsLeft--;
		}
	}

	CurrentStep = ETurnStep::Planning;
	TurnTimeLeft = PlaningLength;
	//SetPlayRate(1.f, 0.1f); // Outcomment this after testing
	UpdateAllModules();
	OnNewTurn.Broadcast();
}


/******************** ProgressTime *************************/
void AGameModeBattle::ProgressTime(float Amount)
{
	Time = Time + Amount;
	TurnTimeLeft = TurnTimeLeft - Amount;
	if (TurnTimeLeft <= 0)
	{
		ETurnStep NewStep = ProgressTurnStep();

		switch (NewStep)
		{
		case ETurnStep::Planning:
			NewTurn();
			break;
		case ETurnStep::Moving:
			TurnTimeLeft = 1.f;
			SetPlayRate(1.f, 1.f);
			break;
		case ETurnStep::Shooting:
			TurnTimeLeft = 1.f;
			break;
		case ETurnStep::SpawningModules:
			TurnTimeLeft = 1.f;
			UpdateOrders(EOrderType::SpawnModule);
			break;
		case ETurnStep::Maneuvering:
			TurnTimeLeft = 2.f;
			break;
		}

		OnStepChange.Broadcast(NewStep);
	}
	OnTimeUpdated.Broadcast(Time, Amount);
}


//void UKismetProceduralMeshLibrary::ConvertQuadToTriangles(TArray<int32>& Triangles, int32 Vert0, int32 Vert1, int32 Vert2, int32 Vert3)

//struct FST_GridTile& AGameModeBattle::GetGridTile(FVector WorldLocation)
//void AGameModeBattle::GetGridTile(FST_GridTile& Tile, FVector WorldLocation)
/******************** GetGridTile *************************/
UGridTile* AGameModeBattle::GetGridTile(FVector WorldLocation, bool bRoundOutOfBounds)
{
	UGridTile* Tile = nullptr;

	/*
	FVector RelativeLocation = WorldLocation + FVector{(GridTileSize * GridSizeX / 2), (GridTileSize * GridSizeY / 2), 0.f };

	if (bRoundOutOfBounds)
	{
		RelativeLocation.X = FMath::Clamp(RelativeLocation.X, 0.f, (GridSizeX - 1) * GridTileSize);
		RelativeLocation.Y = FMath::Clamp(RelativeLocation.Y, 0.f, (GridSizeY - 1) * GridTileSize);
	}

	//UE_LOG(YourLog, Warning, TEXT("MyCharacter's Location is %s"), RelativeLocation.ToString());

	//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, WorldLocation.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, RelativeLocation.ToString());

	float TileXGuess = RelativeLocation.X / GridTileSize;
	float TileYGuess = RelativeLocation.Y / GridTileSize;

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, TEXT("TileXGuess: ") + FString::SanitizeFloat(TileXGuess));
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, TEXT("TileYGuess: ") + FString::SanitizeFloat(TileYGuess));

	int TileX = FMath::FloorToInt(TileXGuess);
	int TileY = FMath::FloorToInt(TileYGuess);
	*/

	FVector TileCoords = WorldLocationToCoords(WorldLocation, bRoundOutOfBounds);

	int TileIndex = TileCoords.Z * GridSizeX + TileCoords.X;
	if (GridTiles.IsValidIndex(TileIndex))
	{
		return GridTiles[TileIndex];
	}
	return Tile;


	/*
	//FST_GridTile& TempTile = FST_GridTile();
	for (auto& GridTile : GridTiles)
	{
		Tile = GridTile;
		// If GridTile is closer than Tile, then override
		//Tile = GridTile;
	}
	*/

	// PARAM_PASSED_BY_REF(StructBox, UStructProperty, FStructBox); ?? What does this do ??


	// Convert world location to Grid Tile

	// Return false if outside grid? 
	// Or return nearest?

	// Loop GridTiles and alsways store the closest one as return value;
}


/******************** SpawnFlyInModule *************************/
AShipModule* AGameModeBattle::SpawnFlyInModule(TSubclassOf<class AShipModule> ModuleClass, int X, int Z, FVector Direction, FVector Target, AShip* Buyer)
{
	AShipModule* Module = nullptr;

	FVector Location = CoordsToWorldLocation(X, Z) + FVector(GridTileSize / 2, GridTileSize / 2, 0);

	// Location should be off screen in row / column

	FRotator Rotation;
	Rotation.Yaw = 0.f;
	Rotation.Pitch = 0.f;
	Rotation.Roll = 0.f;

	Location = Location - (Direction * 2000); 
	Location.Y = 0;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UWorld* const World = GetWorld();
	if (World)
	{
		Module = World->SpawnActor<AShipModule>(ModuleClass, Location, Rotation);
		if (Module)
		{
			Module->CurrentState = EModuleState::STATE_FlyIn;
			Module->FlyInDirection = Direction;
			Module->TargetMoveTo = Target;
			Module->InitModule();
		}
		//Module->EModuleState

		//World->SpawnActor<AShipModule>(ModuleClass, SpawnParameters);
		//GunInstance = GetWorld()->SpawnActor<AGun>(TSubclassOf<AGun>(*(BlueprintLoader::Get().GetBP(FName("BP_2")))), spawnParams);
		//World->SpawnActor<AShipModule>(Module, FVector(0, 0, 0), FRotator::ZeroRotator);
		//Module = (AShipModule*)GetWorld()->SpawnActor(ModuleClass, NAME_None, Location);
	}

	return Module;
}


/******************** IsValidShipLocation *************************/
bool AGameModeBattle::IsValidShipLocation(AShip* Ship, FVector WorldLocation)
{
	bool Valid = true;
	if (IsValid(Ship))
	{
		for (auto& Module : Ship->AttachedModules)
		{
			if (IsValid(Module))
			{
				UGridTile* Tile = GetGridTile(Module->GetActorLocation(), false);
				if (IsValid(Tile))
				{
					if (Tile->StoredShipModule)
					{
						Valid = false;
						break;
					}
				}
			}
		}
		//GetGridTile()
		// Loop Modules and combine their relative location to the ship, and the passed WorldLocation

		// Get ship shape(Modules)
		// Or loop all modules check GridTiles in locations
		// Or loop passed array of locations and check 
	}
	return Valid;
}


/******************** BeginPlay *************************/
void AGameModeBattle::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::CreatePlayer(GetWorld());

	ConstructGrid();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AGameModeBattle::NewTurn, 0.5f, false);
}


/******************** Tick *************************/
void AGameModeBattle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayRate > 0.0001)
	{
		ProgressTime(DeltaTime * PlayRate);
	}
}