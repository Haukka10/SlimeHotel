// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PropsScr/PropsActor.h"
#include "RoomManager.generated.h"

UCLASS()
class SLIMEHOTEL_API ARoomManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomManager();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Room Status")
		float Satisfaction = 0.0F;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Room Status")
		float cleanlinessRoom = MaxcleanlinessRoom;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Room Status")
		TArray<UMaterial*> DirtSkins;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Room Status")
		TArray<FTransform> DirtPOS;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Room Status")
		TArray<AActor*> Dirts;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Room Status")
		TArray<AActor*> DirtsToDelete;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Room Status")
		float CostForRent = 0;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Room Status")
		bool IsBusy = false;

	UFUNCTION(BlueprintCallable,Category="Room Status|Func")
		float GetRoomCost(APropsActor* NewItem);

	TArray<APropsActor*> GetItemsForRoom();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		TArray<APropsActor*> AllItems;
		
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Room Status")
		float MaxcleanlinessRoom = 100.0F;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Room Status")
		TMap<FString, APropsActor*> PropsInRoom;

	UFUNCTION(BlueprintCallable, Category="Find All Items")
		void AddItemsToListRoom(APropsActor* Prop);

	UFUNCTION(BlueprintCallable, Category="Cleanliness|Check")
		void CheckCleanliness();
	UFUNCTION(BlueprintCallable, Category="Satisfacti|Check")
		void CheckSatisfactionOfRoom();

	UFUNCTION(BlueprintImplementableEvent, Category="Cleanliness|Respawn")
		void RespawnDirty();

	UFUNCTION(BlueprintImplementableEvent, Category="Cleanliness|Respawn")
		void StopMovePlayer(float Time);

	UFUNCTION(BlueprintCallable,Category="Room|Clearing")
		void StartClearing();

private:
	UFUNCTION(Category = "a")
		float SatisfactionOfRoom();
};
