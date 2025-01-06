// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SlimeHotel/Public/PropsScr/PropsActor.h"
#include "Equipment.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLIMEHOTEL_API UEquipment : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipment();

	void SetHoldItem(APropsActor* Actor);
	UFUNCTION()
	APropsActor* GetItem();
	
	UFUNCTION(BlueprintCallable, Category="Equipment")
	void DeleteItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EQ|Ammout")
	APropsActor* HoldItems;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
