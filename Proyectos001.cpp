#include <iostream>         // Entrada y salida estándar
#include <fstream>          // Entrada y salida de archivos
#include <string>           // Soporte para manipulación de cadenas
#include <vector>           // Soporte para manipulación de vectores
#include <algorithm>        // Soporte para la función transform
#include <iomanip>          // Soporte para impresión precisa de decimales
#include <sstream>          // Soporte para flujos de cadena de entrada y salida

const int ANIO_TRABAJO = 2022;

using namespace std;

// ÁREA DE DECLARACIÓN DE VARIABLES, FUNCIONES, ARREGLOS Y VECTORES
struct dato {               // Definición de la estructura/registro
    int anio = 0;
    string ciudad = "";
    string mes = "";
    int temperatura = 0;
    int precipitacion = 0;
};
vector<dato> datos;                         // vector dinámico de tipo dato
string nombreArchivo = "base.csv";          // variable con nombre de archivo para leer
string linea;                               // almacena la línea leída de archivo
dato nuevoDato;
int contadorLinea = 0;
int cantidadAguaCaida = 0;
int temperaturaPromedio = 0;
int temperaturaAlta = 0;
string ciudadAlta = "";
int temperaturaBaja = 1000;
string ciudadBaja = "";
string ciudadActiva = "x";
int contadorMesesCiudad = 0;
string mesesTrimestre[3][4] = { {"enero","febrero","marzo","abril"},
                                {"mayo","junio","julio","Agosto"},
                                {"septiembre","octubre","noviembre","diciembre"} };
int sumadorTrimestral[3] = { 0,0,0 };
int contadorTrimestral[3] = { 0,0,0 };

// Prototipos de funciones
int retornaFilaTrimestre(string mes);
float retornaPromedio(float a, float b);
void impresionDatos();
bool existeAnio(int anio);

int main() {
    //setlocale(LC_CTYPE, "Spanish"); // Cambia a la localidad actual a español
    ifstream archivo(nombreArchivo.c_str());  // Abre el archivo para lectura

    if (archivo) {  // Verifica si el archivo se abrió correctamente
        while (getline(archivo, linea)) {
            if (contadorLinea > 0) { // Ignora la primera línea (encabezado)
                stringstream ss(linea);
                dato nuevoDato;
                string campo;
                getline(ss, campo, ';'); nuevoDato.anio = stoi(campo);
                getline(ss, campo, ';'); nuevoDato.ciudad = campo;
                getline(ss, campo, ';'); nuevoDato.mes = campo;
                getline(ss, campo, ';'); nuevoDato.temperatura = stoi(campo);
                getline(ss, campo, ';'); nuevoDato.precipitacion = stoi(campo);
                datos.push_back(nuevoDato); // Agrega el nuevo dato al vector 'datos'
            }
            contadorLinea++;
         
        }

        archivo.close(); // Cierra el archivo

        if (existeAnio(ANIO_TRABAJO)) {
            impresionDatos();
        }
        else {
            // EPA!!
            cout << " " << endl;
            cout << "ADVERTENCIA -> Problemas con el a\xA4o !!" << endl;
            cout << "Posibles errores: " << endl;
            cout << "   - No hay datos para ese a\xA4o " << ANIO_TRABAJO << endl;
            cout << " " << endl;
        }
    }
    else {
        // EPA!! 
        cout << " " << endl;
        cout << "ERROR -> Problemas con el archivo de datos.!!" << endl;
        cout << "Posibles errores: " << endl;
        cout << "   - El archivo no existe. " << endl;
        cout << "   - El archivo no se encuentra en la carpeta del ejecutable. " << endl;
    }

    cout << " " << endl;
    datos.resize(0);    // Limpia el vector dinámico.
    system("PAUSE()");  // Genera pausa.    
    return 0;   // Termina el programa sin problemas
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void impresionDatos()
{
    // Generar un ciclo para listar el vector
    for (size_t i = 0; i < datos.size(); i++) {

        cantidadAguaCaida += datos[i].precipitacion;    // actualizamos acumulador de agua caída

        if (datos[i].temperatura > temperaturaAlta) {   // Dejamos la temperatura mas alta en la variable 
            temperaturaAlta = datos[i].temperatura;
            ciudadAlta = datos[i].ciudad;
        }

        if (datos[i].temperatura < temperaturaBaja) {   // Dejamos la temperatura mas baja en la variable
            temperaturaBaja = datos[i].temperatura;
            ciudadBaja = datos[i].ciudad;
        }

        if (datos[i].anio == ANIO_TRABAJO) {          // Verificamos que contabilización sea año solicitado (2022) 

            if (ciudadActiva != datos[i].ciudad) {      // Si la ciudad es diferente actualizamos la ciudad
                ciudadActiva = datos[i].ciudad;
                contadorMesesCiudad = 1;
            }
            string mes = datos[i].mes;

            int opcion = retornaFilaTrimestre(mes);

            switch (opcion)                             // donde 'opcion' es la variable a comparar
            {
            case 0:
                sumadorTrimestral[0] += datos[i].temperatura;
                contadorTrimestral[0]++;
                break;
            case 1:
                sumadorTrimestral[1] += datos[i].temperatura;
                contadorTrimestral[1]++;
                break;
            case 2:
                sumadorTrimestral[2] += datos[i].temperatura;
                contadorTrimestral[2]++;
                break;
            }
        }
    }

    cout << "<< RESPUESTAS >>" << endl;
    cout << " " << endl;
    cout << "La cantidad total de agua ca" << "\xA1" << "da en Chile durante el " << ANIO_TRABAJO;
    cout << " fue de " << cantidadAguaCaida << " mm. " << endl;
    cout << " " << endl;
    cout << "Temperatura promedio por trimestre : " << endl;
    cout << "   1er trimestre -> " << fixed << setprecision(2) << retornaPromedio(sumadorTrimestral[0], contadorTrimestral[0]) << endl;
    cout << "   2do trimestre -> " << fixed << setprecision(2) << retornaPromedio(sumadorTrimestral[1], contadorTrimestral[1]) << endl;
    cout << "   3er trimestre -> " << fixed << setprecision(2) << retornaPromedio(sumadorTrimestral[2], contadorTrimestral[2]) << endl;
    cout << " " << endl;
    cout << "La temperatura m" << "\xA0" << "s alta durante el " << ANIO_TRABAJO << " fue de " << temperaturaAlta << "\xF8, registrada en " << ciudadAlta << endl;
    cout << " " << endl;
    cout << "La temperatura m" << "\xA0" << "s baja durante el " << ANIO_TRABAJO << " fue de " << temperaturaBaja << "\xF8, registrada en " << ciudadBaja << endl;
    cout << " " << endl;

}

bool existeAnio(int anio) {
    for (const auto& d : datos) {
        if (d.anio == anio) {
            return true;
        }
    }
    return false;
}

float retornaPromedio(float a, float b) {
    float c = 0;
    c = static_cast<float>(a / b);
    return c;
}

int retornaFilaTrimestre(string mes) {
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
