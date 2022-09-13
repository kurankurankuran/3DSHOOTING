// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "Engine/Engine.h"


void UCustomGameInstance::SetScore(int _Score)
{
    Score = FMath::Max(_Score, 0);
}

int UCustomGameInstance::GetScore()
{
    return FMath::Max(Score, 0);
}

void UCustomGameInstance::SetHighScore(int _Score)
{
    HighScore = FMath::Max(_Score, 0);
}

int UCustomGameInstance::GetHighScore()
{
    return FMath::Max(HighScore, 0);
}


UCustomGameInstance* UCustomGameInstance::GetInstance()
{
    UCustomGameInstance* instance = nullptr;

    if (GEngine)
    {
        FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
        instance = Cast<UCustomGameInstance>(context->OwningGameInstance);
    }

    return instance;
}


void UCustomGameInstance::DisplayDebugMessage(FString message)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, message);
    }
}

