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

	// �A�N�^�[�̃p�X
	FString aAssetPath = "/Game/Actor/AC_Target.AC_Target_C";

	// �A�Z�b�g��ǂݍ��ށi�����j
	TSubclassOf<AACTargetActor> aTargetClass = TSoftClassPtr<AACTargetActor>(FSoftObjectPath(*aAssetPath)).LoadSynchronous();

	// �u���b�N���X�|�[�����z�u
	// �ǂݍ��݊m�F
	if (aTargetClass != nullptr) {
		for (int i = 0; i < vBlockArray.Num(); ++i)
		{
			// �X�|�[��
			TObjectPtr< AACTargetActor> aTarget = GetWorld()->SpawnActor<AACTargetActor>(aTargetClass);
			// �Q��
			vBlockArray[i].pActor = aTarget;
			// ���W
			vBlockArray[i].vPosArray[nNum].X += (i % MaxBlock) * Interval;
			vBlockArray[i].vPosArray[nNum].Y += (i / MaxBlock) * Interval;
			vBlockArray[i].vPosArray[2] = vBlockArray[i].vPosArray[1] = vBlockArray[i].vPosArray[nNum];
			aTarget->SetActorLocation(vBlockArray[i].vPosArray[nNum]);
		}
		// �}�e���A���ۑ�
		if (0 < vBlockArray.Num())
		{
			// �擾�����R���|�[�l���g���i�[����z��
			TInlineComponentArray< UActorComponent* > aActorComponents(vBlockArray[0].pActor);
			// �A�N�^�[�����R���|�[�l���g�𕡐��擾
			vBlockArray[0].pActor->GetComponents< UActorComponent >(aActorComponents);
			// �擾�����R���|�[�l���g������
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

	// ���݂̒��_
	nNum = 0;
	// �g�𔭐�
	vBlockArray[FMath::RandRange(0, vBlockArray.Num() - 1)].vPosArray[nNum].Z += X;
}

// Called every frame
void AAC_BlockManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���O�A����̒��_�擾
	int32 prev = (nNum + 2) % 3;	// prev �� num - 1
	int32 next = (nNum + 1) % 3;	// next �� num + 1

	float cth = (c * c * dt * dt) / (h * h);

	// 5�b��1�x�A�g�𐶐�
	if ((ulTimeCount % (int)((1.0f / DeltaTime) * 5)) == 0) {
		vBlockArray[FMath::RandRange(0, vBlockArray.Num() - 1)].vPosArray[nNum].Z += X;
		SetTarget();
	}

	// �g�̍������X�V
// TODO: �����ɔg�̍������X�V���鏈����ǉ�.
//
//   vertex[prev][j][i].pos.y �c �O�̔g�̍���(n-1)
//   vertex[num][j][i].pos.y  �c ���݂̔g�̍���(n)
//   vertex[next][j][i].pos.y �c ���̔g�̍���(n+1)(���̒l�����߂�)
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

	// �Q�ƍ��W���X�V
	nNum = next;

	// ���ԍX�V
	ulTimeCount++;
}


void AAC_BlockManager::SetTarget()
{
	// �u���b�N�����^�[�Q�b�g����菭�Ȃ���Ώ������Ȃ�
	if (vBlockArray.Num() < MaxTarget)
		return;
	// ���݂̃^�[�Q�b�g���f�t�H���g�ɖ߂�
	for (auto aTarget : vTargetArray)
	{
		// �^�[�Q�b�g�t���O
		aTarget->TargetFlag = false;
		// �擾�����R���|�[�l���g���i�[����z��
		TInlineComponentArray< UActorComponent* > aActorComponents(aTarget);
		// �A�N�^�[�����R���|�[�l���g�𕡐��擾
		aTarget->GetComponents< UActorComponent >(aActorComponents);
		// �擾�����R���|�[�l���g������
		for (auto aComponent : aActorComponents) {
			UStaticMeshComponent* SMCompornent = Cast<UStaticMeshComponent>(aComponent);
			if (nullptr != SMCompornent)
			{
				SMCompornent->SetMaterial(0, SaveMID);
			}
		}
	}
	// �^�[�Q�b�g�z��N���A
	vTargetArray.Empty();

	// �����_���Ƀ^�[�Q�b�g��ǉ��i�d���Ȃ��j
	for (int i = 0; i < MaxTarget; ++i)
	{
		// �����_���Ƀ^�[�Q�b�g������
		AACTargetActor* pTarget = vBlockArray[FMath::RandRange(0, vBlockArray.Num() - 1)].pActor;
		// �z��ɒǉ�
		vTargetArray.AddUnique(pTarget);
		// �^�[�Q�b�g�t���O
		pTarget->TargetFlag = true;
		// �擾�����R���|�[�l���g���i�[����z��
		TInlineComponentArray< UActorComponent* > aActorComponents(pTarget);
		// �A�N�^�[�����R���|�[�l���g�𕡐��擾
		pTarget->GetComponents< UActorComponent >(aActorComponents);
		// �擾�����R���|�[�l���g������
		for (auto aComponent : aActorComponents) {
			UStaticMeshComponent* SMCompornent = Cast<UStaticMeshComponent>(aComponent);
			if (nullptr != SMCompornent)
			{
				SMCompornent->SetMaterial(0, TargetMID);
			}
		}
	}
}
