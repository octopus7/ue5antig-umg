# Remote Execute for SetPopupTitleImage
# Run this script from outside Unreal to remotely execute SetPopupTitleImage.py

import sys
import os
import argparse

# Add Unreal Engine's Python path
ue_python_path = r"E:\WorkTemp\Epic Games\UE_5.7\Engine\Plugins\Experimental\PythonScriptPlugin\Content\Python"
if os.path.exists(ue_python_path):
    sys.path.insert(0, ue_python_path)

def main():
    parser = argparse.ArgumentParser(description='Set popup title image in Unreal Editor')
    parser.add_argument('texture_path', help="Game path to texture, e.g. '/Game/UI/Textures/T_TitleBackground'")
    parser.add_argument('--data-asset', default='/Game/UI/StyleData/DA_Style_Popup',
                       help='Game path to the popup style Data Asset')
    args = parser.parse_args()
    
    # Build the script to execute
    script_content = f'''
import unreal

texture_path = "{args.texture_path}"
data_asset_path = "{args.data_asset}"

# Load assets
style_asset = unreal.load_asset(data_asset_path)
texture = unreal.load_asset(texture_path)

if not style_asset:
    print(f"ERROR: Failed to load Data Asset: {{data_asset_path}}")
elif not texture:
    print(f"ERROR: Failed to load texture: {{texture_path}}")
else:
    # Create new brush with texture
    new_brush = unreal.SlateBrush()
    new_brush.set_editor_property('ResourceObject', texture)
    new_brush.set_editor_property('DrawAs', unreal.SlateBrushDrawType.IMAGE)
    new_brush.set_editor_property('Tiling', unreal.SlateBrushTileType.NO_TILE)
    
    # Set and save
    style_asset.set_editor_property('TitleBackgroundBrush', new_brush)
    unreal.EditorAssetLibrary.save_asset(data_asset_path)
    print(f"SUCCESS: Set TitleBackgroundBrush to {{texture_path}}")
'''
    
    try:
        import remote_execution as remote
        
        remote_exec = remote.RemoteExecution()
        remote_exec.start()
        
        import time
        time.sleep(2)
        
        nodes = remote_exec.remote_nodes
        if nodes:
            print(f"Found {len(nodes)} Unreal Editor node(s)")
            node_id = nodes[0]['node_id']
            print(f"Connecting to: {nodes[0]['project_name']}")
            
            remote_exec.open_command_connection(node_id)
            time.sleep(1)
            
            if remote_exec.has_command_connection():
                print("Running command...")
                result = remote_exec.run_command(script_content, exec_mode='ExecuteFile', unattended=True)
                print(f"Result: {result}")
            else:
                print("Failed to establish command connection")
            
            remote_exec.close_command_connection()
        else:
            print("No Unreal Editor nodes found. Enable Remote Execution in Editor Preferences > Python.")
        
        remote_exec.stop()
        
    except ImportError as e:
        print(f"Could not import remote_execution: {e}")
        print("Make sure Unreal Editor is running with Python Remote Execution enabled.")

if __name__ == '__main__':
    main()
