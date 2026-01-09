# UMGDemo Asset Import Script
# Run this script in Unreal Editor: Tools -> Execute Python Script
# Or run from command line with: UnrealEditor-Cmd.exe ProjectPath -ExecutePythonScript="ScriptPath"

import unreal
import os

def import_assets():
    """
    Import assets from UMGDemo-Images folder to Content folder.
    Source structure mirrors the target Content structure.
    Skips import if source file is older than existing uasset.
    """
    
    # Get project paths
    project_dir = unreal.Paths.project_dir()
    content_dir = os.path.join(project_dir, "Content")
    repo_root = os.path.dirname(project_dir.rstrip('/\\'))
    source_root = os.path.join(repo_root, "UMGDemo-Images")
    
    if not os.path.exists(source_root):
        unreal.log_error(f"Source folder not found: {source_root}")
        return
    
    unreal.log(f"=== Starting asset import from {source_root} ===")
    
    # Get asset tools
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    
    # Walk through source directory
    imported_count = 0
    skipped_count = 0
    for root, dirs, files in os.walk(source_root):
        for filename in files:
            # Skip non-image files
            ext = os.path.splitext(filename)[1].lower()
            if ext not in ['.png', '.jpg', '.jpeg', '.tga', '.bmp', '.exr']:
                continue
            
            source_path = os.path.join(root, filename)
            
            # Calculate relative path and check if uasset exists
            rel_path = os.path.relpath(root, source_root)
            asset_name = os.path.splitext(filename)[0]
            
            # Build path to potential existing uasset
            if rel_path == '.':
                uasset_path = os.path.join(content_dir, f"{asset_name}.uasset")
            else:
                uasset_path = os.path.join(content_dir, rel_path, f"{asset_name}.uasset")
            
            # Skip if source is older than existing uasset
            if os.path.exists(uasset_path):
                source_mtime = os.path.getmtime(source_path)
                uasset_mtime = os.path.getmtime(uasset_path)
                if source_mtime < uasset_mtime:
                    skipped_count += 1
                    continue  # Source is older, skip import
            
            # Calculate relative path from source root
            rel_path = os.path.relpath(root, source_root)
            
            # Determine destination in Content folder
            dest_content_path = f"/Game/{rel_path}".replace('\\', '/')
            if rel_path == '.':
                dest_content_path = "/Game"
            
            # Create import task
            task = unreal.AssetImportTask()
            task.filename = source_path
            task.destination_path = dest_content_path
            task.destination_name = os.path.splitext(filename)[0]
            task.replace_existing = True
            task.automated = True
            task.save = True
            
            # Execute import
            asset_tools.import_asset_tasks([task])
            
            # Check result using get_objects() (UE5.7+)
            imported_objects = task.get_objects()
            if imported_objects:
                unreal.log(f"Imported: {source_path} -> {dest_content_path}/{task.destination_name}")
                imported_count += 1
                
                # Configure texture settings for UI
                for obj in imported_objects:
                    if isinstance(obj, unreal.Texture2D):
                        # No compression for crisp UI
                        obj.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
                        # No mipmaps for UI textures
                        obj.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
                        # Set LOD group to UI
                        obj.set_editor_property("lod_group", unreal.TextureGroup.TEXTUREGROUP_UI)
                        # Save the modified asset
                        asset_path = f"{dest_content_path}/{task.destination_name}"
                        unreal.EditorAssetLibrary.save_asset(asset_path)
                        unreal.log(f"  -> Configured as UI texture (no compression, no mipmaps, UI group)")
            else:
                unreal.log_warning(f"Failed to import: {source_path}")
    
    unreal.log(f"=== Import Complete: {imported_count} imported, {skipped_count} skipped (unchanged) ===")

# Run the import
if __name__ == "__main__":
    import_assets()
