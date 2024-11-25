// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_AmbassadorWindow.h"

#include "ChaseCat/ChaseCatCharacter.h"
#include "Components/MultiLineEditableText.h"

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
	SetVisibility(ESlateVisibility::Visible);
}

