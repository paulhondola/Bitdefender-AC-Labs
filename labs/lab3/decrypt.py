import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad

INPUT_DIR = 'sdcard/DCIM/camera'
INPUT_FILE = 'sdcard/Download/text.txt'
KEY_FILE = 'sdcard/SECRETS/nothingsecrethere'
OUTPUT_DIR = 'decrypted_output'
OUTPUT_FILE = 'decrypted_output/text.txt'
IV = b'The BigIV\'s here'

def read_keys(keyfile_path):
    with open(keyfile_path, 'r') as f:
        return [line.strip() for line in f if line.strip()]

def try_decrypt(data, key):
    try:
        key_bytes = key.encode('utf-8')
        cipher = AES.new(key_bytes, AES.MODE_CBC, IV)
        decrypted = unpad(cipher.decrypt(data), AES.block_size)
        return decrypted
    except Exception:
        return None

def decrypt_directory(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

    keys = read_keys(KEY_FILE)
    files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]

    for file_name in files:
        file_path = os.path.join(directory, file_name)
        with open(file_path, 'rb') as f:
            encrypted_data = f.read()

        for key in keys:
            print(f"Trying key '{key}' on file: {file_name}")
            decrypted = try_decrypt(encrypted_data, key)
            if decrypted:
                output_path = os.path.join(OUTPUT_DIR, file_name)
                with open(output_path, 'wb') as out_f:
                    out_f.write(decrypted)
                print(f"✅ Decrypted '{file_name}' with key: {key}")
                break

def decrypt_file(file_path):
    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    keys = read_keys(KEY_FILE)
    file_name = os.path.basename(file_path)

    with open(file_path, 'rb') as f:
        encrypted_data = f.read()

    for key in keys:
        print(f"Trying key '{key}' on file: {file_name}")
        decrypted = try_decrypt(encrypted_data, key)
        if decrypted:
            output_path = os.path.join(OUTPUT_DIR, file_name)
            with open(output_path, 'wb') as out_f:
                out_f.write(decrypted)
            print(f"✅ Decrypted '{file_name}' with key: {key}")
            break

if __name__ == '__main__':
	decrypt_file(INPUT_FILE)
	decrypt_directory(INPUT_DIR)
