// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_AmbassadorWindow.h"

#include "JMS_DialogueData.h"
#include "JMS_SelectButton.h"
#include "ChaseCat/ChaseCatCharacter.h"
#include "ChaseCat/Item/JMS_Item.h"
#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"

#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "Components/VerticalBoxSlot.h"

void UJMS_AmbassadorWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	// DataTable 경로 설정
	const FSoftObjectPath DataTablePath(
		TEXT("/Game/BP/UI/TextData/DataTable_JMSDialogueData.DataTable_JMSDialogueData"));

	// 데이터 테이블 비동기 가져오기
	TSoftObjectPtr<UDataTable> DataTableSoftObject(DataTablePath);
	if (DataTableSoftObject.IsValid())
	{
		JMSDialogueDataTable = DataTableSoftObject.Get();
	}
	else
	{
		JMSDialogueDataTable = DataTableSoftObject.LoadSynchronous();
	}

	if (JMSDialogueDataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Failed to load DataTable_JMSDialogueData"));
	}

	DialogueTextBox = Cast<URichTextBlock>(GetWidgetFromName(TEXT("DialogueText")));
	if (DialogueTextBox == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,
		                                 FString::Printf(
			                                 TEXT("%s DialogueTextBox is null"), *this->GetClass()->GetName()));
	}

	VerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("SelectBox")));
	if (VerticalBox == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,
		                                 FString::Printf(TEXT("%s VerticalBox is null"), *this->GetClass()->GetName()));
	}

	TalkingNameRichTextBlock = Cast<URichTextBlock>(GetWidgetFromName(TEXT("TalkingName")));
	if (TalkingNameRichTextBlock == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,
		                                 FString::Printf(
			                                 TEXT("%s TalkingNameRichTextBlock is null"),
			                                 *this->GetClass()->GetName()));
	}
}


void UJMS_AmbassadorWindow::UpdateSelectBox(TArray<FText> Choices, TArray<FName> NextDialogueIDs)
{
	if (VerticalBox == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
		                                 FString::Printf(
			                                 TEXT("%s VerticalBox is null! Cannot update SelectBox."),
			                                 *this->GetClass()->GetName()));
		return;
	}

	// 기존 버튼 제거
	VerticalBox->ClearChildren();

	// 선택지 배열에 따라 버튼 생성
	for (int32 i = 0; i < Choices.Num(); ++i)
	{
		// 버튼 생성
		//UJMS_SelectButton* NewButton = CreateWidget<UJMS_SelectButton>(this, TSubclassOf<UJMS_SelectButton> 로 받아와서 적용 가능);
		UJMS_SelectButton* NewButton = NewObject<UJMS_SelectButton>(this);
		UVerticalBoxSlot* ButtonSlot = VerticalBox->AddChildToVerticalBox(NewButton);
		ButtonSlot->SetPadding(FMargin(0, 5, 0, 5));
		NewButton->NativeConstruct();
		//UTextBlock* ButtonText = NewObject<UTextBlock>(this);
		// 선택지가 생겼으므로 넘기기 불가능
		bIsDialoguing = false;

		if (NewButton)
		{
			// 버튼 텍스트 설정
			NewButton->SetButtonText(Choices[i]);

			// 버튼 설정 


			// 클릭 이벤트 동적 바인딩
			NewButton->OnClicked.AddDynamic(this, &UJMS_AmbassadorWindow::OnSelectButtonClicked);
			NewButton->SetIndex(i);
			NewButton->SetNextNextDialogueID(NextDialogueIDs[i]);
			ChoiceButtons.Add(NewButton);
	
			
			// 버튼에 개인 인덱스 추가
		}
	}
}

void UJMS_AmbassadorWindow::OnSelectButtonClicked()
{
	// 클릭된 버튼을 매핑에서 찾기
	for (UJMS_SelectButton* Element : ChoiceButtons)
	{
		if (Element->IsHovered()) // 현재 눌린 버튼인지 확인
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange,
			                                 FString::Printf(TEXT("%s -> %s"), *this->GetName(), *Element->GetName()));
			NextTextName = Element->GetNextDialogueID();
		}
	}


	bIsDialoguing = true;

	// 버튼의 인덱스에 맞는 NextTextName으로 바꿔줘야함 
	WriteDialogueText(NextTextName);
}

