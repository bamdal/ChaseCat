// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_UI_DestinationComponent.h"

#include "ChaseCat/JMS_MassGameInstance.h"

// Sets default values for this component's properties
UJMS_UI_DestinationComponent::UJMS_UI_DestinationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


bool UJMS_UI_DestinationComponent::FinishQuest()
{
	bool finish = MGI->NextDestinationIndex();
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Emerald,FString::Printf(TEXT("%i"),finish));
	if(finish)
	{
		return true;
	}
	else
	{
		MGI->RemoveAllDestinationComponent();
		return false;
	}

}

// Called when the game starts
void UJMS_UI_DestinationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// 내 게임인스턴스에 델리게이트에 목표지점 설정
	MGI = Cast<UJMS_MassGameInstance>(GetWorld()->GetGameInstance());
	MGI->AddActiveDestinationDelegate.ExecuteIfBound(this);
}


// Called every frame
void UJMS_UI_DestinationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



