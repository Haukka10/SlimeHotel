// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EconomyManagerScr/ActorEconomyLocal/ActorCompEconomy.h"
#include "NPCClass.generated.h"

UCLASS()
class SLIMEHOTEL_API ANPCClass : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ANPCClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog_System")
		FString NPCName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog_System")
		bool IsCanTalk = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog_System")
		TArray<FString> Messages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog_System")
		FString MessToShow;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movemnt_AI")
		bool IsCanMove = false;

	UPROPERTY(VisibleAnywhere, Category = "Movemnt_AI")
		AActor* Target = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog_System")
		bool IsTalk = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog_System")
		bool DialogDone = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialog_System")
		int MaxLine = Messages.Num();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool isShopKeeper = false;

	UFUNCTION(BlueprintCallable, Category = "Dialog_System")
		void RandomLineToTalk();

	UFUNCTION(BlueprintImplementableEvent, Category = "Dialog_System")
		void BP_Talk();

	UFUNCTION(BlueprintImplementableEvent, Category = "Dialog_System")
		void ShowUIForShop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshComp")
		USkeletalMeshComponent* SkeletaMeshComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economy")
		UActorCompEconomy* EconomyComp = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	UFUNCTION(BlueprintCallable, Category = "Dialog_System")
		void StopTlak();
	
	//UPROPERTY(VisibleAnywhere, Category = "Movemnt_AI")
	//Add Jobs;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
