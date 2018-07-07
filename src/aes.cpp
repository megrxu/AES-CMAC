#include "aes.h"
#include "utils.h"

// Main Functions
unsigned char* aes_128_encrypt(unsigned char* in, unsigned char* out, unsigned char* key)
{
    unsigned char* w;
    w = (unsigned char*)malloc(16 * 11);
    KeyExpansion(key, w);
    Cipher(in, out, w);
    return out;
}

unsigned char* aes_128_decrypt(unsigned char* in, unsigned char* out, unsigned char* key)
{
    unsigned char* w;
    w = (unsigned char*)malloc(16 * 11);
    KeyExpansion(key, w);
    InvCipher(in, out, w);
    return out;
}

// The Cipher
void Cipher(unsigned char* in, unsigned char* out, unsigned char* w)
{
    unsigned char state[4][4];
    memcpy(state, in, 16);

    AddRoundKey(state, w);
    for (auto round = 0; round < 10; round++) {
        SubBytes(state);
        ShiftRows(state);
        if (round != 9)
            MixColumns(state);
        AddRoundKey(state, (unsigned char*)(w + (round + 1) * 16));
    }
    memcpy(out, state, 16);
}

void InvCipher(unsigned char* in, unsigned char* out, unsigned char* w)
{
    unsigned char state[4][4];
    memcpy(state, in, 16);

    AddRoundKey(state, w + (10 * 16));
    for (auto round = 9; round >= 0; round--) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, (unsigned char*)(w + round * 16));
        if (round)
            InvMixColumns(state);
    }
    memcpy(out, state, 16);
}

// Key Expansion
void KeyExpansion(unsigned char* key, unsigned char* w)
{
    unsigned char tmp[4];
    memcpy(w, key, 16);

    for (auto i = 4 * 4; i < 4 * 11 * 4; i += 4) {
        memcpy(tmp, w + i - 4, 4);
        if (i % 16 == 0) {
            SubWord(RotWord(tmp));
            for (auto j = 0; j < 4; j++) {
                tmp[j] ^= Rcon[i / 4 + j];
            }
        }
        for (auto j = 0; j < 4; j++)
            w[i + j] = w[i - 16 + j] ^ tmp[j];
    }
}

unsigned char* SubWord(unsigned char* word)
{
    for (auto i = 0; i < 4; i++) {
        word[i] = sbox[word[i]];
    }
    return word;
}

unsigned char* RotWord(unsigned char* word)
{
    unsigned char tmp[4];
    memcpy(tmp, word, 4);
    for (auto i = 0; i < 4; i++) {
        word[i] = tmp[(i + 1) % 4];
    }
    return word;
}

// Round Ops
void SubBytes(unsigned char state[4][4])
{
    for (auto row = 0; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            state[col][row] = sbox[state[col][row]];
        }
    }
}

void InvSubBytes(unsigned char state[4][4])
{
    for (auto row = 0; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            state[col][row] = invsbox[state[col][row]];
        }
    }
}

void ShiftRows(unsigned char state[4][4])
{
    unsigned char tmp[4];
    for (auto row = 1; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            tmp[col] = state[(row + col) % 4][row];
        }
        for (auto col = 0; col < 4; col++) {
            state[col][row] = tmp[col];
        }
    }
}

void InvShiftRows(unsigned char state[4][4])
{
    unsigned char tmp[4];
    for (auto row = 1; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            tmp[(row + col) % 4] = state[col][row];
        }
        for (auto col = 0; col < 4; col++) {
            state[col][row] = tmp[col];
        }
    }
}

void MixColumns(unsigned char state[4][4])
{
    unsigned char tmp[4];
    unsigned char matmul[][4] = {
        0x02, 0x03, 0x01, 0x01,
        0x01, 0x02, 0x03, 0x01,
        0x01, 0x01, 0x02, 0x03,
        0x03, 0x01, 0x01, 0x02
    };
    for (auto col = 0; col < 4; col++) {
        for (auto row = 0; row < 4; row++) {
            tmp[row] = state[col][row];
        }
        for (auto i = 0; i < 4; i++) {
            state[col][i] = 0x00;
            for (auto j = 0; j < 4; j++) {
                state[col][i] ^= mul(matmul[i][j], tmp[j]);
            }
        }
    }
}

void InvMixColumns(unsigned char state[4][4])
{
    unsigned char tmp[4];
    unsigned char matmul[][4] = {
        0x0e, 0x0b, 0x0d, 0x09,
        0x09, 0x0e, 0x0b, 0x0d,
        0x0d, 0x09, 0x0e, 0x0b,
        0x0b, 0x0d, 0x09, 0x0e
    };
    for (auto col = 0; col < 4; col++) {
        for (auto row = 0; row < 4; row++) {
            tmp[row] = state[col][row];
        }
        for (auto i = 0; i < 4; i++) {
            state[col][i] = 0x00;
            for (auto j = 0; j < 4; j++) {
                state[col][i] ^= mul(matmul[i][j], tmp[j]);
            }
        }
    }
}

unsigned char mul(unsigned char a, unsigned char b)
{
    unsigned char bw[4];
    unsigned char res = 0;
    bw[0] = b;
    for (auto i = 1; i < 4; i++) {
        bw[i] = bw[i - 1] << 1;
        if (bw[i - 1] & 0x80) {
            bw[i] ^= 0x1b;
        }
    }
    for (auto i = 0; i < 4; i++) {
        if (a >> i & 0x01) {
            res ^= bw[i];
        }
    }
    return res;
}

void AddRoundKey(unsigned char state[4][4], unsigned char* key)
{
    for (auto row = 0; row < 4; row++) {
        for (auto col = 0; col < 4; col++) {
            state[col][row] ^= key[col * 4 + row];
        }
    }
}