// Fill out your copyright notice in the Description page of Project Settings.


#include "EconomyManagerScr/ActorEconomyLocal/ActorCompEconomy.h"

// Sets default values for this component's properties
UActorCompEconomy::UActorCompEconomy()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UActorCompEconomy::BuyAItem(APropsActor* ItemToBuy, FVector PlayerPos)
{
	if (ItemToBuy->Cost > CurrentMoney)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5F, FColor::Cyan, FString::Printf(TEXT("Not engot money (Current %f, Cost: %f)"), (CurrentMoney), (ItemToBuy->Cost)));
		return;
	}

	CurrentMoney -= ItemToBuy->Cost;
	const FRotator FR = { 0,0,0};

	auto x = GetWorld()->SpawnActor<APropsActor>(ItemToBuy->GetClass(), PlayerPos, FR);
	
}

void UActorCompEconomy::GetHotelMang(AHotelManager* HotelMag) 
{
	p_HotelManager = HotelMag;
}

AHotelManager* UActorCompEconomy::SetHotelMang()
{
	return p_HotelManager;
}

// Called when the game starts
void UActorCompEconomy::BeginPlay()
{
	Super::BeginPlay();

	if (IsPlayer)
		return;

	if (IsSelling)
	{
		
		if (ItemsToSeles.Num() <= 0)
		{
			FString Name = GetOwner()->GetFullName();
			GEngine->AddOnScreenDebugMessage(-1, 5.0F, FColor::Red, FString::Printf(TEXT("is selling is true but any items is set (Name: %s)"),*Name));
		}
	}
	
}

void UActorCompEconomy::SetCost()
{
	float SatisfactionBuffor = p_HotelManager->AllRoomsSatisfactionAvg;
	float multiplier = 0;

	for (auto& x : ItemsToSeles)
	{
		DivCost = SetCostRand(x);

		if (SatisfactionBuffor <= 50)
		{
			multiplier = (SatisfactionBuffor / 2)/100;
		}
		else
		{
			multiplier = ((SatisfactionBuffor / 2) / 100)*0.2;
		}

		if (SatisfactionBuffor < 1)
			multiplier = 1;
		
		if (x->IsLuxury)
		{
			x->Cost = FMath::RoundToFloat(FMath::RandRange(10.0F, DivCost + 15)) * multiplier;
			x->Cost += x->Cost * 0.15;
		}
		else
		{
			x->Cost = FMath::RoundToFloat(FMath::RandRange(10.0F, DivCost + 15)) * multiplier;
		}

		DivCost = 0;
	}
}


// Called every frame
void UActorCompEconomy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UActorCompEconomy::SetCostRand(APropsActor* Props)
{
	return FMath::RandRange(Props->Cost, Props->Cost + 25);
}
