// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_BlockManager.h"
#include "ACTargetActor.h"
#include "Kismet/KismetSystemLibrary.h"



// Sets default values
AAC_BlockManager::AAC_BlockManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAC_BlockManager::BeginPlay()
{
	Super::BeginPlay();

	//UKismetSystemLibrary::PrintString(this, "C++ Hello World!", true, true, FColor::Cyan, 2.f);

	vBlockArray.Init(FBlockInfo(), MaxBlock * MaxBlock);
	ulTimeCount = 0;

	// アクターのパス
	FString aAssetPath = "/Game/Actor/AC_Target.AC_Target_C";

	// アセットを読み込む（同期）
	TSubclassOf<AACTargetActor> aTargetClass = TSoftClassPtr<AACTargetActor>(FSoftObjectPath(*aAssetPath)).LoadSynchronous();

	// ブロックをスポーン＆配置
	// 読み込み確認
	if (aTargetClass != nullptr) {
		for (int i = 0; i < vBlockArray.Num(); ++i)
		{
			// スポーン
			TObjectPtr< AACTargetActor> aTarget = GetWorld()->SpawnActor<AACTargetActor>(aTargetClass);
			// 参照
			vBlockArray[i].pActor = aTarget;
			// 座標
			vBlockArray[i].vPosArray[nNum].X += (i % MaxBlock) * Interval;
			vBlockArray[i].vPosArray[nNum].Y += (i / MaxBlock) * Interval;
			vBlockArray[i].vPosArray[2] = vBlockArray[i].vPosArray[1] = vBlockArray[i].vPosArray[nNum];
			aTarget->SetActorLocation(vBlockArray[i].vPosArray[nNum]);
		}
		// マテリアル保存
		if (0 < vBlockArray.Num())
		{
			// 取得したコンポーネントを格納する配列
			TInlineComponentArray< UActorComponent* > aActorComponents(vBlockArray[0].pActor);
			// アクターが持つコンポーネントを複数取得
			vBlockArray[0].pActor->GetComponents< UActorComponent >(aActorComponents);
			// 取得したコンポーネントを処理
			for (auto aComponent : aActorComponents) {
				UStaticMeshComponent* SMCompornent = Cast<UStaticMeshComponent>(aComponent);
				if (nullptr != SMCompornent)
				{
					SaveMID = SMCompornent->GetMaterial(0);
				}
			}
		}
		//UKismetSystemLibrary::PrintString(this, "C++ Hello World!", true, true, FColor::Cyan, 2.f);
	}
	else {
		UKismetSystemLibrary::PrintString(this, "C++ Hello World!", true, true, FColor::Cyan, 2.f);
	}

	// 現在の頂点
	nNum = 0;
	// 波を発生
	vBlockArray[FMath::RandRange(0, vBlockArray.Num() - 1)].vPosArray[nNum].Z += X;
}

// Called every frame
void AAC_BlockManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 直前、直後の頂点取得
	int32 prev = (nNum + 2) % 3;	// prev ← num - 1
	int32 next = (nNum + 1) % 3;	// next ← num + 1

	float cth = (c * c * dt * dt) / (h * h);

	// 5秒に1度、波を生成
	if ((ulTimeCount % (int)((1.0f / DeltaTime) * 5)) == 0) {
		vBlockArray[FMath::RandRange(0, vBlockArray.Num() - 1)].vPosArray[nNum].Z += X;
		SetTarget();
	}

	// 波の高さを更新
// TODO: ここに波の高さを更新する処理を追加.
//
//   vertex[prev][j][i].pos.y … 前の波の高さ(n-1)
//   vertex[num][j][i].pos.y  … 現在の波の高さ(n)
//   vertex[next][j][i].pos.y … 次の波の高さ(n+1)(この値を求める)
//
	for (int j = 1; j < MaxBlock - 1; ++j)
	{
		for (int i = 1; i < MaxBlock - 1; ++i)
		{
			int nCurTarget = (j * MaxBlock) + i;


			vBlockArray[nCurTarget].vPosArray[next].Z =
				cth *
				(
					vBlockArray[nCurTarget + 1].vPosArray[nNum].Z +
					vBlockArray[nCurTarget - 1].vPosArray[nNum].Z +
					vBlockArray[nCurTarget + MaxBlock].vPosArray[nNum].Z +
					vBlockArray[nCurTarget - MaxBlock].vPosArray[nNum].Z
					) +
				(2 - 4 * cth) * vBlockArray[nCurTarget].vPosArray[nNum].Z -
				vBlockArray[nCurTarget].vPosArray[prev].Z;

			vBlockArray[nCurTarget].pActor->SetActorLocation(FVector(vBlockArray[nCurTarget].vPosArray[next]));
		}
	}

	// 参照座標を更新
	nNum = next;

	// 時間更新
	ulTimeCount++;
}


void AAC_BlockManager::SetTarget()
{
	// ブロック数がターゲット数より少なければ処理しない
	if (vBlockArray.Num() < MaxTarget)
		return;
	// 現在のターゲットをデフォルトに戻す
	for (auto aTarget : vTargetArray)
	{
		// ターゲットフラグ
		aTarget->TargetFlag = false;
		// 取得したコンポーネントを格納する配列
		TInlineComponentArray< UActorComponent* > aActorComponents(aTarget);
		// アクターが持つコンポーネントを複数取得
		aTarget->GetComponents< UActorComponent >(aActorComponents);
		// 取得したコンポーネントを処理
		for (auto aComponent : aActorComponents) {
			UStaticMeshComponent* SMCompornent = Cast<UStaticMeshComponent>(aComponent);
			if (nullptr != SMCompornent)
			{
				SMCompornent->SetMaterial(0, SaveMID);
			}
		}
	}
	// ターゲット配列クリア
	vTargetArray.Empty();

	// ランダムにターゲットを追加（重複なし）
	for (int i = 0; i < MaxTarget; ++i)
	{
		// ランダムにターゲットを決定
		AACTargetActor* pTarget = vBlockArray[FMath::RandRange(0, vBlockArray.Num() - 1)].pActor;
		// 配列に追加
		vTargetArray.AddUnique(pTarget);
		// ターゲットフラグ
		pTarget->TargetFlag = true;
		// 取得したコンポーネントを格納する配列
		TInlineComponentArray< UActorComponent* > aActorComponents(pTarget);
		// アクターが持つコンポーネントを複数取得
		pTarget->GetComponents< UActorComponent >(aActorComponents);
		// 取得したコンポーネントを処理
		for (auto aComponent : aActorComponents) {
			UStaticMeshComponent* SMCompornent = Cast<UStaticMeshComponent>(aComponent);
			if (nullptr != SMCompornent)
			{
				SMCompornent->SetMaterial(0, TargetMID);
			}
		}
	}
}
