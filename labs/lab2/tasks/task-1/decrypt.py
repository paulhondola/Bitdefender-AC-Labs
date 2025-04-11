from functools import reduce
from hashlib import md5

# offset for each level
level_1_offset = 1
level_2_offset = 10
level_3_offset = 100
level_4_offset = 1100

# lambda function to get a int from a char
def map_string(s):
    return list(map(lambda s: ord(s) - ord('A'), s))

# convert the list into an integer and add the offset
def convert_list_to_int(lst, offset):
    return reduce(lambda x, y: x * 10 + y, lst) + offset

str_digits = ["9", "8", "7", "6", "5", "4", "3", "2", "1", "0", "a", "b", "c", "d", "e", "f"]

def byte_to_array_string(b):
    # Convert signed byte to unsigned (Java-style)
    i = b
    if b >= 0:
        i = b
    else:
        i = b + 256
    return str_digits[i // 16] + str_digits[i % 16]

def byte_to_string(byte_arr):
    return ''.join(byte_to_array_string(b) for b in byte_arr)

def get_md5_code(s):
    try:
        s = str(s)
        md5_bytes = md5(s.encode('utf-8')).digest()
        return byte_to_string(md5_bytes)
    except Exception as e:
        print("Error computing MD5:", e)
        return None

def get_decrypted_code(offset):
	print("Enter the code to decrypt:")
	user_input = input()
	mapped_string = map_string(user_input)
	return convert_list_to_int(mapped_string, offset)

def cmdline_user_interface():
	print("First Level:")
	print(get_decrypted_code(level_1_offset))

	print("Second Level:")
	print(get_decrypted_code(level_2_offset))

	print("Third Level:")
	code = get_decrypted_code(level_3_offset)
	print(get_md5_code(code))

	print("Fourth Level:")
	code = get_decrypted_code(level_4_offset)
	print(get_md5_code(code))

if __name__ == "__main__":
	cmdline_user_interface()
