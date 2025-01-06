// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCScr/NPCClass.h"

// Sets default values
ANPCClass::ANPCClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ANPCClass::RandomLineToTalk()
{
	int a = FMath::RandRange(0, Messages.Num()-1);
	MessToShow = Messages[a];

	BP_Talk();
}

// Called when the game starts or when spawned
void ANPCClass::BeginPlay()
{
	Super::BeginPlay();

	if (Target == nullptr)
		IsCanMove = false;
}

void ANPCClass::StopTlak()
{
	IsTalk = false;
	DialogDone = true;
}

// Called every frame
void ANPCClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

