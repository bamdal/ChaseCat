// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_ChildPawn.h"

#include "JMS_ChildPoolManager.h"

// Sets default values
AJMS_ChildPawn::AJMS_ChildPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsEnabled = false;
	IsVisible(bIsEnabled);


}

/**
 * 오브젝트 활성화 후 위치 재설정
 * @param Location 
 * @param Rotation 
 */
void AJMS_ChildPawn::ObjectEnabled(FVector Location, FRotator Rotation)
{
	bIsEnabled = true;
	SetActorLocation(Location);
	SetActorRotation(Rotation);
	IsVisible(bIsEnabled);
}

/**
 * 부모 재설정후 Manager에 활성화 여부 재설정후 비활성화
 */
void AJMS_ChildPawn::ObjectDisabled()
{
	bIsEnabled = false;
	// 부모가 팩토리가 아닐경우
	if(this->GetParentActor() != GetChildPoolManager())
	{
		this->AttachToActor(GetChildPoolManager(),FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
	GetChildPoolManager()->EnablePoolChilds.Remove(GetPoolIndex());
	GetChildPoolManager()->DisablePoolChilds.Enqueue(this);
	SetChildLife(-1);
	bHasLife = false;
	IsVisible(bIsEnabled);
}

/**
 * 활성화 여부 알기
 * @return 
 */
bool AJMS_ChildPawn::IsEnabled()
{
	return bIsEnabled;
}


/**
 * 소환시 한번만 불린다.
 * 인덱스 설정과 이름 재설정
 * @param index 
 */
void AJMS_ChildPawn::SetPoolIndex(int32 index)
{
	PoolIndex = index;
	FString name= this->GetName();
	FString NewName = FString::Printf(TEXT("%s_%d"), *name, index);

	this->Rename(*NewName);
	this->SetActorLabel(NewName);
}

int32 AJMS_ChildPawn::GetPoolIndex()
{
	return PoolIndex;
}

void AJMS_ChildPawn::SetChildPoolManager(class AJMS_ChildPoolManager* ChildPoolManager)
{
	ChildManager = ChildPoolManager;
}

AJMS_ChildPoolManager* AJMS_ChildPawn::GetChildPoolManager()
{
	return ChildManager;
}

void AJMS_ChildPawn::SetChildLife(float Life)
{
	
	ChildLife = Life;
	bHasLife =true;
}

/**
 * 게임내 활성, 비활성화 - 시야, 콜리전, tick
 * @param visible 활성 여부
 */
void AJMS_ChildPawn::IsVisible(bool visible)
{
	SetActorHiddenInGame(!visible);
	SetActorEnableCollision(visible);
	SetActorTickEnabled(visible);
}

// Called when the game starts or when spawned
void AJMS_ChildPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJMS_ChildPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bHasLife)
	{
		ChildLife -= DeltaTime;
		if(ChildLife < 0)
			ObjectDisabled();
	}
}

// Called to bind functionality to input
void AJMS_ChildPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

