// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "JMS_DialogueData.generated.h"


UENUM(BlueprintType)
enum class EDialogueState : uint8
{
	Start UMETA(DisplayName = "Start"),
	Middle UMETA(DisplayName = "Middle"),
	End UMETA(DisplayName = "End")
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FJMS_DialogueData : public FTableRowBase
{
	GENERATED_BODY()

	// NPC 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NPCName;

	// 대화 내용
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;

	// 대화 선택지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Choices;

	// 선택지에 따른 다음 대화 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> NextDialogueIDs;

	// 대화 이벤트 트리거
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName EventTrigger;

	// 대화 상태 (예: 시작, 진행, 종료 등)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDialogueState DialogueState;
	
};

