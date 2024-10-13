#ifndef GESTOR_CSV_H
#define GESTOR_CSV_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include "ProgramaAcademico.h"
#include "Consolidado.h"

// Recomendación Linter: Se debe evitar el uso de using namespace en archivos de cabecera
using namespace std;

class GestorCsv
{
public:
    GestorCsv() = default;
    vector<int> leerProgramasCsv(string &ruta)const;
    vector<vector<string>> leerArchivoPrimera(string &rutaBase, string &ano, vector<int> &codigosSnies) const;
    vector<vector<string>> leerArchivoSegunda(const string &rutaBase, const string &ano, const vector<int> &codigosSnies) const;
    vector<vector<string>> leerArchivo(string &rutaBase, string &ano, vector<int> &codigosSnies, int colmunaCodigoSnies) const;
    bool crearArchivo(string &ruta, map<int, ProgramaAcademico *> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas) const;
    bool crearArchivoBuscados(string &ruta, list<ProgramaAcademico *> &programasBuscados, vector<string> etiquetasColumnas) const;
    bool crearArchivoExtra(string &ruta, const vector<vector<string>> &datosAImprimir) const;
    void agregarFilasAdicionales(ifstream &archivo, vector<vector<string>> &matrizResultado, int numFilas, int numColumnas) const;

private:
    // Declaración de las funciones auxiliares
    vector<string> leerFila(ifstream &archivo, int numColumnas) const;
    bool verificarPrograma(const vector<string> &vectorFila, const vector<int> &codigosSnies) const;
    bool verificarPrograma(const vector<string> &vectorFila, const vector<int> &codigosSnies, int columnaCodigoSnies) const;
    void leerFilasRestantes(ifstream &archivo, vector<vector<string>> &matrizResultado, int numFilas) const;
    void imprimirFila(ofstream &archivo, const vector<string> &fila) const; // Nueva declaración
};

#endif // GESTOR_CSV_H