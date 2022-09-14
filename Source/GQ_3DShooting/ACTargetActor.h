// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACTargetActor.generated.h"

UCLASS()
class GQ_3DSHOOTING_API AACTargetActor : public AActor
{
	GENERATED_BODY()
public:
	bool TargetFlag = false;


// テスト用変数
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool TestFlag = false;
	// ヒット後のマテリアル
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UMaterialInterface* HitMID;
public:	
	// Sets default values for this actor's properties
	AACTargetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool HitEvent();

};
