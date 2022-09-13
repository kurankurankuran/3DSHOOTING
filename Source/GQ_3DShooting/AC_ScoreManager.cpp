// Fill out your copyright notice in the Description page of Project Settings.

#include "AC_ScoreManager.h"
#include "CustomGameInstance.h"
#include "UMGScore.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AAC_ScoreManager::AAC_ScoreManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAC_ScoreManager::BeginPlay()
{
	Super::BeginPlay();

	//Event Dispather
	for (TActorIterator<AAC_TargetHitEvent> ActItr(GEngine->GameViewport->GetWorld()); ActItr; ++ActItr)
	{
		AAC_TargetHitEvent* Call = *ActItr;
		Call->HitDispather.AddDynamic(this, &AAC_ScoreManager::AddScore);
	}

	FString path = "/Game/UI/UMGCurrentScore.UMGCurrentScore_C";
	TSubclassOf<class UUMGScore> WidgetClass = TSoftClassPtr<UUMGScore>(FSoftObjectPath(*path)).LoadSynchronous();
	UMGScore = CreateWidget<UUMGScore>(GetWorld(), WidgetClass);
	if (UMGScore != nullptr)
	{
		UMGScore->AddToViewport();
	}

	GameInstance = UCustomGameInstance::GetInstance();
	GameInstance->SetScore(0);

}


void AAC_ScoreManager::AddScore()
{
	
	int newScore = GameInstance->GetScore() + AddScoreNum;
	GameInstance->SetScore(newScore);
	UMGScore->UpdateScore_Implementation(newScore);
	UMGScore->UpdateScore(newScore);
}

void AAC_ScoreManager::CheckHighScore/*_Implementation*/()
{
	int Score = GameInstance->GetScore();
	int HighScore = GameInstance->GetHighScore();
	if (HighScore < Score)
	{
		GameInstance->SetHighScore(Score);
	}
}

//
//template <typename WidgetT = UUserWidget, typename OwnerT = UObject>
//WidgetT* CreateWidget(OwnerT* OwningObject, TSubclassOf<UUserWidget> UserWidgetClass = WidgetT::StaticClass(), FName WidgetName = NAME_None)
//{
//	static_assert(TIsDerivedFrom<WidgetT, UUserWidget>::IsDerived, "CreateWidget can only be used to create UserWidget instances. If creating a UWidget, use WidgetTree::ConstructWidget.");
//
//	static_assert(TIsDerivedFrom<OwnerT, UWidget>::IsDerived
//		|| TIsDerivedFrom<OwnerT, UWidgetTree>::IsDerived
//		|| TIsDerivedFrom<OwnerT, APlayerController>::IsDerived
//		|| TIsDerivedFrom<OwnerT, UGameInstance>::IsDerived
//		|| TIsDerivedFrom<OwnerT, UWorld>::IsDerived, "The given OwningObject is not of a supported type for use with CreateWidget.");
//
//	SCOPE_CYCLE_COUNTER(STAT_CreateWidget);
//
//	if (OwningObject)
//	{
//		return Cast<WidgetT>(UUserWidget::CreateWidgetInstance(*OwningObject, UserWidgetClass, WidgetName));
//	}
//	return nullptr;
//}
