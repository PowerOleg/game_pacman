from PIL import Image, ImageDraw
import os

# Create output directory if it doesn't exist
output_dir = 'Pacman\\resources\\walking_frames'
os.makedirs(output_dir, exist_ok=True)

# Yellow color
yellow = (255, 255, 0, 255)

def draw_walking_frame(frame_num, draw):
    """
    Draw a walking human frame
    frame_num: 0-9, determines the phase of the walking cycle
    """
    # Calculate walking phase (0.0 to 1.0)
    phase = frame_num / 10.0
    
    # Head stays in same position
    draw.ellipse([8, 2, 16, 8], fill=yellow)
    
    # Body (rectangle) - slight vertical movement
    body_y_offset = int(1 * (0.5 - abs(phase - 0.5) * 2))  # Slight bounce
    draw.rectangle([10, 8 + body_y_offset, 14, 18 + body_y_offset], fill=yellow)
    
    # Calculate leg and arm positions based on phase
    # Legs alternate: when one is forward, the other is back
    left_leg_forward = phase < 0.5  # Left leg forward in first half
    right_leg_forward = phase >= 0.5  # Right leg forward in second half
    
    # Arm positions (opposite to legs for natural walking)
    left_arm_forward = phase >= 0.5
    right_arm_forward = phase < 0.5
    
    # Leg forward/back offset
    leg_offset = 2
    
    # Left leg
    if left_leg_forward:
        # Left leg forward
        draw.rectangle([8 - leg_offset, 18 + body_y_offset, 11 - leg_offset, 22 + body_y_offset], fill=yellow)
    else:
        # Left leg back
        draw.rectangle([8 + leg_offset, 18 + body_y_offset, 11 + leg_offset, 22 + body_y_offset], fill=yellow)
    
    # Right leg
    if right_leg_forward:
        # Right leg forward
        draw.rectangle([13 + leg_offset, 18 + body_y_offset, 16 + leg_offset, 22 + body_y_offset], fill=yellow)
    else:
        # Right leg back
        draw.rectangle([13 - leg_offset, 18 + body_y_offset, 16 - leg_offset, 22 + body_y_offset], fill=yellow)
    
    # Arm forward/back offset
    arm_offset = 2
    
    # Left arm
    if left_arm_forward:
        # Left arm forward
        draw.rectangle([6 - arm_offset, 10 + body_y_offset, 10 - arm_offset, 14 + body_y_offset], fill=yellow)
    else:
        # Left arm back
        draw.rectangle([6 + arm_offset, 10 + body_y_offset, 10 + arm_offset, 14 + body_y_offset], fill=yellow)
    
    # Right arm
    if right_arm_forward:
        # Right arm forward
        draw.rectangle([14 + arm_offset, 10 + body_y_offset, 18 + arm_offset, 14 + body_y_offset], fill=yellow)
    else:
        # Right arm back
        draw.rectangle([14 - arm_offset, 10 + body_y_offset, 18 - arm_offset, 14 + body_y_offset], fill=yellow)

# Generate 10 frames
print("Creating 10 walking animation frames...")
for frame in range(10):
    # Create a 25x25 transparent image
    img = Image.new('RGBA', (25, 25), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    
    # Draw the walking frame
    draw_walking_frame(frame, draw)
    
    # Save the frame
    frame_path = f'{output_dir}\\frame_{frame:02d}.png'
    img.save(frame_path)
    print(f"Created: {frame_path}")

print("\nAll 10 frames created successfully!")
print(f"Frames saved in: {output_dir}")

