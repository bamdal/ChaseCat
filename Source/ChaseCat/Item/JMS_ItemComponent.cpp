// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_ItemComponent.h"

#include <cmath>

#include "JMS_ItemFocus.h"
#include "ChaseCat/ChaseCatCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UJMS_ItemComponent::UJMS_ItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// 아이템 상호작용 범위
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	BoxComponent->SetupAttachment(this);

	// 아이템 강조 효과 위젯
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	WidgetComponent->SetupAttachment(BoxComponent);
	WidgetComponent->SetDrawAtDesiredSize(true);
	
	// 플레이어 인지 범위
	FocusActivateArea = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionFocusArea"));
	FocusActivateArea->SetSphereRadius(AreaRadius);
	FocusActivateArea->SetupAttachment(BoxComponent);
	// ...
}

/**
 * 상호작용 기능
 */

void UJMS_ItemComponent::Interaction_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
								 FString::Printf(TEXT("Find %s"), *this->GetAttachmentRoot()->GetName()));
	OnInteractionEvent.Broadcast();
}


// Called when the game starts
void UJMS_ItemComponent::BeginPlay()
{
	Super::BeginPlay();

	WidgetComponent->InitWidget();

	// interaction 가능한 UI 초기 좌표 설정
	const FVector box = BoxComponent->GetScaledBoxExtent();
	WidgetComponent->SetRelativeLocation(FVector(box.X, 0, 0));
	WidgetComponent->SetRelativeScale3D(FVector(1, box.Y / 50, box.Z / 50));
	//BoxComponent->SetRelativeRotation((this->GetAttachmentRoot()->GetRelativeRotation()).GetInverse());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%f, %f, %f"), box.X, box.Y, box.Z));

	// 플레이어 인지 범위 오버랩
	FocusActivateArea->OnComponentBeginOverlap.AddDynamic(this, &UJMS_ItemComponent::OnComponentBeginOverlap);
	FocusActivateArea->OnComponentEndOverlap.AddDynamic(this, &UJMS_ItemComponent::OnComponentEndOverlap);
	// 사용자 위젯 접근해 값 넣어두기

	UUserWidget* UserWidget = WidgetComponent->GetUserWidgetObject();

	if (UserWidget != nullptr)
	{
		ItemFocusWidget = Cast<UJMS_ItemFocus>(UserWidget);
	}

	// 포커스 빌보드 기능을 위한 초기 회전 위치 설정
	InitialWidgetRotation = WidgetComponent->K2_GetComponentRotation();


	
}


// Called every frame
void UJMS_ItemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 포커스 위젯이 플레이어 방향으로 살짝만 돌려보기
	if(PlayerCharacter != nullptr)
	{
		
		FRotator WidgetToPlayerRotator = UKismetMathLibrary::FindLookAtRotation(WidgetComponent->K2_GetComponentLocation(),PlayerCharacter->GetActorLocation());
		
		if(FocusRotateFree)
		{
			WidgetComponent->SetWorldRotation(WidgetToPlayerRotator);
		}
		else
		{
			WidgetComponent->SetWorldRotation(UKismetMathLibrary::RLerp(InitialWidgetRotation,WidgetToPlayerRotator,InitialWidgetRotateWeight,true));
			
		}
	}
}


/**
 * 플레이어가 범위안에 들어옴
 * @param OverlappedComponent 
 * @param OtherActor 
 * @param OtherComp 
 * @param OtherBodyIndex 
 * @param bFromSweep 
 * @param SweepResult 
 */
void UJMS_ItemComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                 const FHitResult& SweepResult)
{
	if (OverlappedComponent && OtherActor)
	{
		PlayerCharacter = Cast<AChaseCatCharacter>(OtherActor);
		if (PlayerCharacter != nullptr)
		{
			if (ItemFocusWidget != nullptr)
			{
				
				ItemFocusWidget->OnEnable();
			}
		}
	}
}

/**
 * 플레이어가 나감
 * @param OverlappedComponent 
 * @param OtherActor 
 * @param OtherComp 
 * @param OtherBodyIndex 
 */
void UJMS_ItemComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappedComponent && OtherActor)
	{
		if (PlayerCharacter==OtherActor)
		{
			if (ItemFocusWidget != nullptr)
			{
				PlayerCharacter=nullptr;
				ItemFocusWidget->OnDisable();
			}
		}
	}
}
