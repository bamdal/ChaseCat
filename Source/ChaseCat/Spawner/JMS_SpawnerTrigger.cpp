// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_SpawnerTrigger.h"

#include "JMS_Spawner.h"
#include "ChaseCat/ObjectPool/JMS_ChildPoolManager.h"
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

	Capsule->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::AJMS_SpawnerTrigger::OnComponentBeginOverlap);
	Capsule->OnComponentEndOverlap.AddDynamic(this,&AJMS_SpawnerTrigger::OnComponentEndOverlap);
	
}

// Called every frame
void AJMS_SpawnerTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




void AJMS_SpawnerTrigger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (AJMS_Spawner* Element : GetSpawner)
	{
		Element->Startspawning(E_ChildPoolName::Cat,Element->GetActorLocation()+FVector::UpVector*10,Element->GetActorRotation(),-1);
	}
}

void AJMS_SpawnerTrigger::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}