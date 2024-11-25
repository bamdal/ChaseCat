// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_AmbassadorWindow.h"

#include "ChaseCat/ChaseCatCharacter.h"

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

void UJMS_AmbassadorWindow::EndDialogueText_Implementation()
{
	SetVisibility(ESlateVisibility::Hidden);
	// IMC되돌리기
	AChaseCatCharacter* Chaaar = Cast<AChaseCatCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(Chaaar)
	{
		Chaaar->SetIMCEndDialogueText();
	}

}

void UJMS_AmbassadorWindow::NextDialogueText_Implementation()
{
	if(NextTextName == TEXT(""))
	{
		EndDialogueText_Implementation();

	}

}

void UJMS_AmbassadorWindow::StartDialogueText_Implementation(FName Name)
{
	SetVisibility(ESlateVisibility::Visible);
}

