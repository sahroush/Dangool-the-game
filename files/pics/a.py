from PIL import Image

# Open the image file
img = Image.open("example.png")

# Convert the image to RGBA mode
img = img.convert("RGBA")

# Get the pixel data
pixels = img.load()

# Loop through each pixel and set the alpha value to 0 for white pixels
for i in range(img.size[0]):
    for j in range(img.size[1]):
        r, g, b, a = pixels[i, j]
        if r == 255 and g == 255 and b == 255:
            pixels[i, j] = (r, g, b, 0)

# Save the modified image
img.save("example_modified.png")
