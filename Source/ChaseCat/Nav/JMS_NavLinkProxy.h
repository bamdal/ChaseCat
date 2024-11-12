// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "JMS_NavLinkProxy.generated.h"


UENUM(BlueprintType)
enum class ENavLinkDirectionBP : uint8
{
	BothWays      UMETA(DisplayName = "BothWays"),
	LeftToRight   UMETA(DisplayName = "LeftToRight"),
	RightToLeft   UMETA(DisplayName = "RightToLeft")
};

/**
 * 
 */
UCLASS()
class CHASECAT_API AJMS_NavLinkProxy : public ANavLinkProxy
{
	GENERATED_BODY()
	
public:

	AJMS_NavLinkProxy();

	UFUNCTION(BlueprintCallable, Category = "NavLink")
	ENavLinkDirectionBP ConvertToBPDirection(ENavLinkDirection::Type Direction)
	{
		switch (Direction)
		{
		case ENavLinkDirection::BothWays:
			return ENavLinkDirectionBP::BothWays;
		case ENavLinkDirection::LeftToRight:
			return ENavLinkDirectionBP::LeftToRight;
		case ENavLinkDirection::RightToLeft:
			return ENavLinkDirectionBP::RightToLeft;
		default:
			return ENavLinkDirectionBP::BothWays; // 기본값 설정
		}
	}
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NavLinkProxy")
	FVector StartPoint;     // A 지점
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NavLinkProxy")
	FVector EndPoint;       // B 지점

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NavLinkProxy")
	FVector InitVelocity; // 왼쪽 -> 오른쪽 초기 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NavLinkProxy")
	float TotalTime;        // 총 시간

	
	
	UPROPERTY(BlueprintReadOnly, Category = "NavLinkProxy")
	FVector CurrentVelocity; // 현재 속도

	UPROPERTY(BlueprintReadOnly, Category = "NavLinkProxy")
	FVector CurrentLocation; // 현재 위치

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NavLinkProxy")
	float GRAVITY = 980.0f; // 중력 가속도

private:

	UFUNCTION(BlueprintCallable, Category = "NavLinkProxy")
	void init(const FVector& Start, const FVector& End, float Time);
	
	FVector CalculateParabolicVelocity(const FVector& Start, const FVector& End, float Time);

	UFUNCTION(BlueprintCallable, Category = "NavLinkProxy")
	FVector GetLeftVelocityAtTime(const FVector& InitialVelocity, float DeltaTime);
	
	UFUNCTION(BlueprintCallable, Category = "NavLinkProxy")
	FVector GetRightVelocityAtTime(const FVector& InitialVelocity, float DeltaTime);
	
};
