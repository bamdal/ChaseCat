// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_MassGameInstance.h"

#include "EngineUtils.h"
#include "Spawner/JMS_Spawner.h"
#include "ObjectPool/JMS_PoolFactory.h"




void UJMS_MassGameInstance::Init()
{
	Super::Init();
	
	if(FactoryInit)
	{
		PoolFactory = GetWorld()->SpawnActor<AJMS_PoolFactory>(PoolFactoryClass);
	}

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,&UJMS_MassGameInstance::ReloadLevel);

}

void UJMS_MassGameInstance::ReloadLevel(class UWorld* World)
{

	if(FactoryInit)
	{
		PoolFactory = GetWorld()->SpawnActor<AJMS_PoolFactory>(PoolFactoryClass);
	}
}




