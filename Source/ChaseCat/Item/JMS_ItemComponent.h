// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaseCat/Interface/JMS_Interaction.h"
#include "Components/SceneComponent.h"
#include "JMS_ItemComponent.generated.h"


class AChaseCatCharacter;
class USphereComponent;
class UJMS_ItemFocus;
class UWidgetComponent;
class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionEvent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CHASECAT_API UJMS_ItemComponent : public USceneComponent, public IJMS_Interaction
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UJMS_ItemComponent();

	// 플레이어 상호작용 가능한 박스의 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UBoxComponent* BoxComponent;

	// 강조 UI 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UWidgetComponent* WidgetComponent;

	// 플레이어가 인지할수있는 범위
	UPROPERTY(VisibleAnywhere)
	USphereComponent* FocusActivateArea;

	UPROPERTY()
	UJMS_ItemFocus* ItemFocusWidget;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Item")
	AChaseCatCharacter* PlayerCharacter;
	

	
	// UI 인지 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float AreaRadius = 300.0f;

	// 화면에 띄워주는 목표 UI가 제한없이 회전하게 한다
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool FocusRotateFree = false;

	// 체크시 상호작용후 강조UI가 사라진다
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool IsDisposable = false;
	
	UPROPERTY()
	FRotator InitialWidgetRotation; 

	UPROPERTY()
	float InitialWidgetRotateWeight = 0.5f;

	// 인터페이스를 통해 호출되는 상호작용 호출
	UFUNCTION(BlueprintCallable, meta=(DisplayName = "Interaction"), Category = "Interaction")
	void Interaction_Implementation();

	// 상호작용 호출이 BP로 연계될수있게하는 이벤트
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEvent OnInteractionEvent;

	

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnComponentEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	

	/*
	 * 1. 플레이어가 근처로 오면 상호작용가능하다 표현하게 UI로 보이기
	 */

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
