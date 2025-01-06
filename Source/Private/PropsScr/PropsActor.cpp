// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeHotel/Public/PropsScr/PropsActor.h"
// Sets default values
APropsActor::APropsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetSatisfactionOfItem();
}

// Called when the game starts or when spawned
void APropsActor::BeginPlay()
{
	Super::BeginPlay();

}

void APropsActor::GetSatisfactionOfItem()
{
	SatisfactionOfItem = FMath::RandRange(0.1F, 100.0F);
	IsLuxury = FMath::RandBool();
}

// Called every frame
void APropsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

