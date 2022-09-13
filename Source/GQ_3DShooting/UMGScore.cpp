// Fill out your copyright notice in the Description page of Project Settings.


#include "UMGScore.h"

// Tickˆ—
void UUMGScore::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    // Œp³Œ³ˆ—
    Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUMGScore::UpdateScore_Implementation(int nScore)
{
    Score = nScore;
}
