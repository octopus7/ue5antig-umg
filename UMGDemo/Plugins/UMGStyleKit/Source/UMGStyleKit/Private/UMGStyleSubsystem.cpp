// Copyright octopus7. All Rights Reserved.

#include "UMGStyleSubsystem.h"

FUMGStyleEntry UUMGStyleSubsystem::EmptyStyle;

void UUMGStyleSubsystem::Initialize(FSubsystemCollectionBase &Collection) {
  Super::Initialize(Collection);
}

void UUMGStyleSubsystem::Deinitialize() {
  StyleDataAsset = nullptr;
  PopupStyleDataAsset = nullptr;
  Super::Deinitialize();
}

void UUMGStyleSubsystem::RegisterStyleAsset(UUMGStyleDataAsset *StyleAsset) {
  StyleDataAsset = StyleAsset;
}

void UUMGStyleSubsystem::RegisterPopupStyleAsset(
    UTestPopupStyleAsset *PopupStyleAsset) {
  PopupStyleDataAsset = PopupStyleAsset;
}

const FUMGStyleEntry &UUMGStyleSubsystem::GetStyle(FName StyleName) const {
  if (StyleDataAsset) {
    return StyleDataAsset->GetStyle(StyleName);
  }
  return EmptyStyle;
}
