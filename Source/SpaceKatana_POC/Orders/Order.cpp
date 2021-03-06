// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "Order.h"






UOrder::UOrder()
{
	Buyer = nullptr;
	PowerCost = 0.f;
	PRCost = 0.f;
	bIsResolved = false;
	bIsCancelled = false;
	TurnExcTime = 1;
	TurnsLeft = TurnExcTime;
	OrderLocation = FVector(0.f, 0.f, 0.f);
	X = 0;
	Y = 0;
	Z = 0;
	WorldRef = nullptr;
	Sequence = 1;
}


UOrder::~UOrder()
{

}


void UOrder::ResolveOrder()
{
	bIsResolved = true;
	OnOrderResolved.Broadcast();
	// Remove self
	//ConditionalBeginDestroy();
}


void UOrder::CancelOrder()
{
	bIsCancelled = true;
	OnOrderCancelled.Broadcast();
}