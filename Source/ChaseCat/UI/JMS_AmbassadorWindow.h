// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JMS_AmbassadorWindow.generated.h"


class UJMS_SelectButton;
class UButton;
struct FJMS_DialogueData;
class URichTextBlock;
class UVerticalBox;
class UVerticalBoxSlot;

/**
 * 
 */
UCLASS()
class CHASECAT_API UJMS_AmbassadorWindow : public UUserWidget
{
	GENERATED_BODY()

public:

	// 데이터 테이블
	UPROPERTY()
	UDataTable* JMSDialogueDataTable;
	
	
	// 선택지가 생길 vertical박스
	UPROPERTY(EditAnywhere)
	UVerticalBox* VerticalBox;

	UPROPERTY(EditAnywhere)
	URichTextBlock* TalkingNameRichTextBlock;

	UPROPERTY()
	TArray<UJMS_SelectButton*> ChoiceButtons;
	
	// 선택지 생성 함수
	UFUNCTION(BlueprintCallable)
	void UpdateSelectBox(TArray<FText> Choices,TArray<FName> NextDialogueIDs);

	// 선택지 창에서의 버튼 클릭
	UFUNCTION()
	void OnSelectButtonClicked();

	UFUNCTION(BlueprintCallable)
	void ToggleTextView();

	UFUNCTION(BlueprintCallable)
	void WriteDialogueText(FName RowName);
	

	// 텍스트 창 처음시작 함수
	UFUNCTION(BlueprintCallable)
	void StartDialogueText(FName Name);

	// 텍스트 창 자동완성 , 다음 텍스트 넘기기
	UFUNCTION(BlueprintCallable)
	void NextDialogueText();

	// 텍스트창 종료
	UFUNCTION(BlueprintCallable)
	void EndDialogueText();

	// 다음 텍스트 rowname저장
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName NextTextName = TEXT("");

	// 대화 출력 창 UI
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	URichTextBlock* DialogueTextBox;

	// 대화 저장 장소
	UPROPERTY(VisibleAnywhere,BLUEprintReadWrite)
	FText logText;

	// 점진적 텍스트 진행용 인덱스
	UPROPERTY()
	int32 CurrentTextIndex = 0;

	// 점진적 텍스트 속도
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TypingSpeed = 10;
	
	// 호출시 해당 텍스트를 한글자 한글자 말하듯이 출력되게 함
	UFUNCTION(BlueprintCallable)
	void StartDialogueTyping();

	// 반복 작업함수
	UFUNCTION()
	void UpdateDialogueText();

	// 타이머
	FTimerHandle TypingTimerHandle;

	// 타이밍중이던 대화 완성시키기
	UFUNCTION(BlueprintCallable)
	void SetDialogueTyping();

	// true 면 말하고 있는중 false면 말이 끝남
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsTalking;

	// true 면 다음 텍스트로 넘기기 가능 false면 불가능
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsDialoguing = true;

	virtual void NativeOnInitialized() override;
};
