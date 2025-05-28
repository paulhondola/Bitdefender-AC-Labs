#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

/*─── table1 @0x403000 ───────────────────────────────────────────────────────*/
static const char table1[16] = {
    'a','O','p','W','q','n','R','s',
    'E','h','X','y','C','v','J','t'
};
/*─── table2 @0x403010 ───────────────────────────────────────────────────────*/
static const uint8_t table2[16] = {
    0,0,0,0,  /* 'a','O','p','W' → nibble 0 */
    2,3,6,10, /* 'q','n','R','s' → 2,3,6,A */
    1,4,15,11,/* 'E','h','X','y' → 1,4,F,B */
    9,14,5,13 /* 'C','v','J','t' → 9,E,5,D */
};

/* rotate-left 32 bits */
static uint32_t rol32(uint32_t x, unsigned n) {
    return (x << n) | (x >> (32 - n));
}
/* compute_user_hash = sub_4010B5 */
static uint32_t compute_user_hash(const char* u) {
    uint32_t h = 0;
    if (!u[0]) return 0;
    for (const unsigned char* p = (const unsigned char*)u; *p; ++p) {
        h = rol32(h, 5);
        /* swap low two bytes (xchg al,ah) */
        uint32_t al = h & 0xFF;
        uint32_t ah = (h >> 8) & 0xFF;
        h = (h & ~0xFFFFu) | (al << 8) | ah;
        h ^= 0xC8FA7B6E;
        h += *p;
    }
    return h;
}

/* invert the “((acc<<4)|nib)^0xA” 8× to recover each nibble */
static void recover_nibbles(uint32_t final, uint8_t nib[8]) {
    uint32_t acc = final;
    for (int i = 7; i >= 0; --i) {
        uint32_t t = acc ^ 0xA;
        nib[i] = t & 0xF;
        acc = t >> 4;
    }
}

/* map each nibble back to the first matching char in table1 */
static void build_password(const uint8_t nib[8], char pass[9]) {
    for (int i = 0; i < 8; ++i) {
        char c = '?';
        for (int j = 0; j < 16; ++j) {
            if (table2[j] == nib[i]) {
                c = table1[j];
                break;
            }
        }
        pass[i] = c;
    }
    pass[8] = '\0';
}

int main(void) {
    char user[128];
    printf("Username: ");
    if (!fgets(user, sizeof(user), stdin)) return 1;
    user[strcspn(user, "\r\n")] = 0;

    /* validate exactly as the EXE does */
    if (user[0] == '\0') {
        fprintf(stderr, "Error: empty username\n");
        return 1;
    }
    for (size_t i = 0; i < strlen(user); ++i) {
        if (!isalpha((unsigned char)user[i])) {
            fprintf(stderr, "Error: invalid character in username\n");
            return 1;
        }
    }

    /* compute the 32-bit “user hash” */
    uint32_t h = compute_user_hash(user);

    /* invert the folding to get 8 nibbles */
    uint8_t nib[8];
    recover_nibbles(h, nib);

    /* map nibbles → characters */
    char pass[9];
    build_password(nib, pass);

    printf("Password: %s\n", pass);
    return 0;
}