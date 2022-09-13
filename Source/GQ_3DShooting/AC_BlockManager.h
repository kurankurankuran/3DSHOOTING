// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AC_BlockManager.generated.h"

class AACTargetActor;
UCLASS()
class GQ_3DSHOOTING_API AAC_BlockManager : public AActor
{
	GENERATED_BODY()

	//USTRUCT(BlueprintType)
	struct FBlockInfo
	{
		//GENERATED_BODY()

		AACTargetActor* pActor;
		TArray<FVector> vPosArray;

		FBlockInfo()
		{
			pActor = nullptr;
			vPosArray.Init(FVector(3100, 100, 5000), 3);
		}
	};

	// 過去現在未来のブロック座標保存用
	int32	nNum = 0;
	// 全ブロック管理配列
	TArray<FBlockInfo> vBlockArray;
	// 時間カウント
	unsigned long ulTimeCount;
	// ターゲットブロック管理用配列
	TArray<AACTargetActor*> vTargetArray;
	// ブロックデフォルトのマテリアル保存用
	class UMaterialInterface* SaveMID = nullptr;

public:
	// 配置ブロック一辺数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int MaxBlock = 25;
	// ブロック中心間距離
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Interval = 200;
	// 波の速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float c = 4.0f;
	// 時間の刻み
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float dt = 1.0f;
	// グリッド幅
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float h = 400.0f;
	// 波の上下移動速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float X = -100.0f;
	// ターゲットブロック数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int MaxTarget = 50;
	// ターゲットマテリアル
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		UMaterialInterface* TargetMID;
public:
	// Sets default values for this actor's properties
	AAC_BlockManager();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// ブロックからターゲットを選択し設定
	void SetTarget();
};
