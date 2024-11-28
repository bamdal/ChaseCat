// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_Item.h"

#include "JMS_ItemComponent.h"
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

	TalikingSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	TalikingSound->SetupAttachment(Root);



}




bool AJMS_Item::StartGrab_Implementation()
{
	RootComponent->GetName();

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
				Mesh->AttachToComponent(RootComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				if(Mesh->GetRelativeRotation() == FRotator::ZeroRotator)
					Mesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 180.0f));
				RootComponent->AttachToComponent(AttachHand,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				ItemComponent->ItemFocusDisable();
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
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


		
	}
	
}

void AJMS_Item::ThrowItem()
{

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
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
	if (TalikingSound !=nullptr)
	{
		TalikingSound->SetSound(NewSound);
		TalikingSound->Play();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AJMS_Item::PlayVoice() - Audio is null."));
	}
}

void AJMS_Item::StopVoice()
{

	if (TalikingSound !=nullptr && TalikingSound->IsPlaying()) // Audio가 유효하고 재생 중일 때만 중지
	{
		TalikingSound->Stop();
	}
	else if (!TalikingSound) // Audio가 nullptr인 경우 로그 출력
	{
		UE_LOG(LogTemp, Warning, TEXT("AJMS_Item::StopVoice() - Audio is null."));
	}
}

void AJMS_Item::PlayerDefenceDropItem()
{
	if(bIsGrab)
	{
		EndGrab();
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->SetSimulatePhysics(true);
	}

}

void AJMS_Item::ItemEventTrigger_Implementation(FName EventTrigger)
{

}


void AJMS_Item::EndAmbassadorWindow_Implementation()
{
}

// Called when the game starts or when spawned
void AJMS_Item::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> ChildComponents;
	Root->GetChildrenComponents(true, ChildComponents);

	for (auto ChildComponent : ChildComponents)
	{
		UJMS_ItemComponent* FoundComponent = Cast<UJMS_ItemComponent>(ChildComponent);
		if(FoundComponent)
		{
			ItemComponent = FoundComponent;
			return;
		}
	}
	
}

// Called every frame
void AJMS_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