void UJMS_AmbassadorWindow::ToggleTextView()
{
	if (GetVisibility() == ESlateVisibility::Visible)
	{
		SetVisibility(ESlateVisibility::Hidden);
		bIsDialoguing = true;
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
	}
}


void UJMS_AmbassadorWindow::WriteDialogueText(FName RowName)
{
	if (RowName != NAME_None)
	{
		FJMS_DialogueData* Row = JMSDialogueDataTable->FindRow<FJMS_DialogueData>(
			RowName,TEXT("JMS_AmbassadorWindow"), true);
		TalkingNameRichTextBlock->SetText(Row->NPCName);
		logText = Row->DialogueText;
		if (TalkingItem && Row->TextVoice != nullptr)
		{
			TalkingItem->PlayVoice(Row->TextVoice);
		}
		if(TalkingItem && Row->EventTrigger.Num() > 0)
		{
			for (FName Element : Row->EventTrigger)
			{
				TalkingItem->ItemEventTrigger(Element);
			}
			
		}
		StartDialogueTyping();
		UpdateSelectBox(Row->Choices, Row->NextDialogueIDs);
		if (Row->NextDialogueIDs.Num() > 0)
		{
			NextTextName = Row->NextDialogueIDs[0];
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s 대화 종료"), *this->GetName()));
	}
}


void UJMS_AmbassadorWindow::StartDialogueTyping()
{
	DialogueTextBox->SetText(FText::GetEmpty());

	bIsTalking = true;
	// 타이핑 진행 상태 초기화
	CurrentTextIndex = 0;

	if (TypingSpeed == 0)
	{
		TypingSpeed = 100;
	}

	GetWorld()->GetTimerManager().SetTimer(
		TypingTimerHandle,
		this,
		&UJMS_AmbassadorWindow::UpdateDialogueText,
		1 / TypingSpeed,
		true
	);
}

void UJMS_AmbassadorWindow::UpdateDialogueText()
{
	// logText의 내용을 한 글자씩 추가
	if (logText.IsEmpty() || CurrentTextIndex >= logText.ToString().Len())
	{
		// 타이머 정지 및 대화 종료 처리
		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
		bIsTalking = false;
		return;
	}

	// 점진적으로 텍스트를 출력
	FString FullText = logText.ToString();
	FString PartialText = FullText.Left(CurrentTextIndex + 1);
	DialogueTextBox->SetText(FText::FromString(PartialText));

	// 인덱스 증가
	++CurrentTextIndex;
}

void UJMS_AmbassadorWindow::SetDialogueTyping()
{
	DialogueTextBox->SetText(logText);
	bIsTalking = true;
}


void UJMS_AmbassadorWindow::StartDialogueText(FName Name, AJMS_Item* CalledItem)
{
	ToggleTextView();
	if(CalledItem)
	{
		TalkingItem = CalledItem;
	}
	WriteDialogueText(Name);
}


void UJMS_AmbassadorWindow::NextDialogueText()
{
	if (bIsTalking)
	{
		// 말하고 있는 중에 다음 버튼 눌렀으므로 대화창 끝까지 한번에 출력
		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
		SetDialogueTyping();
	}
	else
	{
		if (NextTextName == TEXT(""))
		{
			if(TalkingItem)
			{
				TalkingItem->StopVoice();
				
			}
			EndDialogueText();
		}
	}

	// 완성되자마자 넘어가기 방지용 부울
	if (bIsTalking)
	{
		bIsTalking = false;
	}
	else
	{
		// 다음 텍스트로 넘어가기 가능할때
		if (bIsDialoguing)
		{
			if(TalkingItem)
			{
				TalkingItem->StopVoice();
				
			}
			WriteDialogueText(NextTextName);
		}
	}
}

void UJMS_AmbassadorWindow::EndDialogueText()
{
	// IMC되돌리기
	AChaseCatCharacter* Chaaar = Cast<AChaseCatCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Chaaar)
	{
		Chaaar->SetIMCEndDialogueText();
	}
}
