// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_TargetHitEvent.h"

void AAC_TargetHitEvent::HitFunc()
{
	HitDispather.Broadcast();
}