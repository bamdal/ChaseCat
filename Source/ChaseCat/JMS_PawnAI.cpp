// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PawnAI.h"

#include "Components/CapsuleComponent.h"

// Sets default values
AJMS_PawnAI::AJMS_PawnAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AJMS_PawnAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJMS_PawnAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJMS_PawnAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

