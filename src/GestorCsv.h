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

    std::vector<int> leerProgramasCsv(const std::string &ruta) const;
    std::vector<std::vector<std::string>> leerArchivoPrimera(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;
    std::vector<std::vector<std::string>> leerArchivoSegunda(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;
    std::vector<std::vector<std::string>> leerArchivo(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies, int columnaCodigoSnies) const;

    bool crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const;
    bool crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const;
    bool crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const;
};

#endif