// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JMS_MassGameInstance.generated.h"

class UJMS_UI_DestinationComponent;
class AJMS_Spawner;
class AJMS_PoolFactory;

DECLARE_DELEGATE_OneParam(FAddActiveDestination,UJMS_UI_DestinationComponent*);

/**
 * 
 */
UCLASS()
class CHASECAT_API UJMS_MassGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool FactoryInit = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsTest = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AJMS_PoolFactory> PoolFactoryClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AJMS_PoolFactory* PoolFactory;

	// 목표지점 설정을 위한 델리게이트
	FAddActiveDestination AddActiveDestinationDelegate;

	// 목표지점들을 담아놓는 배열
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<UJMS_UI_DestinationComponent*> ActiveDestinations;

	// 정렬까지 완전히 끝난후 배열 
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TMap<int32, UJMS_UI_DestinationComponent*> ActiveDestinationsMap;

	// 현재 탐색중인 Map의 인덱스 
	UPROPERTY(visibleAnywhere,BlueprintReadOnly)
	int32 PlayerSearchIndex = 0;

	// 다음 인덱스 번호로 옮기기 true면 존재함 false면 없음
	UFUNCTION(BlueprintCallable)
	bool NextDestinationIndex();

	// 델리게이트로 불릴 함수
	UFUNCTION()
	void AddDestinationComponent(UJMS_UI_DestinationComponent* DestComp);

	UFUNCTION(BlueprintCallable)
	void RemoveAllDestinationComponent();

	UFUNCTION(BlueprintCallable)
	void SortActiveDestinations();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float WorldGravity = 980.0f;

	virtual void Init() override;

	void ReloadLevel(class UWorld* World);

	virtual void BeginDestroy() override;
};
