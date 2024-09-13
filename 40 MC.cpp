#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000

const float english_freq[ALPHABET_SIZE] = {
    0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070,
    0.002, 0.008, 0.040, 0.024, 0.067, 0.075, 0.019, 0.001, 0.060,
    0.063, 0.091, 0.028, 0.010, 0.023, 0.001, 0.020, 0.001
};

void calculate_frequency(const char *text, float *freq) {
    int count[ALPHABET_SIZE] = {0};
    int total = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            count[text[i] - 'A']++;
            total++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            count[text[i] - 'a']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (float)count[i] / total;
    }
}

void sort_indices(const float *freq, int *indices) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        indices[i] = i;
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[indices[i]] < freq[indices[j]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
}

void generate_possible_plaintexts(const char *ciphertext, int *sorted_indices, char *plaintext, int num_plaintexts) {
    int alphabet[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        alphabet[sorted_indices[i]] = i;
    }

    for (int n = 0; n < num_plaintexts; n++) {
        for (int i = 0; ciphertext[i] != '\0'; i++) {
            if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                plaintext[i] = alphabet[ciphertext[i] - 'A'] + 'A';
            } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                plaintext[i] = alphabet[ciphertext[i] - 'a'] + 'a';
            } else {
                plaintext[i] = ciphertext[i];
            }
        }
        plaintext[strlen(ciphertext)] = '\0';

        printf("Possible plaintext %d: %s\n", n + 1, plaintext);

        int temp = alphabet[ALPHABET_SIZE - 1];
        for (int i = ALPHABET_SIZE - 1; i > 0; i--) {
            alphabet[i] = alphabet[i - 1];
        }
        alphabet[0] = temp;
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    float freq[ALPHABET_SIZE];
    int sorted_indices[ALPHABET_SIZE];
    int num_plaintexts;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    if (ciphertext[strlen(ciphertext) - 1] == '\n') {
        ciphertext[strlen(ciphertext) - 1] = '\0';
    }

    printf("Enter the number of top possible plaintexts to generate: ");
    scanf("%d", &num_plaintexts);
    if (num_plaintexts > ALPHABET_SIZE) {
        printf("The number of plaintexts to generate cannot exceed %d.\n", ALPHABET_SIZE);
        return 1;
    }

    calculate_frequency(ciphertext, freq);

    sort_indices(freq, sorted_indices);
    char plaintext[MAX_TEXT_LENGTH];
    generate_possible_plaintexts(ciphertext, sorted_indices, plaintext, num_plaintexts);

    return 0;
}

