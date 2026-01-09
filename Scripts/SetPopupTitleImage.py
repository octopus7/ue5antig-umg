# Unreal Editor Python Script
# Sets the TitleBackgroundBrush image in DA_Style_Popup Data Asset
# Run this script inside Unreal Editor's Python console or via Remote Execution

import unreal

def set_popup_title_image(texture_path: str, data_asset_path: str = '/Game/UI/StyleData/DA_Style_Popup'):
    """
    Set the TitleBackgroundBrush texture in a popup style Data Asset.
    
    Args:
        texture_path: Game path to the texture, e.g. '/Game/UI/Textures/T_TitleBackground'
        data_asset_path: Game path to the Data Asset (default: '/Game/UI/StyleData/DA_Style_Popup')
    
    Returns:
        True on success, False on failure
    """
    # Load the Data Asset
    style_asset = unreal.load_asset(data_asset_path)
    if not style_asset:
        unreal.log_error(f"Failed to load Data Asset: {data_asset_path}")
        return False
    
    # Load the texture
    texture = unreal.load_asset(texture_path)
    if not texture:
        unreal.log_error(f"Failed to load texture: {texture_path}")
        return False
    
    unreal.log(f"Loaded texture: {texture.get_name()}")
    
    # Get current brush and modify it
    current_brush = style_asset.get_editor_property('TitleBackgroundBrush')
    unreal.log(f"Current brush type: {type(current_brush)}")
    
    # Create a new SlateBrush with the texture
    new_brush = unreal.SlateBrush()
    new_brush.set_editor_property('ResourceObject', texture)
    new_brush.set_editor_property('DrawAs', unreal.SlateBrushDrawType.IMAGE)
    new_brush.set_editor_property('Tiling', unreal.SlateBrushTileType.NO_TILE)
    new_brush.set_editor_property('ImageSize', unreal.Vector2D(256, 64))  # Adjust as needed
    
    # Set the new brush
    style_asset.set_editor_property('TitleBackgroundBrush', new_brush)
    
    # Mark as modified and save
    unreal.EditorAssetLibrary.save_asset(data_asset_path)
    unreal.log(f"Successfully updated TitleBackgroundBrush in {data_asset_path}")
    
    return True


# Example usage - modify these paths as needed
if __name__ == '__main__':
    # Change this to your actual texture path
    TEXTURE_PATH = '/Game/UI/Textures/T_TitleBackground'
    
    # Run the function
    success = set_popup_title_image(TEXTURE_PATH)
    
    if success:
        print("Title image updated successfully!")
    else:
        print("Failed to update title image. Check the Output Log for details.")
