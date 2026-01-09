// Copyright octopus7. All Rights Reserved.

#include "UMGStyleDataAsset.h"

const FUMGStyleEntry &UUMGStyleDataAsset::GetStyle(FName StyleName) const {
  if (const FUMGStyleEntry *Found = Styles.Find(StyleName)) {
    return *Found;
  }
  return DefaultStyle;
}

bool UUMGStyleDataAsset::HasStyle(FName StyleName) const {
  return Styles.Contains(StyleName);
}
