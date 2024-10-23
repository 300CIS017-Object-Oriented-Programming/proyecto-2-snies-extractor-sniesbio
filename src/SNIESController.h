#ifndef SNIES_CONTROLLER_H
#define SNIES_CONTROLLER_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "ProgramaAcademico.h"
#include "Consolidado.h"
#include "GestorCsv.h"

class SNIESController
{
private:
    std::map<int, ProgramaAcademico *> programasAcademicos;
    GestorCsv gestorCsvObj;
    std::vector<std::string> etiquetasColumnas;
    std::string rutaProgramasCSV;
    std::string rutaAdmitidos;
    std::string rutaGraduados;
    std::string rutaInscritos;
    std::string rutaMatriculados;
    std::string rutaMatriculadosPrimerSemestre;
    std::string rutaOutput;

public:
    SNIESController() = default;
    SNIESController(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::string &);
    ~SNIESController();

    void procesarDatosCsv(const std::string &ano1, const std::string &ano2);
    std::vector<int> leerCodigosSnies();
    std::vector<std::vector<std::string>> leerDatosPrimera(std::string_view ano1, const std::vector<int>& codigosSnies);
    void procesarProgramaAcademico(const std::vector<std::vector<std::string>>& datos, int i);
    void calcularDatosExtra(bool);
    void buscarProgramas(bool, const std::string &, int);

    // Declaraciones de las nuevas funciones
    std::vector<std::vector<std::string>> generarMatrizEtiquetas1();
    std::vector<std::vector<std::string>> generarMatrizEtiquetas2();
    std::vector<std::vector<std::string>> generarMatrizEtiquetas3();
    void procesarDatos(const std::vector<std::vector<std::string>>& matrizEtiquetas1, int& sumaPrimerAno, int& sumaSegundoAno, bool flag); // Updated declaration
};

#endif