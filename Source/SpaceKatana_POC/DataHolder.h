// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataHolder.generated.h"


//~~~~~ FORWARD DECLATIONS ~~~~~//
class AShipModule;



//~~~~~ ENUMS ~~~~~//

UENUM(BlueprintType)
enum class EShipModuleType : uint8
{
	BlockSquare UMETA(DisplayName = "BlockSquare"),
	BlockCore UMETA(DisplayName = "BlockCore"),
	BlockCorner UMETA(DisplayName = "BlockCorner"),
	TurretLaser UMETA(DisplayName = "TurretLaser"),
	Engine UMETA(DisplayName = "Engine")
};

UENUM(BlueprintType)
enum class EShipModuleShape : uint8
{
	Square UMETA(DisplayName = "Square"),
	Corner UMETA(DisplayName = "Corner")
};

UENUM(BlueprintType)
enum class EModuleState : uint8
{
	STATE_Static UMETA(DisplayName = "Static"),
	STATE_Attached UMETA(DisplayName = "Attached"),
	STATE_Destroyed UMETA(DisplayName = "Destroyed"),
	STATE_FlyIn UMETA(DisplayName = "Flying in")
};

UENUM(BlueprintType)
enum class EShipMessage : uint8
{
	MSG_PlayerSighted UMETA(DisplayName = "PlayerSighted"),
	MSG_Reset UMETA(DisplayName = "Reset")
};

UENUM(BlueprintType)
enum class ETurnStep : uint8
{
	Planning UMETA(DisplayName = "Planning"),
	Moving UMETA(DisplayName = "Moving"),
	Shooting UMETA(DisplayName = "Shooting"),
	SpawningModules UMETA(DisplayName = "SpawningModules")
};

UENUM(BlueprintType)
enum class EOrderType : uint8
{
	MoveShip UMETA(DisplayName = "MoveShip"),
	Shoot UMETA(DisplayName = "Shoot"),
	SpawnModule UMETA(DisplayName = "SpawnModule")
};

UENUM(BlueprintType)
enum class EToolType : uint8
{
	Select UMETA(DisplayName = "Select"),
	SpawnModule UMETA(DisplayName = "SpawnModule")
};


//~~~~~ STRUCTS ~~~~~//

USTRUCT(BlueprintType)
struct FST_TempMod
{
	GENERATED_USTRUCT_BODY()
public:
	FST_TempMod(int32 Rating = 0)
		: Rating(Rating)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int32 Rating;
};

// FST_GridTile
USTRUCT(BlueprintType)
struct FST_GridTile
{
	GENERATED_USTRUCT_BODY()
public:
	FST_GridTile(AShipModule* ShipModule = nullptr, int Column = 0, int Row = 0, FVector WorldLocation = FVector{ 0.f, 0.f, 0.f })
		: ShipModule(ShipModule)
		, Column(Column)
		, Row(Row)
		, WorldLocation(WorldLocation)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	AShipModule* ShipModule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int Column;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	int Row;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FVector WorldLocation;
};



USTRUCT(BlueprintType)
struct FST_ShipModule
{
	GENERATED_USTRUCT_BODY()
public:
	FST_ShipModule(
		FString Title = "",
		EShipModuleType Type = EShipModuleType::BlockSquare,
		float Rotation = 0.f,
		FVector2D Position = FVector2D{0, 0})
		: Title(Title)
		, Type(Type)
		, Rotation(Rotation)
		, Position(Position)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	EShipModuleType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float Rotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FVector2D Position;
};


//~~~~~ DATA IMPORT ~~~~~//

USTRUCT(BlueprintType)
struct FST_Ship : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Ship(FString Id = "", TArray<FST_ShipModule> Modules = TArray<FST_ShipModule>())
		: Id(Id)
		, Modules(Modules)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<FST_ShipModule> Modules;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	//FST_ShipModule TestStruct;
};



UCLASS()
class SPACEKATANA_POC_API UDataHolder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


};

