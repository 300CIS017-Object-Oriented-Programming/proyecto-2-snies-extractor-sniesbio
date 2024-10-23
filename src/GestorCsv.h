#ifndef GESTOR_CSV_H
#define GESTOR_CSV_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <list>
#include "ProgramaAcademico.h"
#include "Consolidado.h"

class GestorCsv
{
public:
    GestorCsv() = default;

    // LeerProgramasCSV : Lee los códigos SNIES de un archivo CSV
    std::vector<int> leerProgramasCsv(const std::string &ruta) const;
    // LeerArchivoPrimera : Lee el archivo del primer conjunto de datos (admitidos)
    std::vector<std::vector<std::string>> leerArchivoPrimera(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;
    // LeerArchivoSegunda : Lee el archivo del segundo conjunto de datos (matriculados)
    std::vector<std::vector<std::string>> leerArchivoSegunda(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;
    // LeerArchivoTercera : Lee el archivo del tercer conjunto de datos (graduados)
    std::vector<std::vector<std::string>> leerArchivo(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies, int columnaCodigoSnies) const;

    // CrearArchivo : Crea un archivo CSV con los datos de los programas académicos
    bool crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const;
    // CrearArchivoConsolidado : Crea un archivo CSV con los datos consolidados de los estudiantes
    bool crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const;
    // CrearArchivoExtra : Crea un archivo CSV con datos adicionales
    bool crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const;
};

#endif