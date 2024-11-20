// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_UI_DestinationUI.h"

#include "JMS_UI_DestinationComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


FVector2D UJMS_UI_DestinationUI::GetDestinationUILocation(UJMS_UI_DestinationComponent* DestinationComponent)
{
	// 화면 크기 구하기
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
	if(DestinationComponent == nullptr)
	{
		return FVector2D(0,0);
	}

	// UI 스케일 가져오기
	float UIScale = UWidgetLayoutLibrary::GetViewportScale(this);
	ViewportSize /= UIScale;

	// 화면 중심과 타원의 반지름 정의
	float ScreenCenterX = ViewportSize.X / 2.0f;
	float ScreenCenterY = ViewportSize.Y / 2.0f;
	float EllipseRadiusX = ScreenCenterX * 0.8f; // 가로 반지름 (화면 크기의 80%)
	float EllipseRadiusY = ScreenCenterY * 0.8f; // 세로 반지름 (화면 크기의 80%)


	// 목적지 향하는 벡터
	FVector CameraLocation;
	FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(CameraLocation, CameraRotation);
	FVector TargetLocation = DestinationComponent->GetOwner()->GetActorLocation();
	FVector Direction = TargetLocation - CameraLocation;
	Direction.Normalize();

	// 화면에 찍힌 목적지 좌표 
	FVector2D ScreenPosition;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		
		if(!PlayerController->ProjectWorldLocationToScreen(TargetLocation, ScreenPosition))
		{

			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation,TargetLocation);
			float DeltaYaw = UKismetMathLibrary::NormalizeAxis(LookRotation.Yaw - CameraRotation.Yaw);
			GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Black,FString::Printf(TEXT("%f"),DeltaYaw));

			if(LookRotation.Pitch > 0)
			{
				// 맨 위
				ScreenPosition.Y = ScreenCenterY;
			}
			else
			{
				// 맨 아래
				ScreenPosition.Y = ScreenCenterY;
			}

			if(DeltaYaw > 0)
			{
				// 오른쪽  ScreenCenterX <-> ViewportSize.X  180 <-> 90
				
				ScreenPosition.X = UKismetMathLibrary::Lerp(ScreenCenterX,ViewportSize.X,(180 - DeltaYaw) / 90);
			}
			else
			{
				// 왼쪽 0 <-> ScreenCenterX  -90 <-> -180
				
				ScreenPosition.X = UKismetMathLibrary::Lerp(0,ScreenCenterX,(-DeltaYaw - 90) / 90);
			}
		}
	}
	

	// 화면 좌표를 UI 스케일에 맞게 보정
	ScreenPosition /= UIScale;

	


	
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

