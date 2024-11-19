// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_UI_DestinationUI.h"

#include "JMS_UI_DestinationComponent.h"
#include "Kismet/GameplayStatics.h"


FVector2D UJMS_UI_DestinationUI::GetDestinationUILocation()
{
	// 화면 크기 구하기
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
	if(DestComp == nullptr)
	{
		return FVector2D(0,0);
	}

	// 목적지 향하는 벡터
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetOwner()->GetActorLocation();
	FVector TargetLocation = DestComp->GetOwner()->GetActorLocation();
	FVector Direction = TargetLocation - PlayerLocation;
	Direction.Normalize();

	// 화면에 찍힌 목적지 좌표 
	FVector2D ScreenPosition;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->ProjectWorldLocationToScreen(TargetLocation, ScreenPosition);
	}

	// 화면 중심과 타원의 반지름 정의
	float ScreenCenterX = ViewportSize.X / 2.0f;
	float ScreenCenterY = ViewportSize.Y / 2.0f;
	float EllipseRadiusX = ScreenCenterX * 0.8f; // 가로 반지름 (화면 크기의 80%)
	float EllipseRadiusY = ScreenCenterY * 0.8f; // 세로 반지름 (화면 크기의 80%)

	
	// 중심 좌표에서 상대 좌표 계산
	FVector2D CenteredPosition = ScreenPosition - FVector2D(ScreenCenterX, ScreenCenterY);

	// 타원의 방정식으로 거리 계산
	float DistanceFactor = FMath::Square(CenteredPosition.X / EllipseRadiusX) + FMath::Square(CenteredPosition.Y / EllipseRadiusY);
	if (DistanceFactor > 1.0f) // 타원 경계를 초과한 경우
	{
		// 타원의 경계로 위치를 클램프
		float ScaleFactor = FMath::Sqrt(DistanceFactor);
		CenteredPosition.X /= ScaleFactor;
		CenteredPosition.Y /= ScaleFactor;
	}
	
	// 화면 좌표로 변환
	FVector2D FinalPosition = CenteredPosition + FVector2D(ScreenCenterX, ScreenCenterY);

	return FinalPosition;
}

/**
 * 
 * @return 현재 추적 목표
 */
void UJMS_UI_DestinationUI::SetDestinationComponent(UJMS_UI_DestinationComponent* DestinationComponent)
{
	DestComp = DestinationComponent;
}

