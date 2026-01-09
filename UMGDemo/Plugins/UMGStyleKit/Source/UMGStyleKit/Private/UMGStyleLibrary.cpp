// Copyright octopus7. All Rights Reserved.

#include "UMGStyleLibrary.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "UMGStyleSubsystem.h"


UUMGStyleSubsystem *
UUMGStyleLibrary::GetStyleSubsystem(const UObject *WorldContextObject) {
  if (!WorldContextObject) {
    return nullptr;
  }

  const UWorld *World = WorldContextObject->GetWorld();
  if (!World) {
    return nullptr;
  }

  UGameInstance *GameInstance = World->GetGameInstance();
  if (!GameInstance) {
    return nullptr;
  }

  return GameInstance->GetSubsystem<UUMGStyleSubsystem>();
}

FUMGStyleEntry UUMGStyleLibrary::GetStyle(const UObject *WorldContextObject,
                                          FName StyleName) {
  if (UUMGStyleSubsystem *Subsystem = GetStyleSubsystem(WorldContextObject)) {
    return Subsystem->GetStyle(StyleName);
  }
  return FUMGStyleEntry();
}

void UUMGStyleLibrary::ApplyStyleToTextBlock(UTextBlock *TextBlock,
                                             const FUMGStyleEntry &Style) {
  if (!TextBlock) {
    return;
  }

  TextBlock->SetFont(Style.Font);
  TextBlock->SetColorAndOpacity(Style.TextColor);
}

void UUMGStyleLibrary::ApplyStyleToBorder(UBorder *Border,
                                          const FUMGStyleEntry &Style) {
  if (!Border) {
    return;
  }

  Border->SetBrush(Style.BackgroundBrush);
  Border->SetPadding(Style.Padding);
}

void UUMGStyleLibrary::ApplyStyleToButton(UButton *Button,
                                          const FUMGStyleEntry &Style) {
  if (!Button) {
    return;
  }

  FButtonStyle ButtonStyle = Button->GetStyle();
  ButtonStyle.Normal = Style.BackgroundBrush;
  ButtonStyle.Hovered = Style.BackgroundBrush;
  ButtonStyle.Pressed = Style.BackgroundBrush;
  Button->SetStyle(ButtonStyle);
}

void UUMGStyleLibrary::ApplyStyleToImage(UImage *Image,
                                         const FUMGStyleEntry &Style) {
  if (!Image) {
    return;
  }

  Image->SetBrush(Style.BackgroundBrush);
}
