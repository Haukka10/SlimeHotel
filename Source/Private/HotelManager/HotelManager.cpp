// Fill out your copyright notice in the Description page of Project Settings.

#include "HotelManager/HotelManager.h"
#include "RoomManager/RoomManager.h"

// Sets default values
AHotelManager::AHotelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AHotelManager::GetRoomComp(TArray<ARoomManager*> AllRoomsActor)
{
	for (auto x : AllRoomsActor)
	{
		AllRooms.Add(x);
	}
	GetAvgSatisfaction();
}

// Called when the game starts or when spawned
void AHotelManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHotelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHotelManager::GetAvgSatisfaction()
{
	int32 Center = (AllRooms.Num()/2);
	if (AllRooms.Num() / 2 == 0)
	{
		AllRoomsSatisfactionAvg = (AllRooms[Center]->Satisfaction + AllRooms[Center++]->Satisfaction) / 2;
	}
	else
	{
		AllRoomsSatisfactionAvg = AllRooms[Center]->Satisfaction;
	}
}

