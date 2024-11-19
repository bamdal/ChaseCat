// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JMS_ItemFocus.generated.h"

/**
 * 
 */
UCLASS()
class CHASECAT_API UJMS_ItemFocus : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Item")
	float AlphaDuration=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Item")
	float AlphaWeight=5;

	UFUNCTION()
	void OnEnable();

	UFUNCTION()
	void OnDisable();

	UFUNCTION()
	void TimerAlpha(bool Up);

	// 시그모이드 함수
	float Sigmoid(float Time, float K, float T0, float YMin =0, float YMax=1);

	float CurrentTime;
	
	virtual void NativeOnInitialized() override;
	FTimerHandle TimerAlphaHandle;

	
};
