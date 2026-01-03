from PIL import Image, ImageDraw

# Create a 25x25 transparent image
img = Image.new('RGBA', (25, 25), (0, 0, 0, 0))
draw = ImageDraw.Draw(img)

# Yellow color
yellow = (255, 255, 0, 255)

# Draw a simple human shape:
# Head (circle/ellipse at top)
draw.ellipse([8, 2, 16, 8], fill=yellow)

# Body (rectangle)
draw.rectangle([10, 8, 14, 18], fill=yellow)

# Left arm
draw.rectangle([6, 10, 10, 14], fill=yellow)

# Right arm
draw.rectangle([14, 10, 18, 14], fill=yellow)

# Left leg
draw.rectangle([8, 18, 11, 22], fill=yellow)

# Right leg
draw.rectangle([13, 18, 16, 22], fill=yellow)

# Save the image
img.save('Pacman\\resources\\picture.png')
print("Image created successfully!")


