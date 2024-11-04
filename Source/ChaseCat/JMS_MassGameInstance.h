// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JMS_MassGameInstance.generated.h"

class AJMS_PoolFactory;
/**
 * 
 */
UCLASS()
class CHASECAT_API UJMS_MassGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AJMS_PoolFactory> PoolClass;

	UFUNCTION(BlueprintPure, Category="Singletone")
	AJMS_PoolFactory* GetFactory();


	virtual void Init() override;
};
