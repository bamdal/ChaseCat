// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_SpawnerTrigger.h"

#include "Components/CapsuleComponent.h"

// Sets default values
AJMS_SpawnerTrigger::AJMS_SpawnerTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 초기화
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	    
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(Root);
    

	
}

// Called when the game starts or when spawned
void AJMS_SpawnerTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJMS_SpawnerTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

