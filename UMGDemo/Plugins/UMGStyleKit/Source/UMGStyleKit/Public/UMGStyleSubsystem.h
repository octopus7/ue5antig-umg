// Copyright octopus7. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UMGStyleDataAsset.h"
#include "UTestPopupStyleAsset.h"
#include "UMGStyleSubsystem.generated.h"


/**
 * GameInstance Subsystem for managing global UMG styles
 * Automatically created when GameInstance initializes
 */
UCLASS()
class UMGSTYLEKIT_API UUMGStyleSubsystem : public UGameInstanceSubsystem {
  GENERATED_BODY()

public:
  // USubsystem interface
  virtual void Initialize(FSubsystemCollectionBase &Collection) override;
  virtual void Deinitialize() override;

  /**
   * Register a style data asset for global access
   * @param StyleAsset The data asset containing style definitions
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  void RegisterStyleAsset(UUMGStyleDataAsset *StyleAsset);

  /**
   * Get the currently registered style data asset
   * @return The registered style data asset, or nullptr if none registered
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  UUMGStyleDataAsset *GetStyleAsset() const { return StyleDataAsset; }

  /**
   * Get a style by name from the registered data asset
   * @param StyleName The name of the style to retrieve
   * @return The style entry, or default style if not found
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  const FUMGStyleEntry &GetStyle(FName StyleName) const;

  /**
   * Check if a style asset is registered
   * @return True if a style asset is registered
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  bool HasStyleAsset() const { return StyleDataAsset != nullptr; }

  // ========== Popup Style Asset ==========

  /**
   * Register a popup style data asset for global access
   * @param PopupStyleAsset The data asset containing popup style definitions
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style|Popup")
  void RegisterPopupStyleAsset(UTestPopupStyleAsset *PopupStyleAsset);

  /**
   * Get the currently registered popup style data asset
   * @return The registered popup style asset, or nullptr if none registered
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style|Popup")
  UTestPopupStyleAsset *GetPopupStyleAsset() const {
    return PopupStyleDataAsset;
  }

  /**
   * Check if a popup style asset is registered
   * @return True if a popup style asset is registered
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style|Popup")
  bool HasPopupStyleAsset() const { return PopupStyleDataAsset != nullptr; }

private:
  UPROPERTY()
  TObjectPtr<UUMGStyleDataAsset> StyleDataAsset;

  UPROPERTY()
  TObjectPtr<UTestPopupStyleAsset> PopupStyleDataAsset;

  // Static default style for when no asset is registered
  static FUMGStyleEntry EmptyStyle;
};
