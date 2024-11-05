// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_Spawner.h"

// Sets default values
AJMS_Spawner::AJMS_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJMS_Spawner::BeginPlay()
{
	Super::BeginPlay();

	if(BeginSpawn)
	{
		
	}
}

// Called every frame
void AJMS_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

