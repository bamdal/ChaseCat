// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_Item.h"

#include "ChaseCat/ChaseCatCharacter.h"
#include "ChaseCat/JMS_MassGameInstance.h"
#include "Components/AudioComponent.h"

// Sets default values
AJMS_Item::AJMS_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetRelativeRotation(FRotator(0, -90.0f, 0));
	Mesh->SetCollisionProfileName(TEXT("ItemProfile"));

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(Root);

}




bool AJMS_Item::StartGrab_Implementation()
{
	if(bPossibleGrab)
	{
		bIsGrab = true;
		AChaseCatCharacter* CatCharacter = Cast<AChaseCatCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if(CatCharacter)
		{
			USceneComponent* AttachHand = CatCharacter->GetHandAttachPoint();
			if(AttachHand!=nullptr)
			{
				// 콜리전 끄기
				Mesh->SetSimulatePhysics(false);
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				RootComponent->AttachToComponent(AttachHand,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				return true;
			}
		}
	
	}
	return false;
}

void AJMS_Item::EndGrab()
{
	if(bIsGrab)
	{
		bIsGrab = false;

		RootComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		Mesh->SetCollisionProfileName(TEXT("ItemProfile"));
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->SetSimulatePhysics(true);

		
	}
	
}

void AJMS_Item::ThrowItem()
{
	Mesh->AddImpulse(GetActorForwardVector()*1000,NAME_None,true);
	ThrowItem_Implementation();
}

void AJMS_Item::Dissolve(float DissolveTime)
{
	int i = 0;
	for (auto Element : Mesh->GetMaterials())
	{
		auto val = Mesh->CreateDynamicMaterialInstance(i,Element,Mesh->GetMaterialSlotNames()[i]);

		val->SetScalarParameterValue(FName("Dissolve"),DissolveTime);
		i++;
	}
}

void AJMS_Item::PlayVoice(USoundWave* NewSound)
{
	Audio->SetSound(NewSound);
	Audio->Play();
}

void AJMS_Item::StopVoice()
{
	Audio->Stop();
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

