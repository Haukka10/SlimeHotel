// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RoomManager/RoomManager.h"
#include "NPCScr/NPCClass.h"
#include "SlimeManager.generated.h"

UENUM(BlueprintType)
enum class ETypesSlime : uint8
{
	Good = 0,
	Normal = 1,
	Bad = 2
};

UENUM(BlueprintType)
enum class EItmesLikeNDisLike : uint8
{
	Normal = 0,
	GodItmes = 1,
	EvliItems = 2,
	LavaItems = 3,
	StoneItems = 4,
	IceItems = 5
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLIMEHOTEL_API USlimeManager : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	USlimeManager();

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category = "Actor Owner")
	ANPCClass* ActorOwner = nullptr;

	UPROPERTY(BlueprintReadWrite,VisibleDefaultsOnly,Category = "Types Berv")
	ETypesSlime TypeSlime = ETypesSlime::Normal;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Types Berv")
	TArray<EItmesLikeNDisLike> ItemDilike;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Types Berv")
	TArray<EItmesLikeNDisLike> ItemLike;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Stats")
	float Happiness = 100.0F;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Stats")
	float Money = rand() % 1000;

	UFUNCTION(BlueprintCallable,Category = "Types Brev")
	void SetTypesOfSlime();

	UPROPERTY(EditAnywhere, Category = "Meshs|Data-Mesh", meta = (MinElements = 3))
	TArray<USkeletalMesh*> AllSlimeSkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Meshs|Data-Materials", meta = (MinElements = 3))
	TArray<UMaterial*> AllSlimeMaterials;

	UFUNCTION(BlueprintCallable,Category = "Check| Items")
	void CheckAllItemsInRoom(ARoomManager* Room);

private:

	UFUNCTION(BlueprintCallable,Category = "Meshs|Set")
	void SetMeshAndMaterial();

	UFUNCTION()
	bool FindItem(const TArray<EItmesLikeNDisLike>& FormList, EItmesTheme ToFind);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
