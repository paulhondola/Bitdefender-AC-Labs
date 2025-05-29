table = [
    0x23, 0x2E, 0x2B, 0x2D, 0x5F,
    0x30, 0x31, 0x32, 0x33, 0x34,
    0x35, 0x36, 0x37, 0x38, 0x39,
    0x41
]

def reverse_lookup(byte):
    if byte not in table:
        raise ValueError(f"Unknown byte: {byte:#x}")
    return table.index(byte)

def decrypt_jpg(input_path, output_path):
    with open(input_path, "rb") as f:
        enc = f.read()

    if len(enc) % 2 != 0:
        raise ValueError("Encrypted JPG size must be even.")

    dec = bytearray(len(enc) // 2)

    for i in range(0, len(enc), 2):
        hi = reverse_lookup(enc[i])
        lo = reverse_lookup(enc[i+1])
        dec[i // 2] = (hi << 4) | lo

    with open(output_path, "wb") as f:
        f.write(dec)

    print(f"✅ Decryption complete: {output_path}")

if __name__ == "__main__":
	main_input = "../encrypted/Drawing1.jpg"
	main_output = "../decrypted/Drawing1.jpg"
	decrypt_jpg(main_input, main_output)
