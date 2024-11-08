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
 * 자체 수명
 * 소한된것 보관해뒀다가 일괄 디스폰도 만들기
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ObjectPool")
	TArray<TSubclassOf<AJMS_ChildPoolManager>> PoolingActors;

public:

	/**
	 * 소환된 PoolManagers
	 */
	UPROPERTY(BlueprintReadOnly, Category="ObjectPool")
	TArray<AJMS_ChildPoolManager*> SpawnedChildPoolManagers;

	
public:
	void InitializePool();
	void CreatePoolChild(TSubclassOf<AJMS_ChildPoolManager> FactoryManager);

	/**
	 * 1개 오브젝트 소환하는 함수
	 * @return ObjectName에 맞는 함수 출력
	 */
	UFUNCTION(BlueprintCallable,Blueprintable,Category="ObjectPool")
	AJMS_ChildPawn* GetFactoryObject(E_ChildPoolName ObjectName,FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator,float Life = - 1.0f);

	UFUNCTION(BlueprintCallable,Blueprintable,Category="ObjectPool")
	TArray<AJMS_ChildPawn*> GetFactoryMultiObject(E_ChildPoolName ObjectName,FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator, int32 Count = 1 ,float Life = - 1.0f);
	
	/**
	 * 모든 오브젝트 비활성화
	 * @param FactoryManager 
	 */
	UFUNCTION(BlueprintCallable,Blueprintable,Category="ObjectPool")
	TArray<AJMS_ChildPawn*> DespawnPoolChild(E_ChildPoolName ObjectName);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
