// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_ChildPoolManager.h"

#include "JMS_ChildPawn.h"

// Sets default values
AJMS_ChildPoolManager::AJMS_ChildPoolManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
				SpawnedChild->SetChildPoolManager(this);
				SpawnedChild->SetPoolIndex(MaxPoolIndex);
				MaxPoolIndex++;
				DisablePoolChilds.Enqueue(SpawnedChild);
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


/**
 * 매니저에서 자식 1개 스폰시키기
 * @param Location 소환 좌표
 * @param Rotation 소환 회전(z축도 돌아감)
 * @param Life 객체 생명주기 (0미만 값이면 영구적 생존)
 * @return 소환된 객체 하나
 */
AJMS_ChildPawn* AJMS_ChildPoolManager::GetChild(FVector Location, FRotator Rotation, float Life)
{
	AJMS_ChildPawn* child = nullptr;
	DisablePoolChilds.Dequeue(child);
	// 만일 pool 이 부족하게 되면 풀을 2배로 키움
	if(child == nullptr)
	{
		MakeDoublePool();
		DisablePoolChilds.Dequeue(child);
	}
	child->ObjectEnabled(Location,Rotation);
	// 라이프를 설정했다면
	if(Life > 0)
	{
		
	}
	
	EnablePoolChilds.Emplace(child->GetPoolIndex(),child);
	return child;
}

void AJMS_ChildPoolManager::DespawnAllChild()
{
	TArray<AJMS_ChildPawn*> AllChildren;
	EnablePoolChilds.GenerateValueArray(AllChildren);
	for (AJMS_ChildPawn* Element : AllChildren)
	{
		Element->ObjectDisabled();
	}
}

/**
 * pool을 다 사용해서 없을경우 2배 리스폰
 */
void AJMS_ChildPoolManager::MakeDoublePool()
{
	InitializePawnChild();
	PoolSize*=2;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Pool Size Up");
}


// Called when the game starts or when spawned
void AJMS_ChildPoolManager::BeginPlay()
{
	Super::BeginPlay();
	
}
