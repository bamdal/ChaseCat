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
 * 
 */
void AJMS_ChildPawn::ObjectDisabled()
{
	bIsEnabled = false;
	// 부모가 팩토리가 아닐경우
	if(!this->GetAttachParentActor()->IsA(AJMS_ChildPoolManager::StaticClass()))
	{
		
	}
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

void AJMS_ChildPawn::BackToFactory()
{
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

}

// Called to bind functionality to input
void AJMS_ChildPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

