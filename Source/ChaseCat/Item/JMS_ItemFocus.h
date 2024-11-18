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
	UJMS_ItemFocus();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Item")
	float AlphaDuration=0;

	UFUNCTION()
	void OnEnable();

	UFUNCTION()
	void OnDisable();

	UFUNCTION()
	void TimerAlpha(bool Up);

	
	FTimerHandle& TimerAlphaHandle;

	
};
