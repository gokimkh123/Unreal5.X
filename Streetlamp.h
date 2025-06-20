// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Streetlamp.generated.h"

UCLASS()
class LIGHTPOLLUTION_API AStreetlamp : public AActor
{
	GENERATED_BODY()
	
public:	
	AStreetlamp();

protected:
	/*
	가로등을 설치하거나 geojson 파일을 읽는 로직에 좋습니다
	게임이 시작되거나 월드에 스폰될 때 한 번 실행됩니다.
	 */
	virtual void BeginPlay() override;	

public:	
	/*
	매 프레임마다 실행된다. bCanEverTick = true여야지 작동된다.
	가로등의 불빛 깜빡임 같은 실시간 변화 처리에 사용된다.	
	 */
	virtual void Tick(float DeltaTime) override;	

};
