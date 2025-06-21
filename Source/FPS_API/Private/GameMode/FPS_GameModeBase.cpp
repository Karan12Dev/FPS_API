// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FPS_GameModeBase.h"
#include "FloatingBox/FloatingBox.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"


void AFPS_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	FetchData();
}

void AFPS_GameModeBase::FetchData()
{
	TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest(); 
	Request->SetURL("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->OnProcessRequestComplete().BindUObject(this, &AFPS_GameModeBase::OnResponseReceived);
	Request->ProcessRequest();
}

void AFPS_GameModeBase::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful) return;
	
	FString JsonString = Response->GetContentAsString();
	UE_LOG(LogTemp, Warning, TEXT("Received JSON: %s"), *JsonString);

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &BoxData))
		{
			//BoxData.Dump();
			GetWorldTimerManager().SetTimer(BoxSpawnTimer, this, &AFPS_GameModeBase::BoxSpawnTimerFinished, BoxSpawnTime, true);
		}
	}
}

void AFPS_GameModeBase::BoxSpawnTimerFinished()
{
	if (UWorld* World = GetWorld(); IsValid(World))
	{
		FloatingBox = World->SpawnActor<AFloatingBox>(FloatingBoxClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (IsValid(FloatingBox) && BoxData.types.Num() > 0 && BoxData.objects.Num() > 0)
		{
			const int32 RandomBoxObject = FMath::RandRange(0, BoxData.objects.Num() - 1);
			int32 RandomBoxType = 0;
			for (int32 i = 0; i < BoxData.types.Num(); i++)
			{
				if (BoxData.objects[RandomBoxObject].type.Contains(BoxData.types[i].name))
				{
					RandomBoxType = i;
					break;
				}
			}
			FloatingBox->SetBoxData(BoxData.types[RandomBoxType], BoxData.objects[RandomBoxObject]);
		}
	}
}
