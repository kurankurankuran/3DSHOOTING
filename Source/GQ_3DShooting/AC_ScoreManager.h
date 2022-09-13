// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AC_TargetHitEvent.h"
#include "EngineUtils.h" //TActorIterator
#include "GameFramework/Actor.h"
#include "AC_ScoreManager.generated.h"

class UCustomGameInstance;
class UUMGScore;
UCLASS()
class GQ_3DSHOOTING_API AAC_ScoreManager : public AActor
{
	GENERATED_BODY()
private:
	UCustomGameInstance* GameInstance = nullptr;
protected:
	UUMGScore* UMGScore;;
public:
	// スコア
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	//	int32 Score = 0;

	// 加算値
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 AddScoreNum = 10;
public:
	// Sets default values for this actor's properties
	AAC_ScoreManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(/*BlueprintNativeEvent,*/ BlueprintCallable, Category = "Job")
		void CheckHighScore();
	//Event Dispather(Multicast Delegate)
	UFUNCTION()
		void AddScore();

	
};
