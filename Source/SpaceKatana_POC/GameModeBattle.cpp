// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "Ship.h"
#include "ShipModule.h"
#include "GameModeBattle.h"



// Sets default values
AGameModeBattle::AGameModeBattle(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	GridSizeX = 30;
	GridSizeX = 20;
	GridTileSize = 100.f;
}



void AGameModeBattle::ConstructGrid()
{
	for (int Y = 0; Y > GridSizeY; Y++)
	{
		for (int X = 0; X > GridSizeX; X++)
		{
			FVector TileWorldLocation;
			TileWorldLocation.X = GridTileSize * X;
			TileWorldLocation.Y = GridTileSize * Y;
			FST_GridTile Tile = FST_GridTile(nullptr, X, Y, TileWorldLocation);
			GridTiles.Add(Tile);
		}
	}
}

//void UKismetProceduralMeshLibrary::ConvertQuadToTriangles(TArray<int32>& Triangles, int32 Vert0, int32 Vert1, int32 Vert2, int32 Vert3)

//struct FST_GridTile& AGameModeBattle::GetGridTile(FVector WorldLocation)
void AGameModeBattle::GetGridTile(FST_GridTile& Tile, FVector WorldLocation)
{
	//FST_GridTile& TempTile = FST_GridTile();
	for (auto& GridTile : GridTiles)
	{
		// If GridTile is closer than Tile, then override
		Tile = GridTile;
	}
	//return TempTile;

	// PARAM_PASSED_BY_REF(StructBox, UStructProperty, FStructBox); ?? What does this do ??


	// Convert world location to Grid Tile

	// Return false if outside grid? 
	// Or return nearest?

	// Loop GridTiles and alsways store the closest one as return value;
}

bool AGameModeBattle::IsValidShipLocation(AShip* Ship, FVector WorldLocation)
{
	bool Valid = false;
	if (IsValid(Ship))
	{

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