// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomManager/RoomManager.h"
#include "HotelManager.generated.h"

UCLASS()
class SLIMEHOTEL_API AHotelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHotelManager();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Prop")
		int AllRoomsSatisfactionAvg = 0;

	UFUNCTION(BlueprintCallable)
		void GetRoomComp(TArray<ARoomManager*> AllRoomsActor);

	UFUNCTION(BlueprintCallable)
		void GetAvgSatisfaction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		TArray<ARoomManager*> AllRooms;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

};
