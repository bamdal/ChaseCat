// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_ChildPoolManager.h"

#include "JMS_ChildPawn.h"

// Sets default values
AJMS_ChildPoolManager::AJMS_ChildPoolManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AJMS_ChildPoolManager::ComeBackChild()
{
	
}

/**
 * pawn 자식 소환, 계층 설정
 */
void AJMS_ChildPoolManager::InitializePawnChild()
{
	if(PoolObject != nullptr)
	{
		for (int32 i = 0; i < PoolSize;i++)
		{
			AJMS_ChildPawn* SpawnedChild = GetWorld()->SpawnActor<AJMS_ChildPawn>(PoolObject,this->GetActorLocation(),FRotator::ZeroRotator);
			if(ManagerPoolName != E_ChildPoolName::None)
			{

				SpawnedChild->AttachToActor(this,FAttachmentTransformRules::SnapToTargetIncludingScale);
				SpawnedChild->PoolName = ManagerPoolName;
				PoolChilds.Enqueue(SpawnedChild);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Nothing EnumName");
				break;
			}

		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Nothing ObjectPool");
	}
	

}



AJMS_ChildPawn* AJMS_ChildPoolManager::GetChild(FVector Location, FRotator Rotation)
{
	AJMS_ChildPawn* child = nullptr;
	PoolChilds.Dequeue(child);
	if(child != nullptr)
	{
		MakeDoublePool();
		PoolChilds.Dequeue(child);
	}
	child->ObjectEnabled(Location,Rotation);
	child->ObjectEnabled(Location,Rotation);
	return child;
}

/**
 * pool을 다 사용해서 없을경우 2배 리스폰
 */
void AJMS_ChildPoolManager::MakeDoublePool()
{
	if(PoolObject != nullptr)
	{
		for (int32 i = 0; i < PoolSize;i++)
		{
			AJMS_ChildPawn* SpawnedChild = GetWorld()->SpawnActor<AJMS_ChildPawn>(PoolObject,this->GetActorLocation(),FRotator::ZeroRotator);
			if(ManagerPoolName != E_ChildPoolName::None)
			{

				SpawnedChild->AttachToActor(this,FAttachmentTransformRules::SnapToTargetIncludingScale);
				SpawnedChild->PoolName = ManagerPoolName;
				PoolChilds.Enqueue(SpawnedChild);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Nothing EnumName");
				break;
			}

		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Nothing ObjectPool");
	}
	PoolSize*=2;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Pool Size Up");
}


// Called when the game starts or when spawned
void AJMS_ChildPoolManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJMS_ChildPoolManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

