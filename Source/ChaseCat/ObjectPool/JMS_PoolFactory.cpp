// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PoolFactory.h"

#include "JMS_ChildPoolManager.h"

// Sets default values
AJMS_PoolFactory::AJMS_PoolFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

void AJMS_PoolFactory::InitializePool()
{
	SpawnedChildPoolManagers.SetNum(PoolingActors.Num());
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

AJMS_ChildPawn* AJMS_PoolFactory::GetFactoryObject(E_ChildPoolName ObjectName, FVector Location, FRotator Rotation, float Life)
{
	for (AJMS_ChildPoolManager* Element : SpawnedChildPoolManagers)
	{
		if(Element->ManagerPoolName == ObjectName)
		{
			return Element->GetChild(Location,Rotation);
		}
	}
	return nullptr;
}


// Called when the game starts or when spawned
void AJMS_PoolFactory::BeginPlay()
{
	Super::BeginPlay();
	InitializePool();
}

// Called every frame
void AJMS_PoolFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

