// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomManager/RoomManager.h"
#include "Engine/World.h"
#include "PropsScr/PropsActor.h"

// Sets default values
ARoomManager::ARoomManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float ARoomManager::GetRoomCost(APropsActor* NewItem)
{
	auto x = NewItem->SatisfactionOfItem / AllItems.Num();
	return x;
}

TArray<APropsActor*> ARoomManager::GetItemsForRoom()
{
	return AllItems;
}

// Called when the game starts or when spawned
void ARoomManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomManager::AddItemsToListRoom(APropsActor* Prop)
{
	AllItems.Add(Prop);
	RespawnDirty();
	Satisfaction = SatisfactionOfRoom();
}

void ARoomManager::CheckCleanliness()
{
	for (size_t i = 0; i < Dirts.Num(); i++)
	{
		cleanlinessRoom -= 25;
	}
}

void ARoomManager::CheckSatisfactionOfRoom()
{
	SatisfactionOfRoom();
}

void ARoomManager::StartClearing()
{
	float TimeOfTimer = 0;
	for (auto& dirt : DirtsToDelete)
	{
		TimeOfTimer += 0.5;
		dirt->Destroy();
	}

	DirtsToDelete.Empty();
	StopMovePlayer(TimeOfTimer);
	cleanlinessRoom = MaxcleanlinessRoom;
}

float ARoomManager::SatisfactionOfRoom()
{
	float buffor = 0;
	Satisfaction = buffor;
	for (auto x : AllItems)
	{
		buffor += x->SatisfactionOfItem;
	}
	return buffor;
}
