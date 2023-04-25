#ifndef ASTROBWT_H
#define ASTROBWT_H

#include <algorithm>
#include <cstring>
#include <cstddef>
#include <stdio.h>
#include <tchar.h>
#include <cstring>

using namespace std;

class AstroBWT {
public:
    static void encode(const unsigned char* input, unsigned char* output, int size) {
        int* indices = new int[size];
        for (int i = 0; i < size; i++) {
            indices[i] = i;
        }

        std::sort(indices, indices + size, [&](int a, int b) {
            return std::memcmp(input + static_cast<long long>(a), input + static_cast<long long>(b), size - std::max(a, b)) < 0;
            });

        for (int i = 0; i < size; i++) {
            output[i] = input[(indices[i] + size - 1) % size];
        }
        delete[] indices;
    }

    static void decode(const unsigned char* input, unsigned char* output, int size, int primary_index) {
        int counts[256] = {};
        for (int i = 0; i < size; i++) {
            counts[input[i]]++;
        }

        int* indices = new int[size];
        int acc = 0;
        for (int i = 0; i < 256; i++) {
            int count = counts[i];
            counts[i] = acc;
            acc += count;
        }
        for (int i = 0; i < size; i++) {
            indices[counts[input[i]]++] = i;
        }

        int i = primary_index;
        for (int j = 0; j < size; j++) {
            output[j] = input[i];
            i = indices[i];
        }
        delete[] indices;
    }
};

#endif // ASTROBWT_H
