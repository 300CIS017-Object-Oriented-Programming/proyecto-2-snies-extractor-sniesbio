#ifndef SNIES_CONTROLLER_H
#define SNIES_CONTROLLER_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <list>
#include "ProgramaAcademico.h"
#include "Consolidado.h"
#include "GestorCsv.h"

using namespace std;

class SNIESController
{
private:
    map<int, ProgramaAcademico *> programasAcademicos;
    GestorCsv gestorCsvObj;
    vector<string> etiquetasColumnas;
    string rutaProgramasCSV;
    string rutaAdmitidos;
    string rutaGraduados;
    string rutaInscritos;
    string rutaMatriculados;
    string rutaMatriculadosPrimerSemestre;
    string rutaOutput;

public:
    SNIESController() = default;
    SNIESController(const string &, const string &, const string &, const string &, const string &, const string &, const string &);  // Modificar para recibir referencias constantes
    ~SNIESController();
    void procesarDatosCsv(const string &, const string &);  // Modificar para recibir referencias constantes
    void calcularDatosExtra(bool);
    void buscarProgramas(bool, const string &, int);  // Modificar para recibir referencias constantes
};

#endif