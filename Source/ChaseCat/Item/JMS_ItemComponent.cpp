// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_ItemComponent.h"

#include "JMS_ItemFocus.h"
#include "ChaseCat/ChaseCatCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UJMS_ItemComponent::UJMS_ItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	BoxComponent->SetupAttachment(this);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	WidgetComponent->SetupAttachment(BoxComponent);
	WidgetComponent->SetDrawAtDesiredSize(true);


	FocusActivateArea = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionFocusArea"));
	FocusActivateArea->SetSphereRadius(AreaRadius);
	FocusActivateArea->SetupAttachment(BoxComponent);
	// ...
}

void UJMS_ItemComponent::Interaction_Implementation()
{
	IJMS_Interaction::Interaction_Implementation();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
	                                 FString::Printf(TEXT("Find %s"), *this->GetAttachmentRoot()->GetName()));
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%f, %f, %f"), box.X, box.Y, box.Z));

	FocusActivateArea->OnComponentBeginOverlap.AddDynamic(this, &UJMS_ItemComponent::OnComponentBeginOverlap);
	FocusActivateArea->OnComponentEndOverlap.AddDynamic(this, &UJMS_ItemComponent::OnComponentEndOverlap);
	// 사용자 위젯 접근해 값 넣어두기

	UUserWidget* UserWidget = WidgetComponent->GetUserWidgetObject();

	if (UserWidget != nullptr)
	{
		ItemFocusWidget = Cast<UJMS_ItemFocus>(UserWidget);
	}
}


// Called every frame
void UJMS_ItemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UJMS_ItemComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                 const FHitResult& SweepResult)
{
	if (OverlappedComponent && OtherActor)
	{
		if (Cast<AChaseCatCharacter>(OtherActor))
		{
			if (ItemFocusWidget != nullptr)
			{
				ItemFocusWidget->OnEnable();
			}
		}
	}
}

void UJMS_ItemComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappedComponent && OtherActor)
	{
		if (Cast<AChaseCatCharacter>(OtherActor))
		{
			if (ItemFocusWidget != nullptr)
			{
				ItemFocusWidget->OnDisable();
			}
		}
	}
}
