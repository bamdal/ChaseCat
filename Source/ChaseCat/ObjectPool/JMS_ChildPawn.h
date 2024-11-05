// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS_EnumPool.h"
#include "GameFramework/Pawn.h"
#include "JMS_ChildPawn.generated.h"

enum class E_ChildPoolName : uint8;

UCLASS()
class CHASECAT_API AJMS_ChildPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJMS_ChildPawn();


	
	/**
	 * Manager가 부여해준 Enum이름 값
	 */
	UPROPERTY()
	E_ChildPoolName PoolName;

	
	void ObjectEnabled(FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	void ObjectDisabled();

	/**
	 * 현재 사용중인지 아닌지 판단
	 * @return true 사용, false 미사용
	 */
	UFUNCTION()
	bool IsEnabled();




	void SetPoolIndex(int32 index);
	
	UFUNCTION(BlueprintPure)
	int32 GetPoolIndex();

	
	void SetChildPoolManager(class AJMS_ChildPoolManager* ChildPoolManager);

	UFUNCTION(BlueprintPure)
	AJMS_ChildPoolManager* GetChildPoolManager();


	void SetChildLife(float Life);

	UFUNCTION(BlueprintCallable)	
	void IsVisible(bool visible);
private:
	UPROPERTY(Blueprintable)
	bool bIsEnabled = false;

	float ChildLife = -1;
	

	AJMS_ChildPoolManager* ChildManager;

	bool bHasLife = false;
	
	/**
	 * 고유 인덱스값(-1이면 에러)
	 */
	int32 PoolIndex = -1;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
