#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
//#include <locale.h>                           //soporte para distintos tipos de formatos, linux
#include <wchar.h>                              // soporte para amplios tipos de caracteres, windows

#include <Windows.h>
#include <sstream>
#include <climits>

using namespace std;

// Definición de variables
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

int main() {

    setlocale(LC_ALL, "");                      //Cambia a la localidad actual
    setlocale(LC_CTYPE, "Spanish");
    ifstream archivo(nombreArchivo.c_str());    // abre el archivo para lectura
    if (archivo) {                              // pregunta si el archivo se abrió correctamente
        cout << "<< Archivo abierto con exito. >>" << endl;
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
            /*cout << i+1 << "\t";
            cout << datos[i].anio << "\t";
            cout << datos[i].ciudad << "\t\t";
            cout << datos[i].mes << "\t\t\t";
            cout << datos[i].temperatura << "\t";
            cout << datos[i].precipitacion < < "\t";
            cout << endl;*/

            cantidadAguaCaida = cantidadAguaCaida + datos[i].temperatura;
            if (datos[i].temperatura > temperaturaAlta) {
                temperaturaAlta = datos[i].temperatura;
                ciudadAlta = datos[i].ciudad;
            }
            if (datos[i].temperatura < temperaturaBaja) {
                temperaturaBaja = datos[i].temperatura;
                ciudadBaja = datos[i].ciudad;
            }
        }


        SetConsoleOutputCP(CP_UTF8);
        setvbuf(stdout, nullptr, _IONBF, 0);


        cout << "Cantidad de agua caida en chile " << cantidadAguaCaida << endl;
        cout << "La temperatura mas alta fue de " << temperaturaAlta << "°, registrada en " << ciudadAlta << endl;
        cout << "La temperatura mas Baja fue de " << temperaturaBaja << "°, registrada en " << ciudadBaja << endl;

    }
    else {
        // EPA!! error
        cout << "<< Archivo no existe. >>" << endl;
        cout << " " << endl;
    }

    datos.resize(0);            // limpia el vector dinamico.
    system("PAUSE()");          // genera pausa.
    return 0;                   // termina prg sin problemas!!
}