// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime_Manager/SlimeManager.h"
#include "NPCScr/NPCClass.h"
// Sets default values for this component's properties
USlimeManager::USlimeManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void USlimeManager::SetTypesOfSlime()
{
	int index = rand() % 2;
	TypeSlime = static_cast<ETypesSlime>(index);
	Happiness -= rand() % 100;
	SetMeshAndMaterial();
}

void USlimeManager::CheckAllItemsInRoom(ARoomManager* Room)
{
	auto Items = Room->GetItemsForRoom();
	for (auto x : Items)
	{
		if (FindItem(ItemDilike, x->ItemsTheme))
		{
			Happiness -= 0.25;
		}
		if (FindItem(ItemLike, x->ItemsTheme))
		{
			Happiness += 0.25;
		}
	}
}

void USlimeManager::SetMeshAndMaterial()
{
	if (ActorOwner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor Owner is not set"));
		return;
	}
	
	if (AllSlimeSkeletalMesh.Num() < 3 || AllSlimeMaterials.Num() < 3)
	{
		UE_LOG(LogTemp, Error, TEXT("Must be more then 2 skelete mesh or Matreils !"));
		return;
	}

	// Convert enum to array index
    int TypeIndex = static_cast<int>(TypeSlime);
    
    // Set mesh and material
    ActorOwner->SkeletaMeshComp->SetMaterial(0, AllSlimeMaterials[TypeIndex]);
    ActorOwner->SkeletaMeshComp->SetSkeletalMesh(AllSlimeSkeletalMesh[TypeIndex]);

}

bool USlimeManager::FindItem(const TArray<EItmesLikeNDisLike>& FormList, EItmesTheme ToFind)
{
	int32 ItemToFind = static_cast<int32>(ToFind);
	for (const auto& Item : FormList)
	{
		if (ItemToFind == static_cast<int32>(Item))
			return true;
	}
	return false;
}

// Called when the game starts
void USlimeManager::BeginPlay()
{
	Super::BeginPlay();
	SetTypesOfSlime();
	// ...
	
}


// Called every frame
void USlimeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

