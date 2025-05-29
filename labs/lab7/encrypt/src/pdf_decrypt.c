#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t _state;

// seed
void my_srand(uint32_t seed) { _state = seed; }

// exactly MSVC’s algorithm
uint32_t msvc_rand(void) {
  _state = _state * 214013u + 2531011u;
  return (_state >> 16) & 0x7FFF;
}

// produce the 8-bit byte used in the PDF encrypt/decrypt
unsigned char next_rand_byte(void) {
  return (unsigned char)(msvc_rand() & 0xFF);
}

void decrypt_pdf(const char *in_path, const char *out_path) {
  // --- Read entire encrypted file into memory ---
  FILE *fin = fopen(in_path, "rb");
  if (!fin) {
    perror("fopen input");
    exit(1);
  }
  fseek(fin, 0, SEEK_END);
  long size = ftell(fin);
  rewind(fin);

  uint8_t *enc = malloc(size);
  uint8_t *dec = malloc(size);
  if (!enc || !dec) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  if (fread(enc, 1, size, fin) != (size_t)size) {
    perror("fread");
    exit(1);
  }

  fclose(fin);

  // Seed PRNG with the file size (same as assembly: srand(Size))
  srand((unsigned)size);

  // Decrypt byte by byte
  // sum corresponds to [esp+168h+var_155] in the ASM, initialized to 0
  unsigned char sum = 0;
  for (long i = 0; i < size; i++) {
    unsigned char rand_b = next_rand_byte();

    unsigned char e = enc[i];
    // reverse: orig = (enc - sum) ^ rand_b
    unsigned char o = (unsigned char)((e - sum) ^ rand_b);
    dec[i] = o;

    // update sum = enc (as per ASM: mov [var_155], cl)
    sum = e;
  }

  // Write out the decrypted PDF
  FILE *fout = fopen(out_path, "wb");
  if (!fout) {
    perror("fopen output");
    exit(1);
  }
  if (fwrite(dec, 1, size, fout) != (size_t)size) {
    perror("fwrite");
    exit(1);
  }

  fclose(fout);

  free(enc);
  free(dec);

  printf("Decryption complete.\n");
}

int main(int argc, char **argv) {
  char *input_file = "../encrypted/cpu.pdf";
  char *output_file = "../decrypted/cpu.pdf";
  decrypt_pdf(input_file, output_file);
  return 0;
}
