// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_Item.h"

// Sets default values
AJMS_Item::AJMS_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AJMS_Item::OnInteraction_Implementation()
{
}

// Called when the game starts or when spawned
void AJMS_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJMS_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

