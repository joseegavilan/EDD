#include <iostream>
#include <fstream>
#include <string>                               // soporte para manupulacion de cadenas
#include <vector>                               // soporte para manupulacion de vectores
#include <algorithm>                            // soporte para la función transform
#include <iomanip>                              // soporte para impresion precisa de decimales
#include <sstream>

const int anioSolicitado = 2022;                // se define constante para el año solicitado

using namespace std;

// AREA DE DECLARACION DE VARIABLE FUNCIONES ARREGLOS Y VECTORES
struct dato {                                   // Definición de la estructura/registro
    int anio = 0;
    string ciudad = "";
    string mes = "";
    int temperatura = 0;
    int precipitacion = 0;
};
dato nuevoDato;

vector<dato> datos;                             // vector dinámico de tipo dato
string nombreArchivo = "base.csv";              // nombre del archivo con datos
string linea;                                   // variable para almacenar la linea leida de archivo
int contadorLinea = 0;                          // contador de lineas leidas
int cantidadAguaCaida = 0;                      // totalizador de agua caida a nivel nacional
int temperaturaAlta = 0;                        // variable que conserva la temperatura mas alta
int temperaturaBaja = 1000;                     // variable que conserva la temperatura mas baja
string ciudadAlta = "";                         // variable que conserva el nombre de la ciudad con la temperatura mas alta
string ciudadBaja = "";                         // variable que conserva el nombre de la ciudad con la temperatura mas baja
//int trimestre;

// arreglo para almacenamiento y clasificacion de meses en trimestres
string mesesTrimestre[3][4] = { {"enero","febrero","marzo","abril"},
                                {"mayo","junio","julio","agosto"},
                                {"septiembre","octubre","noviembre","diciembre"} };
int sumadorTrimestral[3] = { 0,0,0 };           // arreglo sumador  de elementos enctrados pos trimestre
int contadorTrimestral[3] = { 0,0,0 };          // arreglo contador de elementos encontrados por trimestre

int trimestreEnCurso(string mes) {
    transform(mes.begin(), mes.end(), mes.begin(), ::tolower);      // convierte mes minusculas 
    for (int i = 0; i < 3; ++i) {                                   // reccorido de filas de las matriz de meses
        for (int j = 0; j < 4; ++j) {                               // recorrido de la columna en la fila de la matriz de meses
            if (mesesTrimestre[i][j] == mes) {                      // si hay coincidencia, retornamos la fila que indica el trimistre
                return i;
            }
        }
    }
}

float retornaPromedio(float a, float b) {
    float c = 0;
    c = static_cast<float>(a / b);
    return c;
}

int main() {

    setlocale(LC_CTYPE, "Spanish");             //Cambia a la localidad actual
    ifstream archivo(nombreArchivo.c_str());    // abre el archivo para lectura

    if (archivo) {                              // pregunta si el archivo se abrió correctamente

        // rellenar vector dinamico con datos rescatados de archivo .csv
        while (getline(archivo, linea)) {

            // se definen variables temporales.
            string panio = "";
            string pciudad = "";
            string pmes = "";
            string ptemperatura = "";
            string pprecipitacion = "";

            // se rescata linea del buffer en memória y la deja en linea.
            stringstream input_stringstream(linea);

            // toma cada parte y la almacena en las variables temporales.
            getline(input_stringstream, panio, ';');
            getline(input_stringstream, pciudad, ';');
            getline(input_stringstream, pmes, ';');
            getline(input_stringstream, ptemperatura, ';');
            getline(input_stringstream, pprecipitacion, ';');

            contadorLinea++;

            // ingresa datos al nuevo vector datos
            if (contadorLinea > 1) {                        // saltar titulos
                nuevoDato.anio = stoi(panio);
                nuevoDato.ciudad = pciudad;
                nuevoDato.mes = pmes;
                nuevoDato.temperatura = stoi(ptemperatura);
                nuevoDato.precipitacion = stoi(pprecipitacion);
                datos.push_back(nuevoDato);
            }
        }

        // Generar un ciclo para recforrer vector dinamico
        for (size_t i = 0; i < datos.size(); i++) {

            // actualizamos acumulador de agua caida
            cantidadAguaCaida = cantidadAguaCaida + datos[i].precipitacion;

            //actualizamos datos de temperatura mas alta
            if (datos[i].temperatura > temperaturaAlta) {
                temperaturaAlta = datos[i].temperatura;
                ciudadAlta = datos[i].ciudad;
            }
            //actualizamos datos de temperatura mas baja
            if (datos[i].temperatura < temperaturaBaja) {
                temperaturaBaja = datos[i].temperatura;
                ciudadBaja = datos[i].ciudad;
            }

            if (datos[i].anio == anioSolicitado) {          // verificamos que la contabilizacion sea para el año solicitado (2022) 
                int trimestre = trimestreEnCurso(datos[i].mes);
                sumadorTrimestral[trimestre] = sumadorTrimestral[trimestre] + datos[i].temperatura;
                contadorTrimestral[trimestre]++;
            }
        }

        cout << "<< RESPUESTAS >>" << endl;
        cout << " " << endl;
        cout << "La cantidad total de agua caida en chile durante el " << anioSolicitado;
        cout << " fue de " << cantidadAguaCaida << " mm. " << endl;
        cout << " " << endl;
        cout << "Temperatura promedio por trimestre : " << endl;
        cout << "   1er trimestre -> " << fixed << setprecision(2) << retornaPromedio(sumadorTrimestral[0], contadorTrimestral[0]) << endl;
        cout << "   2do trimestre -> " << fixed << setprecision(2) << retornaPromedio(sumadorTrimestral[1], contadorTrimestral[1]) << endl;
        cout << "   3er trimestre -> " << fixed << setprecision(2) << retornaPromedio(sumadorTrimestral[2], contadorTrimestral[2]) << endl;
        cout << " " << endl;
        cout << "La temperatura mas alta durante el " << anioSolicitado << " fue de " << temperaturaAlta << " C, registrada en " << ciudadAlta << endl;
        cout << " " << endl;
        cout << "La temperatura mas Baja durante el " << anioSolicitado << " fue de " << temperaturaBaja << " C, registrada en " << ciudadBaja << endl;
        datos.resize(0);    // limpia el vector dinamico.
    }
    else {
        cout << " " << endl;
        cout << "ERROR -> Problemas con el archivo de datos.!!" << endl;
        cout << "Posibles errores: " << endl;
        cout << "   - El archivo no existe. " << endl;
        cout << "   - El archivo no se encuentra en la carapeta del ejecutable. " << endl;
    }
    cout << " " << endl;
    system("PAUSE()");          // genera pausa.
    return 0;                   // termina prg sin problemas!!
}