// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS_EnumPool.h"
#include "GameFramework/Pawn.h"
#include "DetourCrowdAIController.h"
#include "JMS_ChildPawn.generated.h"

enum class E_ChildPoolName : uint8;

UCLASS()
class CHASECAT_API AJMS_ChildPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJMS_ChildPawn();

	UPROPERTY(EditAnywhere,Category = "Debug")
	bool IsFactory = true;
	
	/**
	 * Manager가 부여해준 Enum이름 값
	 */
	UPROPERTY()
	E_ChildPoolName PoolName;

	
	void ObjectEnabled(FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	AJMS_ChildPawn* ObjectDisabled();

	/**
	 * 현재 사용중인지 아닌지 판단
	 * @return true 사용, false 미사용
	 */
	UFUNCTION(BlueprintPure)
	bool IsEnabled();

	/**
	 * 스폰시 AI 재시작
	 */
	UFUNCTION(BlueprintImplementableEvent,Category = "Spawn")
	void SpawnCat(bool Spawn);


	void SetPoolIndex(int32 index);
	
	UFUNCTION(BlueprintPure)
	int32 GetPoolIndex();

	
	void SetChildPoolManager(class AJMS_ChildPoolManager* ChildPoolManager);

	UFUNCTION(BlueprintPure)
	AJMS_ChildPoolManager* GetChildPoolManager();


	void SetChildLife(float Life);

	UFUNCTION(BlueprintCallable)	
	void IsVisible(bool visible = true);
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

	UFUNCTION(BlueprintCallable, Category = "NavLinkProxy")
	FVector GetLeftVelocityAtTime(const FVector& InitialVelocity,float GRAVITY, float DeltaTime);
	
	UFUNCTION(BlueprintCallable, Category = "NavLinkProxy")
	FVector GetRightVelocityAtTime(const FVector& InitialVelocity,float GRAVITY, float DeltaTime);

};
