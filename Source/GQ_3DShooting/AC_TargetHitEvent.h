// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AC_TargetHitEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitDispather);

UCLASS()
class GQ_3DSHOOTING_API AAC_TargetHitEvent : public AActor
{
	GENERATED_BODY()

public:
	//Event Dispather(Multicast Delegate)
	UPROPERTY(BlueprintAssignable)
		FHitDispather HitDispather;

public:
	UFUNCTION(BlueprintCallable)
		void HitFunc();

};
