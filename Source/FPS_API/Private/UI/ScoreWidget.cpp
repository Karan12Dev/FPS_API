// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"
#include "Components/TextBlock.h"


void UScoreWidget::SetScore(const int32 PlayerScore) const
{
	TextBlock_Score->SetText(FText::AsNumber(PlayerScore));
}
