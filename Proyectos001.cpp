//segunda actualizacion
#include <iostream>
#include <fstream>
#include <wchar.h>                              // soporte para amplios tipos de caracteres, windows
#include <Windows.h>
#include <sstream>
#include <climits>

using namespace std;

struct dato {                                   // Definición de la estructura/registro
    int anio = 0;
    string ciudad = "";
    string mes = "";
    int temperatura = 0;
    int precipitacion = 0;
};
vector<dato> datos;                             //Crear un vector dinámico de tipo dato
string nombreArchivo = "base.csv";              //Crear variable con nombre de archivo para leer
string linea;                                   //Crear variable para almacenar la linea leida de archivo
dato nuevoDato;
int contadorLinea = 0;

//      Responder:
//          - Cantidad de agua caída en Chile en mm.
//          - Temperatura(°C) promedio por cada trimestre(agrupación de 4 meses) en Chile.
//          - Señalar que ciudad tuvo la temperatura más alta y baja en el 2022.

int cantidadAguaCaida = 0;
int temperaturaPromedio = 0;
int temperaturaAlta = 0;
string ciudadAlta = "";
int temperaturaBaja = 1000;
string ciudadBaja = "";
int anioSolicitado = 2022;
string ciudadActiva = "x";
int contadorMesesCiudad = 0;
string mesesTrimestre[3][4] = { {"enero","febrero","marzo","abril"},{"mayo","junio","julio","Agosto"},{"septiembre","octubre","noviembre","diciembre"} };
int sumadorTrimestral[3] = { 0,0,0 };
int contadorTrimestral[3] = { 0,0,0 };

int trimestreEnCurso(string mes);
float retornaPromedio(float a, float b);

int main() {

    ifstream archivo(nombreArchivo.c_str());    // abre el archivo para lectura

    if (archivo) {                              // pregunta si el archivo se abrió correctamente
        cout << " " << endl;
        while (getline(archivo, linea)) {
            //cout << linea << endl;            // Lo vamos imprimiendo
            // se definen variables temporales.
            string panio = "";
            string pciudad = "";
            string pmes = "";
            string ptemperatura = "";
            string pprecipitacion = "";

            // se rescata linea del buffer en memória y la deja en linea.
            stringstream input_stringstream(linea);

            // toma cada parte y la almacena en las variables ptemporales.
            getline(input_stringstream, panio, ';');
            getline(input_stringstream, pciudad, ';');
            getline(input_stringstream, pmes, ';');
            getline(input_stringstream, ptemperatura, ';');
            getline(input_stringstream, pprecipitacion, ';');

            contadorLinea++;

            if (contadorLinea > 1) {

                // ingresa datos al nuevo vector vector.
                nuevoDato.anio = stoi(panio);
                nuevoDato.ciudad = pciudad;
                nuevoDato.mes = pmes;
                nuevoDato.temperatura = stoi(ptemperatura);
                nuevoDato.precipitacion = stoi(pprecipitacion);

                // agrega el nuevo dato al vector dinamico(datos)
                datos.push_back(nuevoDato);

            }
        }

        // Generar un ciclo para listar el vector
        for (size_t i = 0; i < datos.size(); i++) {
            if (datos[i].temperatura > temperaturaAlta) {
                temperaturaAlta = datos[i].temperatura;
                ciudadAlta = datos[i].ciudad;
            }
            //actualizamos datos de temperatura baja
            if (datos[i].temperatura < temperaturaBaja) {
                temperaturaBaja = datos[i].temperatura;
                ciudadBaja = datos[i].ciudad;
            }
            if (ciudadActiva != datos[i].ciudad) {
                ciudadActiva = datos[i].ciudad;            // dejamos la ciudadActiva como nueva ciudad 
                contadorMesesCiudad = 0;                    // inicilizamos el contador de meses
            }

            if (datos[i].anio == anioSolicitado) {          // verificamos que contabilizacion sea año solicitado (2022) 
                if (ciudadActiva != datos[i].ciudad) {      // preguntamos si seguimos con la ciudad activa
                    ciudadActiva = datos[i].ciudad;            // dejamos la ciudadActiva como nueva ciudad 
                    contadorMesesCiudad = 1;                    // inicilizamos el contador de meses
                }
                string mes = datos[i].mes;
                int opcion = trimestreEnCurso(mes);


        datos.resize(0);            // limpia el vector dinamico.


    }
    else {

        // EPA!! error
        cout << " " << endl;
    }

    datos.resize(0);            // limpia el vector dinamico.
        system("PAUSE()");          // genera pausa.

    }
    return 0;                   // termina prg sin problemas!!

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int trimestreEnCurso(string mes) {
    // Convertir el mes a minúsculas
    transform(mes.begin(), mes.end(), mes.begin(), ::tolower);
    // Bucle a través de las filas de la matriz
    for (int i = 0; i < 3; ++i) {
        // Bucle a través de las columnas de la matriz
        for (int j = 0; j < 4; ++j) {
            // Si el valor actual coincide con el mes dado, devuelve el número de fila
            if (mesesTrimestre[i][j] == mes) {
                return i;
            }
        }
    }
}

float retornaPromedio(float a, float b) {
    float c = 0;
    c = static_cast<float>(a / b);
    return c;

