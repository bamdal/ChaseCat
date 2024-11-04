// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS_ChildPawn.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "JMS_ChildPoolManager.generated.h"

enum class E_ChildPoolName : uint8;
class AJMS_ChildPawn;

UCLASS()
class CHASECAT_API AJMS_ChildPoolManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJMS_ChildPoolManager();

	UPROPERTY(EditAnywhere,Blueprintable,Category="ObjectPool")
	int32 PoolSize = 16;

	UPROPERTY(EditAnywhere,Blueprintable,Category="ObjectPool")
	TSubclassOf<AJMS_ChildPawn> PoolObject;

	UPROPERTY(EditAnywhere,Blueprintable,Category = ObjectPool)
	E_ChildPoolName ManagerPoolName = E_ChildPoolName::None;

	/**
	 * poolchild 배열
	 */
	TQueue<AJMS_ChildPawn*> PoolChilds;

	UFUNCTION()
	void ComeBackChild();

	
	UFUNCTION()
	void InitializePawnChild();

	




	/**
	 * 인덱스 순서에 맞는 자식하나 주기
	 * @return 
	 */
	AJMS_ChildPawn* GetChild(FVector Location, FRotator Rotation);

private:
	void MakeDoublePool();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
