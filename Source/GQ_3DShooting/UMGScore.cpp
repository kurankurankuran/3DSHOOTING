// Fill out your copyright notice in the Description page of Project Settings.


#include "UMGScore.h"

// Tick����
void UUMGScore::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    // �p��������
    Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUMGScore::UpdateScore_Implementation(int nScore)
{
    Score = nScore;
}
