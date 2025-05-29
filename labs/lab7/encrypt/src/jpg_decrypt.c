#include <stdio.h>
#include <stdlib.h>

// Get nibble index from ASCII 'A' to 'P'
int find_index(unsigned char c) {
  if (c < 0x41 || c > 0x50)
    return -1; // not in range 'A'–'P'
  return c - 0x41;
}

void decrypt_jpg(const char *input_file, const char *output_file) {
  FILE *in = fopen(input_file, "rb");
  if (!in) {
    perror("Error opening input file");
    exit(1);
  }

  fseek(in, 0, SEEK_END);
  long enc_size = ftell(in);
  rewind(in);

  if (enc_size % 2 != 0) {
    fprintf(stderr, "Encrypted JPG size is not even.\n");
    fclose(in);
    exit(1);
  }

  unsigned char *enc = malloc(enc_size);
  fread(enc, 1, enc_size, in);
  fclose(in);

  unsigned char *dec = malloc(enc_size / 2);

  for (long i = 0; i < enc_size; i += 2) {
    int hi = find_index(enc[i]);
    int lo = find_index(enc[i + 1]);
    if (hi == -1 || lo == -1) {
      fprintf(stderr, "Invalid byte in encrypted JPG at %ld: %02X %02X\n", i,
              enc[i], enc[i + 1]);
      free(enc);
      free(dec);
      exit(1);
    }

    dec[i / 2] = (hi << 4) | lo;
  }

  FILE *out = fopen(output_file, "wb");
  if (!out) {
    perror("Error opening output file");
    free(enc);
    free(dec);
    exit(1);
  }

  fwrite(dec, 1, enc_size / 2, out);
  fclose(out);

  free(enc);
  free(dec);

  printf("✅ Decryption complete: %s\n", output_file);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <encrypted.jpg> <decrypted.jpg>\n", argv[0]);
    return 1;
  }

  decrypt_jpg(argv[1], argv[2]);
  return 0;
}
