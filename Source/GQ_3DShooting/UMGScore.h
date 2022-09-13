// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMGScore.generated.h"

/**
 * 
 */
UCLASS()
class GQ_3DSHOOTING_API UUMGScore : public UUserWidget
{
	GENERATED_BODY()
private:	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Job")
	void UpdateScore(int nScore);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Job")
	int Score = 0;
};
