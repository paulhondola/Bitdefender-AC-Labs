// decrypt_txt.c
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Rotate‐right an 8‐bit value by n bits
static inline uint8_t ror8(uint8_t v, int n) {
  return (uint8_t)((v >> n) | (v << (8 - n)));
}

// Reverse the per‐char transformation from sub_401034:
uint8_t decrypt_char(uint8_t e) {
  // 1) undo the final ROL 2 → ROR 2
  uint8_t d = ror8(e, 2);

  // 2) reverse the range‐based substitutions:
  if (d >= 'a' && d <= 'z') {
    // original was 'A'–'Z', mapped via:
    //   y = tolower(0x9B - x)
    // so x = 0x9B - toupper(y)
    uint8_t up = d & ~0x20; // toupper(d)
    return (uint8_t)(0x9B - up);
  } else if (d >= 'A' && d <= 'Z') {
    // original was 'a'–'z', mapped via:
    //   y = toupper(0xDB - x)
    // so x = 0xDB - tolower(y)
    uint8_t lo = d | 0x20; // tolower(d)
    return (uint8_t)(0xDB - lo);
  } else if (d >= '0' && d <= '9') {
    // original was '0'–'9', mapped via:
    //   y = 0x69 - x
    // so x = 0x69 - y
    return (uint8_t)(0x69 - d);
  }
  // else: non‐alphanumeric, they just did the ROL 2
  return d;
}

void decrypt_txt(const char *in_path, const char *out_path) {
  FILE *fin = fopen(in_path, "rb");
  if (!fin) {
    perror("fopen input");
    exit(1);
  }
  fseek(fin, 0, SEEK_END);
  long size = ftell(fin);
  fseek(fin, 0, SEEK_SET);

  uint8_t *buf = malloc(size);
  if (!buf) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }
  fread(buf, 1, size, fin);
  fclose(fin);

  for (long i = 0; i < size; i++) {
    buf[i] = decrypt_char(buf[i]);
  }

  FILE *fout = fopen(out_path, "wb");
  if (!fout) {
    perror("fopen output");
    exit(1);
  }
  fwrite(buf, 1, size, fout);
  fclose(fout);

  free(buf);
  printf("Decryption complete.\n");
}

int main(void) {
  char *input_file = "../encrypted/olly.txt";
  char *output_file = "../decrypted/olly.txt";
  decrypt_txt(input_file, output_file);
  return 0;
}
