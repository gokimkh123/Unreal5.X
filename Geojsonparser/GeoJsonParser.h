#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"

class FGeoJsonParser
{
public:
	// 위도, 경도 쌍을 담는 구조체
	struct FCoordPair
	{
		double Latitude;
		double Longitude;
	};

	// JSON 파싱 함수
	static bool ParseGeoJson(const FString& RelativePath, TArray<FCoordPair>& OutCoords);
};
