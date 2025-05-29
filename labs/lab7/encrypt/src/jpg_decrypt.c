#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Substitution table from byte_403294 in the binary
// AkjsSHwiE27.[$+#
static const uint8_t table[16] = {
    0x41, // 'A'
    0x6B, // 'k'
    0x6A, // 'j'
    0x73, // 's'
    0x53, // 'S'
    0x48, // 'H'
    0x77, // 'w'
    0x69, // 'i'
    0x45, // 'E'
    0x32, // '2'
    0x37, // '7'
    0x2E, // '.'
    0x5B, // '['
    0x24, // '$'
    0x2B, // '+'
    0x23  // '#'
};

// Find the index of c in table[]
static int reverse_lookup(uint8_t c) {
  for (int i = 0; i < 16; i++)
    if (table[i] == c)
      return i;
  return -1;
}

void decrypt_jpg(const char *in_path, const char *out_path) {

  // open file in binary mode
  FILE *fin = fopen(in_path, "rb");
  if (!fin) {
    perror("fopen input");
    exit(1);
  }

  // determine file size
  fseek(fin, 0, SEEK_END);
  long size = ftell(fin);
  fseek(fin, 0, SEEK_SET);

  // incorrect size check
  if (size % 2 != 0) {
    fprintf(stderr, "Error: encrypted size must be even\n");
    exit(1);
  }

  // allocate memory for encrypted and decrypted data
  uint8_t *enc = malloc(size);
  uint8_t *dec = malloc(size / 2);
  if (!enc || !dec) {
    perror("malloc");
    exit(1);
  }

  // read the encrypted file
  if (fread(enc, 1, size, fin) != size) {
    perror("fread");
    exit(1);
  }
  fclose(fin);

  // decrypt the data
  for (long i = 0; i < size; i += 2) {
    // set the high and low nibbles
    int hi = reverse_lookup(enc[i]);
    int lo = reverse_lookup(enc[i + 1]);

    // if either nibble is not found, print an error and exit
    if (hi < 0 || lo < 0) {
      fprintf(stderr, "Unknown byte pair at offset %ld: %02X %02X\n", i, enc[i],
              enc[i + 1]);
      exit(1);
    }

    // combine the nibbles into a byte
    dec[i / 2] = (uint8_t)((hi << 4) | lo);
  }

  // write the decrypted data to the output file
  FILE *fout = fopen(out_path, "wb");
  if (!fout) {
    perror("fopen output");
    exit(1);
  }

  fwrite(dec, 1, size / 2, fout);
  fclose(fout);

  free(enc);
  free(dec);
  printf("Decryption complete.\n");
}

int main(int argc, char **argv) {
  char *input_file = "../encrypted/Drawing1.jpg";
  char *output_file = "../decrypted/Drawing1.jpg";
  decrypt_jpg(input_file, output_file);
  return 0;
}
