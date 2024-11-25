// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JMS_AmbassadorWindow.generated.h"

class UMultiLineEditableText;
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

	// 대화 출력 창
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMultiLineEditableText* DialogueTextBox;
	
	UPROPERTY(VisibleAnywhere,BLUEprintReadWrite)
	FText logText;

	UPROPERTY()
	int32 CurrentTextIndex = 0;
	
	
	// 호출시 해당 텍스트를 한글자 한글자 말하듯이 출력되게 함
	UFUNCTION(BlueprintCallable)
	void StartDialogueTyping(float TypingSpeed = 10);

	// 반복 작업함수
	UFUNCTION()
	void UpdateDialogueText();

	// 타이머
	FTimerHandle TypingTimerHandle;
	
	UFUNCTION(BlueprintCallable)
	void SetDialogueTyping();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsTalking;
};
