// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "Kismet/KismetMathLibrary.h"
#include "Ship.h"
#include "ShipModule.h"
#include "GridTile.h"
#include "GameModeBattle.h"



// Sets default values
AGameModeBattle::AGameModeBattle(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	GridSizeX = 15;
	GridSizeY = 10;
	GridTileSize = 100.f;
}



void AGameModeBattle::ConstructGrid()
{

	for (int Y = 0; Y < GridSizeY; Y++)
	{
		for (int X = 0; X < GridSizeX; X++)
		{
			FVector TileWorldLocation;
			//TileWorldLocation.X = GridTileSize * X;
			TileWorldLocation.X = GridTileSize * X - (GridTileSize * GridSizeX / 2);
			//TileWorldLocation.Y = GridTileSize * Y;
			TileWorldLocation.Y = GridTileSize * Y - (GridTileSize * GridSizeY / 2);
			TileWorldLocation.Z = 0.f;

			//FST_GridTile Tile = FST_GridTile(nullptr, X, Y, TileWorldLocation);
			UGridTile* Tile = NewObject<UGridTile>();
			if (Tile)
			{
				Tile->WorldLocation = TileWorldLocation;
				Tile->Row = Y;
				Tile->Column = X;
			}
			
			GridTiles.Add(Tile);
		}
	}
}

//void UKismetProceduralMeshLibrary::ConvertQuadToTriangles(TArray<int32>& Triangles, int32 Vert0, int32 Vert1, int32 Vert2, int32 Vert3)

//struct FST_GridTile& AGameModeBattle::GetGridTile(FVector WorldLocation)
//void AGameModeBattle::GetGridTile(FST_GridTile& Tile, FVector WorldLocation)
UGridTile* AGameModeBattle::GetGridTile(FVector WorldLocation, bool bRoundOutOfBounds)
{
	UGridTile* Tile = nullptr;

	FVector RelativeLocation = WorldLocation + FVector{(GridTileSize * GridSizeX / 2), (GridTileSize * GridSizeY / 2), 0.f };

	if (bRoundOutOfBounds)
	{
		//UKismetMathLibrary::ClampVectorSize(RelativeLocation, 0.f, 10.f);
		//UKismetMathLibrary::Clam
		RelativeLocation.X = FMath::Clamp(RelativeLocation.X, 0.f, (GridSizeX - 1) * GridTileSize);
		RelativeLocation.Y = FMath::Clamp(RelativeLocation.Y, 0.f, (GridSizeY - 1) * GridTileSize);
		//FMath::Clamp(RelativeLocation, 0, GridSizeX - 1);
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

	if (bRoundOutOfBounds)
	{
		//FMath::Clamp(TileX, 0, GridSizeX - 1);
		//FMath::Clamp(TileY, 0, GridSizeY - 1);
	}
	
	int TileIndex = TileY * GridSizeX + TileX;
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

bool AGameModeBattle::IsValidShipLocation(AShip* Ship, FVector WorldLocation)
{
	bool Valid = true;
	if (IsValid(Ship))
	{
		for (auto& Module : Ship->Modules)
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

bool AGameModeBattle::RegisterOnTile(AShipModule* ShipModule)
{
	bool Registered = false;

	// One Ship Move, register module on tile

	// Or loop every new turn and trace each tile for module in world location?




	return Registered;
}