from PIL import Image
import os

# Paths
sprite_sheet_path = 'Pacman\\resources\\pacmansprites2.png'
walking_frames_dir = 'Pacman\\resources\\walking_frames'
output_path = 'Pacman\\resources\\pacmansprites2.png'

# Cell size
cell_size = 25

# Load the existing sprite sheet
print(f"Loading sprite sheet: {sprite_sheet_path}")
original_img = Image.open(sprite_sheet_path)
original_width, original_height = original_img.size

print(f"Original size: {original_width}x{original_height}")
print(f"Expected: 6 columns * {cell_size} = {6 * cell_size}px wide")
print(f"Expected: 5 rows * {cell_size} = {5 * cell_size}px tall")

# Calculate new dimensions (add one column)
new_width = original_width + cell_size  # Add one column
new_height = original_height

# Create new image with the expanded size
print(f"\nCreating new sprite sheet: {new_width}x{new_height}")
new_img = Image.new('RGBA', (new_width, new_height), (0, 0, 0, 0))

# Copy the original sprite sheet to the left side
new_img.paste(original_img, (0, 0))
print("Copied original sprite sheet")

# Add black cell at row 0, column 6 (first cell of new column)
black_cell = Image.new('RGB', (cell_size, cell_size), (0, 0, 0))
x_pos = 6 * cell_size  # Column 6
y_pos = 0 * cell_size  # Row 0
new_img.paste(black_cell, (x_pos, y_pos))
print(f"Added black cell at column 6, row 0")

# Load and add walking frames to rows 1-5, column 6
print("\nAdding walking frames:")
for row in range(1, 6):  # Rows 1-5
    frame_num = row - 1  # frame_00, frame_01, etc.
    frame_path = f'{walking_frames_dir}\\frame_{frame_num:02d}.png'
    
    if os.path.exists(frame_path):
        frame_img = Image.open(frame_path)
        # Resize to 25x25 if needed
        if frame_img.size != (cell_size, cell_size):
            frame_img = frame_img.resize((cell_size, cell_size), Image.Resampling.LANCZOS)
        
        x_pos = 6 * cell_size  # Column 6
        y_pos = row * cell_size  # Row 1-5
        new_img.paste(frame_img, (x_pos, y_pos), frame_img if frame_img.mode == 'RGBA' else None)
        print(f"  Added frame_{frame_num:02d}.png to column 6, row {row}")
    else:
        print(f"  Warning: {frame_path} not found, skipping row {row}")

# Save the modified sprite sheet
print(f"\nSaving modified sprite sheet to: {output_path}")
new_img.save(output_path)
print("Done!")

