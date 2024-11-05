// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_Spawner.h"

#include "JMS_MassGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "ObjectPool/JMS_ChildPawn.h"
#include "ObjectPool/JMS_PoolFactory.h"

// Sets default values
AJMS_Spawner::AJMS_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TArray<AJMS_ChildPawn*> AJMS_Spawner::StartSpawning(E_ChildPoolName E_ObjectName, FVector Location, FRotator Rotation,
	int32 Count, float Life)
{
	TArray<AJMS_ChildPawn*> ChildArrays;
	if(BeginSpawn)
	{
		UJMS_MassGameInstance* GI = Cast<UJMS_MassGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if(GI != nullptr)
		{
			AJMS_PoolFactory* PoolFactory = GI->PoolFactory;
			if(PoolFactory != nullptr)
			{
				
				ChildArrays = PoolFactory->GetFactoryMultiObject(E_ObjectName,Location,Rotation,Count,Life);

			}
		}
	}
	return ChildArrays;
}

// Called when the game starts or when spawned
void AJMS_Spawner::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AJMS_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
