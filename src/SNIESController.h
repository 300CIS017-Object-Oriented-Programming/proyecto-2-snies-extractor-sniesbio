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

    void procesarNuevoPrograma(const std::vector<std::vector<std::string>>& programasAcademicosVector, size_t i, int codigoSnies);
    void actualizarConsolidadosExistentes(ProgramaAcademico* programaAcademico, const std::vector<std::vector<std::string>>& programasAcademicosVector, size_t i) const;

public:
    SNIESController() = default;
    SNIESController(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::string &);
    ~SNIESController();

    std::map<std::string, int, std::less<>> mapearColumnas(const std::string& encabezado, const std::string& delimitador) const;

    void procesarDatosCsv(const std::string &ano1, const std::string &ano2);
    std::vector<int> leerCodigosSnies() const;
    std::vector<std::vector<std::string>> leerDatosPrimera(std::string_view ano1, const std::vector<int>& codigosSnies) const;
    void calcularDatosExtra(bool) const;
    void buscarProgramas(bool flag, std::string_view palabraClave, int idComparacion) const;

    std::vector<std::vector<std::string>> generarMatrizEtiquetas1() const;
    std::vector<std::vector<std::string>> generarMatrizEtiquetas2() const;
    std::vector<std::vector<std::string>> generarMatrizEtiquetas3() const;
    void procesarDatos(int& sumaPrimerAno, int& sumaSegundoAno, bool flag) const;
};

#endif