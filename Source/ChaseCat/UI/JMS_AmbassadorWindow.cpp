// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_AmbassadorWindow.h"

#include "JMS_DialogueData.h"
#include "ChaseCat/ChaseCatCharacter.h"
#include "Components/Button.h"

#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "Components/VerticalBoxSlot.h"

void UJMS_AmbassadorWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	// DataTable 경로 설정
	const FSoftObjectPath DataTablePath(TEXT("/Game/BP/UI/TextData/DataTable_JMSDialogueData.DataTable_JMSDialogueData"));

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


	VerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("SelectBox")));
	if(VerticalBox == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString::Printf(TEXT("%s VerticalBox is null"),*this->GetClass()->GetName()));

	}

	TalkingNameRichTextBlock = Cast<URichTextBlock>(GetWidgetFromName(TEXT("TalkingName")));
	if(VerticalBox == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString::Printf(TEXT("%s TalkingNameRichTextBlock is null"),*this->GetClass()->GetName()));

	}

}


void UJMS_AmbassadorWindow::UpdateSelectBox(TArray<FText> Choices)
{
	if (VerticalBox == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Red, TEXT("VerticalBox is null! Cannot update SelectBox."));
		return;
	}

	// 기존 버튼 제거
	VerticalBox->ClearChildren();

	// 선택지 배열에 따라 버튼 생성
	for (int32 i = 0; i < Choices.Num(); ++i)
	{
		// 버튼 생성
		UButton* NewButton = NewObject<UButton>(this);
		UTextBlock* ButtonText = NewObject<UTextBlock>(this);
		// 선택지가 생겼으므로 넘기기 불가능
		bIsDialoguing = false;

		if (NewButton && ButtonText)
		{
			// 버튼 텍스트 설정
			ButtonText->SetText(Choices[i]);

			// 버튼에 텍스트 추가
			NewButton->AddChild(ButtonText);

			// 버튼 스타일 설정 (옵션)
			// NewButton->WidgetStyle = CustomStyle;

			// 클릭 이벤트 동적 바인딩
			NewButton->OnClicked.AddDynamic(this, &UJMS_AmbassadorWindow::OnSelectButtonClicked);
			ButtonIndexMap.Add(NewButton,i);
			// VerticalBox에 버튼 추가
			VerticalBox->AddChild(NewButton);

			// 버튼에 개인 인덱스 추가

			
		}
	}
}

void UJMS_AmbassadorWindow::OnSelectButtonClicked()
{

	// 클릭된 버튼을 매핑에서 찾기
	for (const TPair<UButton*, int32>& Pair : ButtonIndexMap)
	{
		if (Pair.Key->IsPressed()) // 현재 눌린 버튼인지 확인
		{
			//인덱스 통해구하기
			//NextTextName = Pair.Value;
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Orange, FString::Printf(TEXT("%s -> Button Click"),*this->GetName()));

	bIsDialoguing = true;

	// 버튼의 인덱스에 맞는 NextTextName으로 바꿔줘야함 
	WriteDialogueText(NextTextName);
}

void UJMS_AmbassadorWindow::ToggleTextView()
{
	if(GetVisibility() == ESlateVisibility::Visible)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
		
	}
}


void UJMS_AmbassadorWindow::WriteDialogueText(FName RowName)
{
	if(RowName!=NAME_None)
	{
		FJMS_DialogueData* Row = JMSDialogueDataTable->FindRow<FJMS_DialogueData>(RowName,TEXT("JMS_AmbassadorWindow"),true);
		TalkingNameRichTextBlock->SetText(Row->NPCName);
		logText = Row->DialogueText;
		StartDialogueTyping();
		UpdateSelectBox(Row->Choices);
		if(Row->NextDialogueIDs.Num() > 0)
		{
			NextTextName = Row->NextDialogueIDs[0];
		}
		
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Blue,FString::Printf(TEXT("%s 대화 종료"),*this->GetName()));

	}

}


void UJMS_AmbassadorWindow::StartDialogueTyping()
{
	DialogueTextBox->SetText(FText::GetEmpty());
	
	bIsTalking = true;
	// 타이핑 진행 상태 초기화
	CurrentTextIndex = 0;
	
	GetWorld()->GetTimerManager().SetTimer(
	TypingTimerHandle,
	this,
	&UJMS_AmbassadorWindow::UpdateDialogueText,
	1/TypingSpeed,
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



void UJMS_AmbassadorWindow::EndDialogueText_Implementation()
{
	
	// IMC되돌리기
	AChaseCatCharacter* Chaaar = Cast<AChaseCatCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Chaaar)
	{
		Chaaar->SetIMCEndDialogueText();
	}

}


void UJMS_AmbassadorWindow::NextDialogueText_Implementation()
{

	if(bIsTalking)
	{
		// 말하고 있는 중에 다음 버튼 눌렀으므로 대화창 끝까지 한번에 출력
		GetWorld()->GetTimerManager().ClearTimer(TypingTimerHandle);
		SetDialogueTyping();
	
	}
	else
	{
		if(NextTextName == TEXT(""))
		{
			EndDialogueText();

		}

	}

	// 완성되자마자 넘어가기 방지용 부울
	if(bIsTalking)
	{
		bIsTalking = false;
	}
	else
	{
		// 다음 텍스트로 넘어가기 가능할때
		if(bIsDialoguing)
		{
			WriteDialogueText(NextTextName);
		}
	}

		
	
	

}

void UJMS_AmbassadorWindow::StartDialogueText_Implementation(FName Name)
{
	ToggleTextView();

	
}

