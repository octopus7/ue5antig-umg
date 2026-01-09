# Remote Execute using Unreal's built-in remote_execution module
# This script runs outside of Unreal and uses Python's sys.path to access
# Unreal's internal Python modules

import sys
import os

# Add Unreal Engine's Python path
ue_python_path = r"E:\WorkTemp\Epic Games\UE_5.7\Engine\Plugins\Experimental\PythonScriptPlugin\Content\Python"
if os.path.exists(ue_python_path):
    sys.path.insert(0, ue_python_path)

try:
    import remote_execution as remote
    
    # Connect to the running Unreal Editor
    remote_exec = remote.RemoteExecution()
    remote_exec.start()
    
    # Wait for node discovery
    import time
    time.sleep(2)
    
    # Get available nodes
    nodes = remote_exec.remote_nodes
    if nodes:
        print(f"Found {len(nodes)} Unreal Editor node(s)")
        node_info = nodes[0]
        node_id = node_info['node_id']
        print(f"Connecting to: {node_info['project_name']} on {node_info['machine']}")
        print(f"Node ID: {node_id}")
        
        # Execute the import script
        script_path = r"d:/github/ue5antig-umg/Scripts/ImportAssets.py"
        with open(script_path, 'r', encoding='utf-8') as f:
            script_content = f.read()
        
        try:
            # First open connection to the node
            print("Opening command connection...")
            remote_exec.open_command_connection(node_id)
            time.sleep(1)
            
            if remote_exec.has_command_connection():
                print("Connection established! Running command...")
                result = remote_exec.run_command(script_content, exec_mode='ExecuteFile', unattended=True)
                print(f"Result: {result}")
            else:
                print("Failed to establish command connection")
                
        except Exception as cmd_err:
            print(f"Command execution error: {cmd_err}")
        finally:
            print("Closing command connection...")
            remote_exec.close_command_connection()
    else:
        print("No Unreal Editor nodes found. Make sure Remote Execution is enabled.")
    
    remote_exec.stop()
except ImportError as e:
    print(f"Could not import remote_execution module: {e}")
    print("Trying alternative approach...")
    
    # Alternative: Use HTTP Remote Control API if available
    import urllib.request
    import json
    
    script_path = r"d:/github/ue5antig-umg/Scripts/ImportAssets.py"
    with open(script_path, 'r', encoding='utf-8') as f:
        script_content = f.read()
    
    payload = {
        "objectPath": "/Script/PythonScriptPlugin.Default__PyCommandlet",
        "functionName": "ExecuteCommand", 
        "parameters": {
            "Command": f"py exec(open(r'{script_path}').read())"
        }
    }
    
    try:
        req = urllib.request.Request(
            "http://127.0.0.1:30010/remote/object/call",
            data=json.dumps(payload).encode('utf-8'),
            headers={'Content-Type': 'application/json'},
            method='PUT'
        )
        response = urllib.request.urlopen(req, timeout=10)
        print(f"HTTP Remote Control response: {response.read().decode()}")
    except Exception as http_err:
        print(f"HTTP Remote Control failed: {http_err}")
        print("\nMake sure one of these is enabled in Unreal Editor:")
        print("1. Python Remote Execution (Edit -> Editor Preferences -> Python)")
        print("2. Remote Control API (Edit -> Plugins -> Web Remote Control)")
except Exception as e:
    print(f"Error: {e}")
