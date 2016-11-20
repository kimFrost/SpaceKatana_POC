// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "GameModeBattle.h"
#include "OrderSpawnModule.h"
#include "OrderVisualizer.h"


// Sets default values
AOrderVisualizer::AOrderVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OrderType = EOrderType::SpawnModule;
	Order = nullptr;
}



void AOrderVisualizer::Init()
{
	if (IsValid(Order))
	{
		//FTimerDelegate TimerDel;
		//TimerDel.BindUFunction(this, FName("Destroy"), false, false);

		/*
		FScriptDelegate ScriptDel;
		ScriptDel.BindUFunction(this, FName("Destroy"));
		Order->OnOrderResolved.Add(ScriptDel);
		*/

		//Order->OnOrderResolved.AddDynamic(this, &AOrderVisualizer::Destroy);
		//Order->OnOrderResolved.AddDynamic(this, &AOrderVisualizer::RemoveVisualizer);
		Order->OnOrderResolved.AddUniqueDynamic(this, &AOrderVisualizer::OnOrderResolved);
	}
}

void AOrderVisualizer::OnOrderResolved()
{
	if (IsValid(Order))
	{
		AGameModeBattle* GameMode = Cast<AGameModeBattle>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			UOrderSpawnModule* SpawnOrder = Cast<UOrderSpawnModule>(Order);
			if (SpawnOrder)
			{
				GameMode->SpawnFlyInModule(SpawnOrder->ModuleClassToSpawn, SpawnOrder->X, SpawnOrder->Y, SpawnOrder->FlyInDirection, SpawnOrder->Buyer);
			}
			else 
			{
				
			}
		}
	}

	Destroy();
}


// Called when the game starts or when spawned
void AOrderVisualizer::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AOrderVisualizer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

