// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeHotel/Public/EQScr/Equipment.h"

// Sets default values for this component's properties
UEquipment::UEquipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UEquipment::SetHoldItem(APropsActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Add Item %s"), *Actor->GetName());
	
	HoldItems = Actor;
}

APropsActor* UEquipment::GetItem()
{
	return HoldItems;
}

void UEquipment::DeleteItem()
{
	HoldItems = nullptr;
}


// Called when the game starts
void UEquipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

