// Copyright octopus7. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UMGDemoGameInstance.generated.h"

class UUMGStyleDataAsset;
class UTestPopupStyleAsset;

/**
 * Game Instance for UMGDemo project
 * Handles global style registration
 */
UCLASS()
class UMGDEMO_API UUMGDemoGameInstance : public UGameInstance {
  GENERATED_BODY()

public:
  virtual void Init() override;

  // Style Data Asset to register globally
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Style")
  TObjectPtr<UUMGStyleDataAsset> StyleDataAsset;

  // Popup Style Data Asset to register globally
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Style")
  TObjectPtr<UTestPopupStyleAsset> PopupStyleAsset;
};
