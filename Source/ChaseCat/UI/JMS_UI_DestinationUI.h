// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JMS_UI_DestinationUI.generated.h"

class UJMS_UI_DestinationComponent;
/**
 * 
 */
UCLASS()
class CHASECAT_API UJMS_UI_DestinationUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FVector2D GetDestinationUILocation(UJMS_UI_DestinationComponent* DestinationComponent);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDestinationComponent(UJMS_UI_DestinationComponent* DestinationComponent);

protected:

	
};
