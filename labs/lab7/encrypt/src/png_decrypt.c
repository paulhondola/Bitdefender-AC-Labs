#include <stdio.h>
#include <stdlib.h>

// Rotate right (ROR) for 8-bit values
unsigned char ror(unsigned char value, int bits) {
  return (value >> bits) | (value << (8 - bits));
}

void decrypt_png(const char *input_file, const char *output_file) {
  // Open the encrypted PNG file in binary mode
  FILE *in = fopen(input_file, "rb");
  if (!in) {
    perror("Failed to open input file");
    exit(1);
  }

  // Determine the size of the file
  fseek(in, 0, SEEK_END);
  long size = ftell(in);
  fseek(in, 0, SEEK_SET);

  // Allocate memory for the encrypted data
  unsigned char *enc = malloc(size);
  if (!enc) {
    perror("Failed to allocate memory");
    fclose(in);
    exit(1);
  }

  // Read the encrypted data from the file
  fread(enc, 1, size, in);
  fclose(in);

  // Decrypt the data
  for (long i = 0; i < size; i++) {
    enc[i] = ror(enc[i], 4) ^ 0x44;
  }

  // Write the decrypted data to the output file
  FILE *out = fopen(output_file, "wb");
  if (!out) {
    perror("Failed to open output file");
    free(enc);
    exit(1);
  }

  fwrite(enc, 1, size, out);
  fclose(out);
  free(enc);

  printf("Decryption complete.\n");
}

int main(void) {
  char *input_file = "../encrypted/64bit_memory.png";
  char *output_file = "../decrypted/64bit_memory.png";
  decrypt_png(input_file, output_file);
  return 0;
}
