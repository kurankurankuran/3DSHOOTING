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
		// �^�[�Q�b�g�t���O
		TargetFlag = false;
		if (HitMID != nullptr)
		{
			// �擾�����R���|�[�l���g���i�[����z��
			TInlineComponentArray< UActorComponent* > aActorComponents(this);
			// �A�N�^�[�����R���|�[�l���g�𕡐��擾
			GetComponents< UActorComponent >(aActorComponents);
			// �擾�����R���|�[�l���g������
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

