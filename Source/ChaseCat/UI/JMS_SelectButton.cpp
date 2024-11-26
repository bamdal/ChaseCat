// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_SelectButton.h"

#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"


UJMS_SelectButton::UJMS_SelectButton()
{
	// CreateDefaultSubobject로 UImage 생성
	OverlayWidget = CreateDefaultSubobject<UOverlay>(TEXT("OverlayWidget"));
	
	ButtonImage = CreateDefaultSubobject<UImage>(TEXT("ButtonImage"));

	ButtonText = CreateDefaultSubobject<UTextBlock>(TEXT("ButtonText"));
}

void UJMS_SelectButton::NativeConstruct()
{


	if (OverlayWidget)
	{
		// Overlay를 버튼의 자식으로 추가
		UButtonSlot* ButtonSlot = Cast<UButtonSlot>(AddChild(OverlayWidget));
		if (ButtonSlot)
		{
			ButtonSlot->SetPadding(FMargin(0.0f));
			ButtonSlot->SetHorizontalAlignment(HAlign_Fill);
			ButtonSlot->SetVerticalAlignment(VAlign_Fill);
		}

		// 이미지 추가
		if (ButtonImage)
		{
			UOverlaySlot* ImageSlot = OverlayWidget->AddChildToOverlay(ButtonImage);
			ImageSlot->SetHorizontalAlignment(HAlign_Fill);
			ImageSlot->SetVerticalAlignment(VAlign_Fill);
		}

		// 텍스트 추가
		if (ButtonText)
		{
			UOverlaySlot* TextSlot = OverlayWidget->AddChildToOverlay(ButtonText);
			if (TextSlot)
			{
				TextSlot->SetHorizontalAlignment(HAlign_Center); // 텍스트 중앙 정렬
				TextSlot->SetVerticalAlignment(VAlign_Center);
			}

			// 텍스트 색상 및 기본 속성 설정
			ButtonText->SetColorAndOpacity(FSlateColor(FColor::Black)); // 텍스트 흰색
			ButtonText->SetText(FText::FromString(TEXT("Button"))); // 기본 텍스트
		}
	}
}

void UJMS_SelectButton::OnSelectButtonClicked()
{
	
}

void UJMS_SelectButton::SetButtonText(FText Text)
{
	ButtonText->SetText(Text);
}
 



