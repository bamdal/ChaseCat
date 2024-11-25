// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_AmbassadorWindow.h"

#include "ChaseCat/ChaseCatCharacter.h"
#include "Components/Button.h"

#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

#include "Components/VerticalBoxSlot.h"

void UJMS_AmbassadorWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	VerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("SelectBox")));
	if(VerticalBox == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString::Printf(TEXT("%s VerticalBox is null"),*this->GetClass()->GetName()));

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

			// VerticalBox에 버튼 추가
			VerticalBox->AddChild(NewButton);
		}
	}
}

void UJMS_AmbassadorWindow::OnSelectButtonClicked()
{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f,FColor::Orange, FString::Printf(TEXT("%s -> Button Click"),*this->GetName()));
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



void UJMS_AmbassadorWindow::StartDialogueTyping(float TypingSpeed)
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


}

void UJMS_AmbassadorWindow::StartDialogueText_Implementation(FName Name)
{
	ToggleTextView();
}

