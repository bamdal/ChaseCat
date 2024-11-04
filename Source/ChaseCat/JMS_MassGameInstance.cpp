// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_MassGameInstance.h"

#include "ObjectPool/JMS_PoolFactory.h"




void UJMS_MassGameInstance::Init()
{
	Super::Init();
	
	if(FactoryInit)
	{
		PoolFactory = GetWorld()->SpawnActor<AJMS_PoolFactory>(PoolFactoryClass);
	}

}


