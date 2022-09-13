// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GQ_3DSHOOTING_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetScore, BlueprintGetter = GetScore ,Category = "Score")
		int Score = 0;
	UFUNCTION(BlueprintSetter)
		void SetScore(int nScore_);
	UFUNCTION(BlueprintGetter)
		int32 GetScore();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetHighScore, BlueprintGetter = GetHighScore, Category = "HighScore")
		int HighScore = 0;
	UFUNCTION(BlueprintSetter)
		void SetHighScore(int nScore_);
	UFUNCTION(BlueprintGetter)
		int32 GetHighScore();
public:
	static UCustomGameInstance* GetInstance();
	void DisplayDebugMessage(FString message);


};
