// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceKatana_POC.h"
#include "DataHolder.h"
#include "Order.h"






UOrder::UOrder()
{
	Buyer = nullptr;
	Cost = 100.f;
	TurnExcTime = 1;
	TurnsLeft = TurnExcTime;
	OrderLocation = FVector(0.f, 0.f, 0.f);
	X = 0;
	Y = 0;
}


UOrder::~UOrder()
{

}
