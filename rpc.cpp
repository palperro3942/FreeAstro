#include <iostream>
#include <jsonrpccpp/client.h>

using namespace std;
using namespace jsonrpc;

int main() {
    HttpClient client("http://140.84.166.52:10100"); // dirección del daemon JSON RPC de Testeos
    Client c(client);

    // Llamada RPC
    Json::Value input = c.CallMethod("nombre_del_metodo_json_rpc", "parametro_1", "parametro_2");

    // Procesamiento de los datos de entrada
    int valor_entero = input["entero"].asInt();
    string valor_cadena = input["cadena"].asString();

    // Imprimir los resultados
    cout << "El valor entero es: " << valor_entero << endl;
    cout << "El valor de cadena es: " << valor_cadena << endl;

    return 0;
}
