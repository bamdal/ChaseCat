// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JMS_PoolFactory.generated.h"

enum class E_ChildPoolName : uint8;
class AJMS_ChildPawn;
class AJMS_ChildPoolManager;
class UJMS_PoolingActorComponent;

/*
 * 여러개 스폰 안함
 * 비활성화시 팩토리로 돌아오기
 * 자체 수명
 * bool로 조건보고 GameInstance에서 Factory있으면 넘기고 없으면 소환
 * GameInstance에서 Factory접근
 * GameInstance에 연결해서 소환 
 */

UCLASS()
class CHASECAT_API AJMS_PoolFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJMS_PoolFactory();


	/**
	 * 소환할 PoolManagers
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ObjectPool")
	TArray<TSubclassOf<AJMS_ChildPoolManager>> PoolingActors;

	/**
	 * 소환된 PoolManagers
	 */
	UPROPERTY()
	TArray<AJMS_ChildPoolManager*> SpawnedChildPoolManagers;

	
public:
	void InitializePool();
	void CreatePoolChild();

	/**
	 * 1개 오브젝트 소환하는 함수
	 * @return ObjectName에 맞는 함수 출력
	 */
	AJMS_ChildPawn* GetObject(E_ChildPoolName ObjectName,FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	
};
