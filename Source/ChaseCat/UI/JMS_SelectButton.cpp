// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_SelectButton.h"

#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"


UJMS_SelectButton::UJMS_SelectButton()
{
	// CreateDefaultSubobject로 UImage 생성
	OverlayWidget =  CreateDefaultSubobject<UVerticalBox>(TEXT("VerticalBoxWidget"));
	
	ButtonImage = CreateDefaultSubobject<UImage>(TEXT("ButtonImage"));

	ButtonText = CreateDefaultSubobject<UTextBlock>(TEXT("ButtonText"));
}

void UJMS_SelectButton::NativeConstruct()
{


	if (OverlayWidget)
	{
		// OverlayWidget을 버튼의 자식으로 추가
		UButtonSlot* ButtonSlot = Cast<UButtonSlot>(AddChild(OverlayWidget));
		if (ButtonSlot)
		{
			ButtonSlot->SetPadding(FMargin(0.0f));
			ButtonSlot->SetHorizontalAlignment(HAlign_Fill);
			ButtonSlot->SetVerticalAlignment(VAlign_Fill);
		}

		// UVerticalBox를 사용하여 이미지와 텍스트 배치
		UVerticalBox* VerticalBox = NewObject<UVerticalBox>(this);
		if (VerticalBox)
		{
			// VerticalBox를 OverlayWidget에 추가
			UVerticalBoxSlot* VerticalBoxSlot = OverlayWidget->AddChildToVerticalBox(VerticalBox);
			if (VerticalBoxSlot)
			{
				VerticalBoxSlot->SetHorizontalAlignment(HAlign_Fill);
				VerticalBoxSlot->SetVerticalAlignment(VAlign_Fill);
			}

			// 이미지 추가
			if (ButtonImage)
			{
				UVerticalBoxSlot* ImageSlot = VerticalBox->AddChildToVerticalBox(ButtonImage);
				if (ImageSlot)
				{
					ImageSlot->SetHorizontalAlignment(HAlign_Fill);
					ImageSlot->SetVerticalAlignment(VAlign_Fill);
				}
			}

			// 텍스트 추가
			if (ButtonText)
			{
				UVerticalBoxSlot* TextSlot = VerticalBox->AddChildToVerticalBox(ButtonText);
				if (TextSlot)
				{
					TextSlot->SetHorizontalAlignment(HAlign_Left); // 텍스트 왼쪽 정렬
					TextSlot->SetVerticalAlignment(VAlign_Center); // 텍스트 중앙 정렬
					TextSlot->SetPadding(FMargin(0.0f, 10.0f, 0.0f, 10.0f)); // 간격 추가
				}

				// 텍스트 색상 및 기본 속성 설정
				ButtonText->SetColorAndOpacity(FSlateColor(FColor::Black)); // 텍스트 색상
				ButtonText->SetText(FText::FromString(TEXT("Button"))); // 기본 텍스트
				ButtonText->SetAutoWrapText(true); // 텍스트 자동 줄바꿈
			}
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
 



