#include "GeoJsonParser.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool FGeoJsonParser::ParseGeoJson(const FString& RelativePath, TArray<FCoordPair>& OutCoords)
{
	FString FilePath = FPaths::ProjectContentDir() + RelativePath;
	FString JsonStr;

	if (!FFileHelper::LoadFileToString(JsonStr, *FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("GeoJSON 파일 읽기 실패: %s"), *FilePath);
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonStr);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("GeoJSON 파싱 실패"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* Features;
	if (!JsonObject->TryGetArrayField(TEXT("features"), Features))
	{
		UE_LOG(LogTemp, Error, TEXT("features 배열을 찾을 수 없음"));
		return false;
	}

	int Index = 0;
	for (const auto& FeatureValue : *Features)
	{
		if (Index++ >= 5) break;

		const TSharedPtr<FJsonObject> FeatureObj = FeatureValue->AsObject();
		if (!FeatureObj.IsValid()) continue;

		const TSharedPtr<FJsonObject> Geometry = FeatureObj->GetObjectField("geometry");
		const TArray<TSharedPtr<FJsonValue>>* Coords;

		if (Geometry->TryGetArrayField("coordinates", Coords) && Coords->Num() >= 2)
		{
			double Lon = (*Coords)[0]->AsNumber();
			double Lat = (*Coords)[1]->AsNumber();

			OutCoords.Add({ Lat, Lon });

			UE_LOG(LogTemp, Log, TEXT("[%d] 위도: %f, 경도: %f"), Index, Lat, Lon);
		}
	}

	return true;
}
