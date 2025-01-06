// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PropsActor.generated.h"

UENUM(BlueprintType)
enum class EItmesTheme : uint8
{
	Normal = 0,
	GodItmes = 1,
	EvliItems = 2,
	LavaItems = 3,
	StoneItems = 4,
	IceItems = 5
};

UCLASS()
class SLIMEHOTEL_API APropsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropsActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PropsActor|Status", meta = (AllowPrivateAccess))
	FString NameOfItem = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PropsActor|Status", meta = (AllowPrivateAccess))
	UTexture2D* Image = nullptr;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="PropsActor|Status")
	bool IsLuxury = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PropsActor|Status", meta = (AllowPrivateAccess))
	int Cost = rand() % 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PropsActor|Status", meta = (AllowPrivateAccess))
	UStaticMesh* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PropsActor|Status", meta = (AllowPrivateAccess))
	UStaticMeshComponent* CubeComp; // Set in UE

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PropsActor|Status", meta = (AllowPrivateAccess))
	float SatisfactionOfItem = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PropsActor|Status", meta = (AllowPrivateAccess))
	EItmesTheme ItemsTheme = EItmesTheme::Normal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Category="Satisfaction")
	void GetSatisfactionOfItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
