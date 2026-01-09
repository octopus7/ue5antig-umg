"""
Split 2x2 cake grid image into 4 individual images with transparency extraction.
Uses content-based transparency extraction (white background removal).
"""

from PIL import Image
import os
import sys

def extract_transparency(img):
    """
    Extract transparency based on content - remove white/near-white background.
    Uses the image content to determine what should be transparent.
    """
    # Convert to RGBA if not already
    if img.mode != 'RGBA':
        img = img.convert('RGBA')
    
    pixels = img.load()
    width, height = img.size
    
    for y in range(height):
        for x in range(width):
            r, g, b, a = pixels[x, y]
            
            # Check if pixel is white or near-white (background)
            # Using a high threshold for white detection
            if r > 240 and g > 240 and b > 240:
                # Make fully transparent
                pixels[x, y] = (r, g, b, 0)
            else:
                # Calculate alpha based on how far from white
                # This creates smooth edges
                white_distance = ((255 - r) + (255 - g) + (255 - b)) / 3
                
                if white_distance < 30:
                    # Semi-transparent for near-white pixels (anti-aliasing)
                    alpha = int(white_distance * 255 / 30)
                    pixels[x, y] = (r, g, b, alpha)
                # else: keep original alpha (fully opaque)
    
    return img


def split_and_process(input_path, output_dir):
    """
    Split a 2x2 grid image into 4 individual images with transparency.
    """
    # Load the image
    img = Image.open(input_path)
    width, height = img.size
    
    # Calculate individual cake dimensions
    cake_width = width // 2
    cake_height = height // 2
    
    # Define cake names based on their characteristics
    cake_names = [
        "T_StrawberryShortcake",   # Top-left: pink strawberry
        "T_ChocoCherryCake",       # Top-right: chocolate with cherries
        "T_RainbowUnicornCake",    # Bottom-left: rainbow unicorn
        "T_BlueberryCheesecake"    # Bottom-right: blueberry
    ]
    
    # Define cropping regions (left, upper, right, lower)
    regions = [
        (0, 0, cake_width, cake_height),                     # Top-left
        (cake_width, 0, width, cake_height),                 # Top-right
        (0, cake_height, cake_width, height),                # Bottom-left
        (cake_width, cake_height, width, height)             # Bottom-right
    ]
    
    # Create output directory if it doesn't exist
    os.makedirs(output_dir, exist_ok=True)
    
    # Process each cake
    output_paths = []
    for i, (region, name) in enumerate(zip(regions, cake_names)):
        # Crop the cake
        cake_img = img.crop(region)
        
        # Extract transparency
        cake_img = extract_transparency(cake_img)
        
        # Save as PNG with transparency
        output_path = os.path.join(output_dir, f"{name}.png")
        cake_img.save(output_path, "PNG")
        print(f"Saved: {output_path}")
        output_paths.append(output_path)
    
    return output_paths


if __name__ == "__main__":
    # Input path
    input_image = r"C:\Users\blendue\.gemini\antigravity\brain\5fd88a38-e549-423f-be0e-d4d9cdd25bf6\cake_grid_2x2_1767944959316.png"
    
    # Output directory for processed images
    output_directory = r"d:\github\ue5antig-umg\UMGDemo-Images\UI\Textures"
    
    # Split and process
    paths = split_and_process(input_image, output_directory)
    print(f"\nProcessed {len(paths)} cake images with transparency.")
