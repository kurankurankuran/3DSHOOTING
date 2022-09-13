// Fill out your copyright notice in the Description page of Project Settings.


#include "ACTargetActor.h"

// Sets default values
AACTargetActor::AACTargetActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AACTargetActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AACTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AACTargetActor::HitEvent()
{
	if (TargetFlag)
	{
		// ターゲットフラグ
		TargetFlag = false;
		if (HitMID != nullptr)
		{
			// 取得したコンポーネントを格納する配列
			TInlineComponentArray< UActorComponent* > aActorComponents(this);
			// アクターが持つコンポーネントを複数取得
			GetComponents< UActorComponent >(aActorComponents);
			// 取得したコンポーネントを処理
			for (auto aComponent : aActorComponents) {
				UStaticMeshComponent* SMCompornent = Cast<UStaticMeshComponent>(aComponent);
				if (nullptr != SMCompornent)
				{
					SMCompornent->SetMaterial(0, HitMID);
					return true;
				}
			}
		}
	}

	return false;
}

