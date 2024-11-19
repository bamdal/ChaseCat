// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_ItemFocus.h"
#include "Async/Async.h"




void UJMS_ItemFocus::OnEnable()
{
	
	GetWorld()->GetTimerManager().SetTimer(TimerAlphaHandle,FTimerDelegate::CreateUObject(this,&UJMS_ItemFocus::TimerAlpha,true),GetWorld()->GetDeltaSeconds(),true);

}

void UJMS_ItemFocus::OnDisable()
{
	GetWorld()->GetTimerManager().SetTimer(TimerAlphaHandle,FTimerDelegate::CreateUObject(this,&UJMS_ItemFocus::TimerAlpha,false),GetWorld()->GetDeltaSeconds(),true);

}

void UJMS_ItemFocus::TimerAlpha(bool Up)
{
	int i = 1;
	if(!Up)
	{
		i = -1;
	}
	CurrentTime += GetWorld()->GetDeltaSeconds()*i;
	AlphaDuration = Sigmoid(CurrentTime,AlphaWeight,0.5f);
	
	//GEngine->AddOnScreenDebugMessage(-1,0.2f,FColor::Blue,FString::Printf(TEXT("AlphaDuration: %f"),AlphaDuration));
	if(AlphaDuration > 0.95 || AlphaDuration < 0.05)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerAlphaHandle);
		GEngine->AddOnScreenDebugMessage(-1,0.2f,FColor::Red,FString::Printf(TEXT("Stop")));

	}

}

float UJMS_ItemFocus::Sigmoid(float Time, float K, float T0, float YMin, float YMax)
{
	return YMin + (YMax - YMin) / (1 + FMath::Exp(-K * (Time - T0)));
}

void UJMS_ItemFocus::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

