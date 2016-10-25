// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataHolder.generated.h"



//~~~~~ ENUMS ~~~~~//

UENUM(BlueprintType)
enum class EShipModuleType : uint8
{
	Square UMETA(DisplayName = "Square")
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	int32 Rating;
};



USTRUCT(BlueprintType)
struct FST_ShipModule
{
	GENERATED_USTRUCT_BODY()
public:
	FST_ShipModule(EShipModuleType Type = EShipModuleType::Square, int32 Rating = 0)
		: Type(Type)
		, Rating(Rating)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	EShipModuleType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	int32 Rating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rating")
	FST_TempMod TempMod;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	FST_ShipModule TestStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doom")
	TArray<FST_ShipModule> Modules;
};





UCLASS()
class SPACEKATANA_POC_API UDataHolder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


};

