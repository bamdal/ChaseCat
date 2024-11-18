// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_ItemFocus.h"
#include "Async/Async.h"


UJMS_ItemFocus::UJMS_ItemFocus(): TimerAlphaHandle()
{
}

void UJMS_ItemFocus::OnEnable()
{
	GetWorld()->GetTimerManager().SetTimer(TimerAlphaHandle,FTimerDelegate::CreateUObject(this,&UJMS_ItemFocus::TimerAlpha,true),GetWorld()->GetDeltaSeconds(),true);

}

void UJMS_ItemFocus::OnDisable()
{
	AlphaDuration = 0.0f;
}

void UJMS_ItemFocus::TimerAlpha(bool Up)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerAlphaHandle);
}
