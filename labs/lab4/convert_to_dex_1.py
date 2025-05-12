from PIL import Image

def to_rbitmap(image):
    """
    Converts image pixels into a list of 4-bit nibbles [high0, low0, high1, low1, ...]
    Each pixel (grayscale 0–255) becomes two 4-bit values.
    """
    image = image.convert('L')  # Convert to grayscale (1 byte per pixel)
    pixels = list(image.getdata())
    bytecode = []
    for b in pixels:
        bytecode.append((b >> 4) & 0x0F)  # High nibble
        bytecode.append(b & 0x0F)         # Low nibble
    return bytecode

def from_base63(bytecode):
    """
    Reconstruct bytes from nibble pairs, matching the Java fromBase63() method.
    """
    output = bytearray()
    for i in range(0, len(bytecode), 2):
        high = bytecode[i]
        low = bytecode[i + 1]
        combined = (high << 4) | low
        output.append(combined)
    return output

# Step 1: Load the PNG image
with open("logo.png", "rb") as f:
    image = Image.open(f)
    image.load()

# Step 2: Convert image to nibble-based representation
bytecode = to_rbitmap(image)

# Step 3: Convert nibble list back into bytes
bytes1 = from_base63(bytecode)

# Step 4: Save to module2.dex
with open("module2.dex", "wb") as out_file:
    out_file.write(bytes1)

print("Conversion complete. Output written to module2.dex")
