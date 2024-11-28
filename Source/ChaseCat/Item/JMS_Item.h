// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JMS_Item.generated.h"

class UJMS_ItemComponent;

UCLASS()
class CHASECAT_API AJMS_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJMS_Item();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAudioComponent* TalikingSound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UJMS_ItemComponent* ItemComponent;

	// 잡기 Grab ---------------------------------------------------------------------
	UFUNCTION(BlueprintNativeEvent)
	bool StartGrab();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bPossibleGrab = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsGrab = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName StartDialogueName = "";
	
	UFUNCTION(BlueprintCallable)
	void EndGrab();

	// 던지기 Throw ---------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void ThrowItem();

	UFUNCTION(BlueprintImplementableEvent)
	void ThrowItem_Implementation();

	// 아이템 떨어뜨리기
	UFUNCTION(BlueprintCallable)
	void PlayerDefenceDropItem();

	// ---------------------------------------------------------------------

	
	// 디졸브 효과 실행
	UFUNCTION(BlueprintCallable)
	void Dissolve(float DissolveTime);

	// 설정된 보이스 시작
	UFUNCTION(BlueprintCallable)
	void PlayVoice(USoundWave* NewSound);

	// 재생중이던 보이스 정지
	UFUNCTION(BlueprintCallable)
	void StopVoice();


	// 대사에 트리거가 있을경우 실행
	UFUNCTION(BlueprintNativeEvent)
	void ItemEventTrigger(FName EventTrigger);

	UFUNCTION(BlueprintNativeEvent)
	void EndAmbassadorWindow();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
