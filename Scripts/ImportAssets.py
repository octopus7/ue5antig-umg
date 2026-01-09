# UMGDemo Asset Import Script
# Run this script in Unreal Editor: Tools -> Execute Python Script
# Or run from command line with: UnrealEditor-Cmd.exe ProjectPath -ExecutePythonScript="ScriptPath"

import unreal
import os

def import_assets():
    """
    Import assets from UMGDemo-Images folder to Content folder.
    Source structure mirrors the target Content structure.
    """
    
    # Get project paths
    project_dir = unreal.Paths.project_dir()
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
    for root, dirs, files in os.walk(source_root):
        for filename in files:
            # Skip non-image files
            ext = os.path.splitext(filename)[1].lower()
            if ext not in ['.png', '.jpg', '.jpeg', '.tga', '.bmp', '.exr']:
                continue
            
            source_path = os.path.join(root, filename)
            
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
            else:
                unreal.log_warning(f"Failed to import: {source_path}")
    
    unreal.log(f"=== Import Complete: {imported_count} assets imported ===")

# Run the import
if __name__ == "__main__":
    import_assets()
