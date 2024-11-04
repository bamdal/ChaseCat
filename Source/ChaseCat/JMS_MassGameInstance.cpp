// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_MassGameInstance.h"

#include "ObjectPool/JMS_PoolFactory.h"

AJMS_PoolFactory* UJMS_MassGameInstance::GetFactory()
{
	if(AJMS_PoolFactory* PoolFactory = CastChecked<AJMS_PoolFactory>(GEngine->GameSingleton))
		return PoolFactory;

#if WITH_EDITOR
	UE_LOG(LogTemp, Error, TEXT("Invalid PoolFactory"));
#endif
	
	return NewObject<AJMS_PoolFactory>();;
}


void UJMS_MassGameInstance::Init()
{
	Super::Init();


}


