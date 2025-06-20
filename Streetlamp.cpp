// Fill out your copyright notice in the Description page of Project Settings.


#include "Streetlamp.h"
#include "Geojsonparser/GeoJsonParser.h"
#include "CesiumGlobeAnchorComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

/*
	액터가 생성될때 한 번 호출된다.
	PrimaryActorTick.bCanEverTick = true;는 Tick() 함수가 매 프레임 호출되도록 허용합니다.
	만약 이걸 false로 하면, Tick()은 무시됩니다 (성능 최적화 가능).
 */
AStreetlamp::AStreetlamp()
{
	PrimaryActorTick.bCanEverTick = true;
}

/*
	이 함수는 게임이 시작되거나 액터가 스폰되었을 때 딱 한 번 호출됩니다.
	여기에 초기화 작업을 넣습니다.
 */
void AStreetlamp::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Log, TEXT("Streetlamp가 시작됨"));


	// GeoJson 위경도 값 가져오기
	TArray<FGeoJsonParser::FCoordPair> Coords;
	if (!FGeoJsonParser::ParseGeoJson(TEXT(""), Coords)){
		UE_LOG(LogTemp, Error, TEXT("GeoJSON 파싱 실패"));
		return;
	}

	// StaticMesh 로딩 (.glb가 이미 콘텐츠로 임포트되었어야 함)
	UStaticMesh* StreetlampMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Models/street_lamp.street_lamp"));
	if (!StreetlampMesh){
		UE_LOG(LogTemp, Error, TEXT("StaticMesh 로드 실패"));
		return;
	}
	
	for (int i = 0; i < Coords.Num(); ++i){
		const auto& Coord = Coords[i];

		// StaticMeshActor 생성
		AStaticMeshActor* NewLamp = GetWorld()->SpawnActor<AStaticMeshActor>();
		if (!NewLamp){
			UE_LOG(LogTemp, Error, TEXT("StaticMeshActor 생성 실패."));
			continue;
		}
		NewLamp->GetStaticMeshComponent()->SetStaticMesh(StreetlampMesh);
		NewLamp->SetActorLabel(FString::Printf(TEXT("Lamp_%d"), i));
		NewLamp->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
		
		UCesiumGlobeAnchorComponent* Anchor = NewLamp->FindComponentByClass<UCesiumGlobeAnchorComponent>();
		if (!Anchor){
			Anchor = NewObject<UCesiumGlobeAnchorComponent>(NewLamp);
			if (Anchor){
				// 액터에 컴포넌트 추가
				NewLamp->AddInstanceComponent(Anchor);

				Anchor->RegisterComponent();
			}
			else{
				UE_LOG(LogTemp, Warning, TEXT("CesiumGlobeAnchorComponent 생성 실패."));
				continue;
			}
		}
		
		if (Anchor){
			FVector LonLatHeight(Coord.Longitude, Coord.Latitude, 48.0f);
			Anchor->MoveToLongitudeLatitudeHeight(LonLatHeight);
		}
		else UE_LOG(LogTemp, Warning, TEXT("CesiumGlobeAnchorComponent를 생성하거나 찾을 수 없습니다."));
	}
	UE_LOG(LogTemp, Log, TEXT("Streetlamp 생성 완료."));
}
/*
	매 프레임마다 호출됩니다.
	DeltaTime은 이번 프레임의 시간 간격 (초 단위)입니다.
	예: 빛 깜빡임, 위치 보간, 타이머 처리 등에 사용됩니다.
 */
void AStreetlamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

