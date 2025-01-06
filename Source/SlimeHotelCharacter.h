// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NPCScr/NPCClass.h"
#include "Public/EQScr/Equipment.h"
#include "SlimeHotelCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASlimeHotelCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ShootingAction;
	
public:
	ASlimeHotelCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Invetory", meta = (AllowPrivateAccess = "true"))
	int Index = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Invetory", meta = (AllowPrivateAccess = "true"))
	APropsActor* HoldItem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ItemChoseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ItemDropAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Invetory", meta = (AllowPrivateAccess = "true"))
	UEquipment* Invetory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	ANPCClass* NPCTalkWith = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Invetory", meta = (AllowPrivateAccess = "true"))
	bool InBuildingMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ray Cast|hit", meta = (AllowPrivateAccess = "true"))
	FHitResult HitDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	bool IsInDialog = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Camera)
	int NextLine = 0;

	UFUNCTION(BlueprintCallable, Category="Drop")
		void DropItem();
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	UFUNCTION()
		void ChoseItem();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void CastRay();

	bool SetCameraToNPC(FVector PosNPC);

	void GetLineToDialog();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

