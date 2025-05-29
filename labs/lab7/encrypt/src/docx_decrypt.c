#include <stdio.h>
#include <stdlib.h>

void decrypt_docx(const char *input_path, const char *output_path) {

  // open file in binary mode
  FILE *in = fopen(input_path, "rb");
  if (!in) {
    perror("Failed to open input file");
    exit(1);
  }

  // determine file size
  fseek(in, 0, SEEK_END);
  long size = ftell(in);
  fseek(in, 0, SEEK_SET);

  // allocate memory for encrypted and decrypted data
  unsigned char *enc = malloc(size);
  unsigned char *dec = malloc(size);
  if (!enc || !dec) {
    perror("Memory allocation failed");
    fclose(in);
    exit(1);
  }

  // read the encrypted file
  fread(enc, 1, size, in);
  fclose(in);

  // reverse the encryption
  for (long i = 0; i < size; i++) {
    unsigned char c = enc[i];
    c ^= 0xC1;
    c += 0x4D;
    c ^= 0x8B;
    c -= 5;

    dec[i] = c;
  }

  // write the decrypted data to the output file
  FILE *out = fopen(output_path, "wb");
  if (!out) {
    perror("Failed to open output file");
    free(enc);
    free(dec);
    exit(1);
  }

  fwrite(dec, 1, size, out);
  fclose(out);
  free(enc);
  free(dec);

  printf("Decryption complete.\n");
}

int main(void) {
  char *input_file = "../encrypted/Qiew_overview.docx";
  char *output_file = "../decrypted/Qiew_overview.docx";
  decrypt_docx(input_file, output_file);
  return 0;
}
