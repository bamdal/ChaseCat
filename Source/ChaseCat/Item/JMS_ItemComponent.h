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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* FocusActivateArea;

	UPROPERTY()
	UJMS_ItemFocus* ItemFocusWidget;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Item")
	AChaseCatCharacter* PlayerCharacter;
	

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float AreaRadius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	bool FocusRotateFree = false;
	
	UPROPERTY()
	FRotator InitialWidgetRotation; 

	UPROPERTY()
	float InitialWidgetRotateWeight = 0.5f;

	UFUNCTION(BlueprintCallable, meta=(DisplayName = "Interaction"), Category = "Interaction")
	void Interaction_Implementation();

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
