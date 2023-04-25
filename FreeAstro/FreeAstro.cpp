#include <sodium.h>
#include <iostream>
#include <cstring>
#include <sha3.h>
#include "astrobwt.h" // Archivo de cabecera de AstroBWT

typedef unsigned char byte;
const int expansion_size = 69371;
int expansion_size_2 = 0;
using namespace std;

int main()
{
    // Paso 1: Calcular SHA3-256 de los datos de entrada
    string input_data = "Datos de entrada"; // reemplazar con los datos reales
    CryptoPP::SHA3_256 sha3;
    byte hash[CryptoPP::SHA3_256::DIGESTSIZE];
    sha3.CalculateDigest(hash, (byte*)input_data.data(), input_data.size());

    // Paso 2: Expandir los datos usando Salsa20
    //int expansion_size = 69371;
    byte expansion_key[crypto_stream_xsalsa20_KEYBYTES];
    byte expansion_nonce[crypto_stream_xsalsa20_NONCEBYTES];
    // Inicializar clave y nonce aleatorios utilizando libsodium
    randombytes_buf(expansion_key, crypto_stream_xsalsa20_KEYBYTES);
    randombytes_buf(expansion_nonce, crypto_stream_xsalsa20_NONCEBYTES);
    // Expandir los datos utilizando Salsa20
    char buffer[expansion_size];
    byte expanded_data[expansion_size];
    crypto_stream_xsalsa20_xor(expanded_data, expanded_data, expansion_size, expansion_nonce, expansion_key);

    // Paso 3: Calcular BWT de los datos expandidos
    byte bwt_data[expansion_size];
    AstroBWT::encode(expanded_data, bwt_data, expansion_size);

    // Paso 4: Calcular SHA3-256 de los datos BWT
    CryptoPP::SHA3_256 sha3_2;
    byte hash_2[CryptoPP::SHA3_256::DIGESTSIZE];
    sha3_2.CalculateDigest(hash_2, bwt_data, expansion_size);

    // Paso 5: Expandir los datos utilizando Salsa20 con la clave generada en el paso 4
    int expansion_size_2 = expansion_size + hash_2[0]; // agregamos un número aleatorio basado en el hash SHA3-256 del paso 4
    byte expansion_key_2[crypto_stream_xsalsa20_KEYBYTES];
    memcpy(expansion_key_2, hash_2, crypto_stream_xsalsa20_KEYBYTES); // la clave es el hash SHA3-256
    byte expansion_nonce_2[crypto_stream_xsalsa20_NONCEBYTES];
    // Inicializar nonce aleatorio utilizando libsodium
    randombytes_buf(expansion_nonce_2, crypto_stream_xsalsa20_NONCEBYTES);
    // Expandir los datos utilizando Salsa20
    byte* expanded_data_2 = new byte[expansion_size_2];
    crypto_stream_xsalsa20_xor(expanded_data_2, expanded_data_2, expansion_size_2, expansion_nonce_2, expansion_key_2);

    // Paso 6: Calcular BWT de los datos expandidos del paso 5
    byte* bwt_data_2 = new byte[expansion_size_2];
    AstroBWT::encode(expanded_data_2, bwt_data_2, expansion_size_2);
    delete[] expanded_data_2;
    // Paso 7: Calcular SHA3-256 de los datos BWT del paso 6
    CryptoPP::SHA3_256 sha3_3;
    byte hash_3[CryptoPP::SHA3_256::DIGESTSIZE];
    sha3_3.CalculateDigest(hash_3, bwt_data_2, expansion_size_2);
    delete[] bwt_data_2;

    // Imprimir resultados
    cout << "Hash SHA3-256 de los datos de entrada: ";
    for (int i = 0; i < CryptoPP::SHA3_256::DIGESTSIZE; i++)
    {
        cout << hex << (int)hash[i];
    }
    cout << endl;

    cout << "Datos expandidos con Salsa20: ";
    for (int i = 0; i < expansion_size; i++)
    {
        cout << hex << (int)expanded_data[i];
    }
    cout << endl;

    cout << "Datos BWT de la expansión: ";
    for (int i = 0; i < expansion_size; i++)
    {
        cout << hex << (int)bwt_data[i];
    }
    cout << endl;

    cout << "Hash SHA3-256 de los datos BWT: ";
    for (int i = 0; i < CryptoPP::SHA3_256::DIGESTSIZE; i++)
    {
        cout << hex << (int)hash_2[i];
    }
    cout << endl;

    cout << "Datos expandidos con Salsa20 y número aleatorio: ";
    for (int i = 0; i < expansion_size_2; i++)
    {
        cout << hex << (int)expanded_data_2[i];
    }
    cout << endl;

    cout << "Datos BWT de la expansión con número aleatorio: ";
    for (int i = 0; i < expansion_size_2; i++)
    {
        cout << hex << (int)bwt_data_2[i];
    }
    cout << endl;

    cout << "Hash SHA3-256 de los datos BWT con número aleatorio: ";
    for (int i = 0; i < CryptoPP::SHA3_256::DIGESTSIZE; i++)
    {
        cout << hex << (int)hash_3[i];
    }
    cout << endl;

    return 0;
}
