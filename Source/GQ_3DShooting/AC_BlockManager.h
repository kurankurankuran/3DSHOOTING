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

	// �ߋ����ݖ����̃u���b�N���W�ۑ��p
	int32	nNum = 0;
	// �S�u���b�N�Ǘ��z��
	TArray<FBlockInfo> vBlockArray;
	// ���ԃJ�E���g
	unsigned long ulTimeCount;
	// �^�[�Q�b�g�u���b�N�Ǘ��p�z��
	TArray<AACTargetActor*> vTargetArray;
	// �u���b�N�f�t�H���g�̃}�e���A���ۑ��p
	class UMaterialInterface* SaveMID = nullptr;

public:
	// �z�u�u���b�N��Ӑ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int MaxBlock = 25;
	// �u���b�N���S�ԋ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Interval = 200;
	// �g�̑��x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float c = 4.0f;
	// ���Ԃ̍���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float dt = 1.0f;
	// �O���b�h��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float h = 400.0f;
	// �g�̏㉺�ړ����x
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float X = -100.0f;
	// �^�[�Q�b�g�u���b�N��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int MaxTarget = 50;
	// �^�[�Q�b�g�}�e���A��
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
	// �u���b�N����^�[�Q�b�g��I�����ݒ�
	void SetTarget();
};
