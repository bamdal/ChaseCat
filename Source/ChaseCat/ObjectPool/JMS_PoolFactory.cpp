// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PoolFactory.h"

#include "JMS_ChildPoolManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AJMS_PoolFactory::AJMS_PoolFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

void AJMS_PoolFactory::InitializePool()
{
	for (TSubclassOf<AJMS_ChildPoolManager> Element : PoolingActors)
	{
		CreatePoolChild(Element);
		
	}
}

void AJMS_PoolFactory::CreatePoolChild(TSubclassOf<AJMS_ChildPoolManager> FactoryManager)
{
	if (FactoryManager != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "Creating Actor");
		AJMS_ChildPoolManager* SpawnedChild = GetWorld()->SpawnActor<AJMS_ChildPoolManager>(FactoryManager, this->GetActorLocation(), FRotator::ZeroRotator);
		SpawnedChild->AttachToActor(this,FAttachmentTransformRules::SnapToTargetIncludingScale);
		SpawnedChild->InitializePawnChild();
		SpawnedChildPoolManagers.Add(SpawnedChild);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "null PoolChildClass");
	}
}

/**
 * Enum값에 맞는 매니저로 연결해줌
 * @param ObjectName 
 * @param Location 
 * @param Rotation 
 * @param Life 
 * @return 잘못되면 nullptr
 */
AJMS_ChildPawn* AJMS_PoolFactory::GetFactoryObject(E_ChildPoolName ObjectName, FVector Location, FRotator Rotation, float Life)
{
	for (AJMS_ChildPoolManager* Element : SpawnedChildPoolManagers)
	{
		if(Element->ManagerPoolName == ObjectName)
		{
			return Element->GetChild(Location,Rotation,Life);
		}
	}
	return nullptr;
}

TArray<AJMS_ChildPawn*> AJMS_PoolFactory::GetFactoryMultiObject(E_ChildPoolName ObjectName, FVector Location, FRotator Rotation,
	int32 Count, float Life)
{
	TArray<AJMS_ChildPawn*> FactoryObjects;
	for(int i =0; i< Count;i++)
	{
		FVector newLocation = Location + UKismetMathLibrary::RandomUnitVector()*200;
		newLocation.Z = Location.Z;
		FactoryObjects.Add(GetFactoryObject(ObjectName,newLocation,Rotation,Life));
	}
	return FactoryObjects;
}

void AJMS_PoolFactory::DespawnPoolChild(E_ChildPoolName ObjectName)
{
	for (AJMS_ChildPoolManager* Element : SpawnedChildPoolManagers)
	{
		if(Element->ManagerPoolName == ObjectName)
		{
			return Element->DespawnAllChild();
		}
	}
}


// Called when the game starts or when spawned
void AJMS_PoolFactory::BeginPlay()
{
	Super::BeginPlay();
	InitializePool();
}


