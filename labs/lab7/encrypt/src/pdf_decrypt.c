#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void decrypt_pdf(const char *in_path, const char *out_path) {
  // open file in binary mode
  FILE *fin = fopen(in_path, "rb");

  if (!fin) {
    fprintf(stderr, "Error opening input file: %s\n", in_path);
    return;
  }

  // determine file size
  fseek(fin, 0, SEEK_END);
  long size = ftell(fin);
  fseek(fin, 0, SEEK_SET);

  // allocate memory for encrypted and decrypted data
  uint8_t *enc = malloc(size), *dec = malloc(size);
  fread(enc, 1, size, fin);
  fclose(fin);

  // seed the CRT rand()
  // ONLY FOR MSVC
  srand((unsigned)size);

  // decrypt the data
  uint8_t sum = 0;
  for (long i = 0; i < size; i++) {
    unsigned char rb = (unsigned char)(rand() & 0xFF);
    uint8_t e = enc[i];
    dec[i] = (uint8_t)((e - sum) ^ rb);
    sum = e;
  }

  // write the decrypted data to the output file
  FILE *fout = fopen(out_path, "wb");

  if (!fout) {
    fprintf(stderr, "Error opening output file: %s\n", out_path);
    free(enc);
    free(dec);
    return;
  }

  fwrite(dec, 1, size, fout);
  fclose(fout);

  free(enc);
  free(dec);
  printf("Decrypted to %s\n", out_path);
}

int main(void) {
  char *input_file = "C:\\Users\\paulh\\Bitdefender-AC-"
                     "Labs\\labs\\lab7\\encrypt\\encrypted\\cpu.pdf";
  char *output_file = "C:\\Users\\paulh\\Bitdefender-AC-"
                      "Labs\\labs\\lab7\\encrypt\\decrypted\\cpu.pdf";
  decrypt_pdf(input_file, output_file);
  return 0;
}
