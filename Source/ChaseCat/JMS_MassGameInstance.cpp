// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_MassGameInstance.h"

#include "ChaseCatCharacter.h"
#include "EngineUtils.h"
#include "PropertyAccess.h"
#include "VisualizeTexture.h"
#include "Spawner/JMS_Spawner.h"
#include "ObjectPool/JMS_PoolFactory.h"
#include "UI/JMS_AmbassadorWindow.h"
#include "UI/JMS_UI_DestinationComponent.h"


void UJMS_MassGameInstance::Init()
{
	Super::Init();
	
	if(FactoryInit)
	{
		PoolFactory = GetWorld()->SpawnActor<AJMS_PoolFactory>(PoolFactoryClass);
	}

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,&UJMS_MassGameInstance::ReloadLevel);
	AddActiveDestinationDelegate.BindUObject(this,&UJMS_MassGameInstance::AddDestinationComponent);
	NextTextDialogue.BindUObject(this,&UJMS_MassGameInstance::NextTextDialogueFunc);

}

void UJMS_MassGameInstance::ReloadLevel(class UWorld* World)
{

	if(FactoryInit)
	{
		PoolFactory = GetWorld()->SpawnActor<AJMS_PoolFactory>(PoolFactoryClass);
	}
}

void UJMS_MassGameInstance::BeginDestroy()
{
	Super::BeginDestroy();

	AddActiveDestinationDelegate.Unbind();
	NextTextDialogue.Unbind();
}


bool UJMS_MassGameInstance::NextDestinationIndex()
{
	// ActiveDestinationsMap이 비어 있는 경우 바로 false 반환
	if (ActiveDestinationsMap.Num() == 0)
	{
		return false;
	}
	
	// Map의 키값을 정렬하여 배열로 저장
	TArray<int32> SortedKeys;
	ActiveDestinationsMap.GetKeys(SortedKeys);


	
	// 현재 인덱스 위치를 찾음
	int32 CurrentKeyIndex = SortedKeys.IndexOfByKey(PlayerSearchIndex);
	GEngine->AddOnScreenDebugMessage(-1,3.0,FColor::Cyan,FString::Printf(TEXT("CurrentKeyIndex:%d"),CurrentKeyIndex));

	// 현재 키가 유효하지 않거나 마지막 키일 경우
	if (CurrentKeyIndex == INDEX_NONE || CurrentKeyIndex >= SortedKeys.Num() - 1)
	{
		return false; // 더 이상 유효한 다음 인덱스가 없음
	}
	

	// 다음 유효한 키로 이동
	PlayerSearchIndex = SortedKeys[CurrentKeyIndex + 1];
	return true;
	
}

void UJMS_MassGameInstance::AddDestinationComponent(UJMS_UI_DestinationComponent* DestComp)
{

	if(DestComp->Index > -1)
	{
		if(!ActiveDestinationsMap.Contains(DestComp->Index))
			ActiveDestinationsMap.Add(DestComp->Index,DestComp);
		else
		{
			ActiveDestinations.Add(DestComp);
		}
	}
	else
	{
		ActiveDestinations.Add(DestComp);
		
	}
	
}

void UJMS_MassGameInstance::NextTextDialogueFunc()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,FString::Printf(TEXT("NextTalk triggered")));
	JMS_AmbassadorWindow->NextDialogueText();

}

void UJMS_MassGameInstance::RemoveAllDestinationComponent()
{
	ActiveDestinations.Empty();
	ActiveDestinationsMap.Empty();
}

void UJMS_MassGameInstance::SortActiveDestinations()
{
	if (ActiveDestinations.Num() == 0)
	{
		auto It = ActiveDestinationsMap.CreateConstIterator();
		if(It)
		{
			PlayerSearchIndex = It->Key;
		}
		
		
		return; // 정렬할 대상이 없을 때
	}

	// Map의 키값들을 가져와 정렬
	TArray<int32> SortedKeys;
	ActiveDestinationsMap.GetKeys(SortedKeys);
	SortedKeys.Sort(); // 오름차순 정렬
	if(SortedKeys.Num()>0)
	{
		PlayerSearchIndex = SortedKeys[0];
		// Map의 마지막 Key값 가져오기
		int32 CurrentIndex = SortedKeys.Num() > 0 ? SortedKeys.Last() : 0;

		// ActiveDestinations의 요소를 순회하며 Map에 추가
		for (UJMS_UI_DestinationComponent* Destination : ActiveDestinations)
		{
			if (!Destination)
			{
				continue; // 유효하지 않은 항목은 스킵
			}

			// 기존 인덱스 값이 유효하지 않거나, Map에 포함되지 않은 경우
			if (Destination->Index < 0 || !ActiveDestinationsMap.Contains(Destination->Index))
			{
				Destination->Index = ++CurrentIndex; // 새로운 Index 할당
				ActiveDestinationsMap.Add(Destination->Index, Destination); // Map에 추가
			}
			else
			{
				// Map에 이미 포함된 경우, 인덱스를 그대로 유지
				ActiveDestinationsMap[Destination->Index] = Destination;
			}
		}

	}

	// ActiveDestinations 배열도 Key값 기준으로 정렬
	ActiveDestinations.Sort([](const UJMS_UI_DestinationComponent& A, const UJMS_UI_DestinationComponent& B) {
		return A.Index < B.Index;
	});
}

