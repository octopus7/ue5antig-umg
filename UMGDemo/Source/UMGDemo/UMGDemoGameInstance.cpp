// Copyright octopus7. All Rights Reserved.

#include "UMGDemoGameInstance.h"
#include "UMGStyleDataAsset.h"
#include "UMGStyleSubsystem.h"
#include "UTestPopupStyleAsset.h"

void UUMGDemoGameInstance::Init() {
  Super::Init();

  // Get the style subsystem
  UUMGStyleSubsystem *StyleSubsystem = GetSubsystem<UUMGStyleSubsystem>();
  if (!StyleSubsystem) {
    return;
  }

  // Register the style asset with the subsystem
  if (StyleDataAsset) {
    StyleSubsystem->RegisterStyleAsset(StyleDataAsset);
  }

  // Register the popup style asset with the subsystem
  if (PopupStyleAsset) {
    StyleSubsystem->RegisterPopupStyleAsset(PopupStyleAsset);
  }
}
