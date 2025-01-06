// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlimeHotelCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "NPCScr/NPCClass.h"
#include "RoomManager/RoomManager.h"
#include "Public/PropsScr/PropsActor.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);
//RoadMap
/* order
 * 	— UI
 *	— UI Dialog ✅
 *	— Game Master
 *		— UI for shoop keeper, Hotel, Clean ✅ / WIP Clean
 */
//////////////////////////////////////////////////////////////////////////
// ASlimeHotelCharacter

ASlimeHotelCharacter::ASlimeHotelCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ASlimeHotelCharacter::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////// Input

void ASlimeHotelCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASlimeHotelCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlimeHotelCharacter::Look);

		EnhancedInputComponent->BindAction(ShootingAction, ETriggerEvent::Completed, this, &ASlimeHotelCharacter::CastRay);

		EnhancedInputComponent->BindAction(ItemChoseAction, ETriggerEvent::Completed, this, &ASlimeHotelCharacter::ChoseItem);

		EnhancedInputComponent->BindAction(ItemDropAction, ETriggerEvent::Completed, this, &ASlimeHotelCharacter::DropItem);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASlimeHotelCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASlimeHotelCharacter::ChoseItem()
{
	HoldItem = Invetory->GetItem();
}

void ASlimeHotelCharacter::DropItem()
{
	if (HoldItem != nullptr)
		Invetory->DeleteItem();
}

void ASlimeHotelCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASlimeHotelCharacter::CastRay()
{
	if(InBuildingMode)
		return;

	if(IsInDialog)
	{
		NPCTalkWith->DialogDone = false;
		NPCTalkWith->IsTalk = false;
		IsInDialog = false;
		NPCTalkWith->BP_Talk();
		return;
	}
	
	FVector Start = GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector Forw = GetFirstPersonCameraComponent()->GetForwardVector();

	Start = FVector(Start.X + (Forw.X * 100), Start.Y+ (Forw.Y * 100), Start.Z+ (Forw.Z * 100));
	FVector end = Start + Forw * 120;

	if(GetWorld())
	{
		bool HitBool = GetWorld()->LineTraceSingleByChannel(HitDirection,Start,end,ECC_GameTraceChannel1,FCollisionQueryParams(),FCollisionResponseParams());
		DrawDebugLine(GetWorld(),Start,end,FColor::Red,false,8.50,1,1);
		if(HitBool)
		{
			auto c = HitDirection.GetActor();
			if(c->ActorHasTag("NPC"))
			{
				UE_LOG(LogTemp, Display, TEXT("NPC Found"));
				NPCTalkWith = Cast<ANPCClass>(c);
				NPCTalkWith->DialogDone = false;

				if (NPCTalkWith->EconomyComp)
				{
					NPCTalkWith->ShowUIForShop();
				}

				if (NPCTalkWith->IsCanTalk)
				{
					//if (NPCTalkWith->IsTalk == false)
					{
						IsInDialog = true;
						auto b = SetCameraToNPC(c->GetActorLocation());
						if (!b)
						{
							IsInDialog = false;
							UE_LOG(LogTemp, Error, TEXT("ERROR NPC CAN'T TALK"));
						}

						GetLineToDialog();
					}
				}
				// TO DO: ADD UI Like in the dialog
			}
			if(c->ActorHasTag("Prop"))
			{
				UE_LOG(LogTemp, Display, TEXT("Prop Found"));
				auto PCast = Cast<APropsActor>(c);
				if (HoldItem == nullptr)
				{
					Invetory->SetHoldItem(PCast);
					c->Destroy();
				}
			}
			if (c->ActorHasTag("Room"))
			{
				UE_LOG(LogTemp, Display, TEXT("Start Clearing"));
				auto Ro = Cast<ARoomManager>(c);
				Ro->StartClearing();
			}
		}
	}
}
//TO DO 
bool ASlimeHotelCharacter::SetCameraToNPC(FVector PosNPC)
{
	if(!IsInDialog)
		return false;

	UCameraComponent* Camera = GetFirstPersonCameraComponent();

	const FVector DirectionToNPC = (PosNPC - GetActorLocation()).GetSafeNormal();
	const FRotator TargetRotation = DirectionToNPC.Rotation();

	Camera->SetWorldRotation(TargetRotation);
	return true;
}

void ASlimeHotelCharacter::GetLineToDialog()
{
	if(NPCTalkWith->IsTalk)
		NPCTalkWith->IsTalk = false;

	NPCTalkWith->IsTalk = true;
	NPCTalkWith->RandomLineToTalk();
}
