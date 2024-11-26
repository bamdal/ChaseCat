// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "JMS_SelectButton.generated.h"

class UVerticalBox;
class UOverlay;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CHASECAT_API UJMS_SelectButton : public UButton
{
	GENERATED_BODY()


private:
	UPROPERTY()
	int32 Index = -1;


	UPROPERTY()
	UVerticalBox* OverlayWidget;
	
	UPROPERTY()
	FName NextDialogueID;
	
	// 버튼 이미지 추가
	UPROPERTY()
	UImage* ButtonImage; 
	
	UPROPERTY()
	UTextBlock* ButtonText;

public:

	UJMS_SelectButton();

	virtual void NativeConstruct();
	
	UFUNCTION(BlueprintCallable)
	void SetIndex(int32 InIndex) { Index = InIndex; }

	UFUNCTION(BlueprintCallable)
	int32 GetIndex() const { return Index; }

	UFUNCTION(BlueprintCallable)
	void SetNextNextDialogueID(FName NextID) { NextDialogueID = NextID; }

	UFUNCTION(BlueprintCallable)
	FName GetNextDialogueID() const { return NextDialogueID; }

	UFUNCTION()
	void OnSelectButtonClicked();

	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText Text);


};
