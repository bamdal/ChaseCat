// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JMS_AmbassadorWindow.generated.h"

/**
 * 
 */
UCLASS()
class CHASECAT_API UJMS_AmbassadorWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void ToggleTextView();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartDialogueText(FName Name);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NextDialogueText();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndDialogueText();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName NextTextName = TEXT("");
};
