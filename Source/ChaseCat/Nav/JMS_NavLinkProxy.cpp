// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_NavLinkProxy.h"

AJMS_NavLinkProxy::AJMS_NavLinkProxy()
{
	PrimaryActorTick.bCanEverTick = true;


	
}


void AJMS_NavLinkProxy::init(const FVector& Start, const FVector& End, float Time)
{

	// 초기 값 설정
	StartPoint = Start;  // A 지점
	EndPoint = End; // B 지점
	TotalTime = Time;  // 총 시간 1초
	
	// A에서 B로 가는 초기 속도 계산

	InitVelocity = CalculateParabolicVelocity(StartPoint, EndPoint, TotalTime);
	CurrentLocation = StartPoint;
	CurrentVelocity = InitVelocity;
}


FVector AJMS_NavLinkProxy::CalculateParabolicVelocity(const FVector& Start, const FVector& End, float Time)
{


	FVector Displacement = End - Start;

	// 수평 속도 (수평 방향은 일정한 속도 유지)
	FVector HorizontalVelocity = FVector(Displacement.X / Time, Displacement.Y / Time, 0);

	// 수직 속도 (중력만 고려)
	 //FMath::Abs(Start.Z - End.Z);
	float VerticalVelocity = (2 * Displacement.Z) / Time;

	return FVector(HorizontalVelocity.X, HorizontalVelocity.Y, VerticalVelocity);
}

FVector AJMS_NavLinkProxy::GetLeftVelocityAtTime(const FVector& InitialVelocity, float DeltaTime)
{
	// 시간에 따른 수직 속도 변화 (중력 고려)
	float VerticalVelocity = InitialVelocity.Z - GRAVITY * DeltaTime;

	// 수평 속도는 일정
	return FVector(InitialVelocity.X, InitialVelocity.Y, VerticalVelocity);
}

FVector AJMS_NavLinkProxy::GetRightVelocityAtTime(const FVector& InitialVelocity, float DeltaTime)
{
	FVector right = GetLeftVelocityAtTime(InitialVelocity,DeltaTime);

	return FVector(-right.X, -right.Y, right.Z);
}
	