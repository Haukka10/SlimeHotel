// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropsScr/PropsActor.h"
#include "HotelManager/HotelManager.h"
#include "Components/ActorComponent.h"
#include "ActorCompEconomy.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLIMEHOTEL_API UActorCompEconomy : public UActorComponent
{
	
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorCompEconomy();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool IsSelling = false;
		
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		float CurrentMoney = 100;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		bool IsPlayer = true;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		float DivCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MinElements = 5))
		TArray<APropsActor*> ItemsToSeles;

	UFUNCTION(BlueprintCallable)
		void BuyAItem(APropsActor* ItemToBuy, FVector PlayerPos);

	UFUNCTION(BlueprintCallable)
		void GetHotelMang(AHotelManager* HotelMag);

	UFUNCTION(BlueprintCallable)
		AHotelManager* SetHotelMang();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		AHotelManager* p_HotelManager = nullptr;

	UFUNCTION(BlueprintCallable)
		void SetCost();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UFUNCTION()
		float SetCostRand(APropsActor* Props);

		
};
