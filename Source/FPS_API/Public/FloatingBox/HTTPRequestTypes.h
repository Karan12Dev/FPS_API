#pragma once

#include "CoreMinimal.h"
#include "HTTPRequestTypes.generated.h"

USTRUCT(BlueprintType)
struct FBoxTransform
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<float> location;

	UPROPERTY(BlueprintReadWrite)
	TArray<float> rotation;

	UPROPERTY(BlueprintReadWrite)
	TArray<float> scale;

	void Dump() const;
};

USTRUCT(BlueprintType)
struct FBoxObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString type{};

	UPROPERTY(BlueprintReadWrite)
	FBoxTransform transform{};

	void Dump() const;
};

USTRUCT(BlueprintType)
struct FBoxType
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString name{};

	UPROPERTY(BlueprintReadWrite)
	TArray<float> color{}; 

	UPROPERTY(BlueprintReadWrite)
	int32 health{};

	UPROPERTY(BlueprintReadWrite)
	int32 score{};
	
	void Dump() const;
};

USTRUCT(BlueprintType)
struct FBoxData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FBoxType> types{};

	UPROPERTY(BlueprintReadWrite)
	TArray<FBoxObject> objects{};

	void Dump() const;
};