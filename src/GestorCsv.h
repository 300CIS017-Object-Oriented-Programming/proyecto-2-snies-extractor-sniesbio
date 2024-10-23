#ifndef GESTORCSV_H
#define GESTORCSV_H

#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "ProgramaAcademico.h"
#include "Consolidado.h"

class GestorCsv
{
private:
    std::string delimitador = ";";

public:
    GestorCsv() = default;

    // Función para establecer el delimitador dinámicamente
    void setDelimitador(std::string_view nuevoDelimitador);

    // Funciones para leer archivos
    std::vector<int> leerProgramasCsv(const std::string &ruta) const;
    std::vector<std::vector<std::string>> leerArchivoPrimera(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;
    std::vector<std::vector<std::string>> leerArchivoSegunda(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;
    std::vector<std::vector<std::string>> leerArchivo(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;

    // Función para procesar una fila
    void procesarFila(const std::string &fila, std::vector<std::string> &vectorFila) const;

    // Función para leer tres filas asociadas
    void leerTresFilasAsociadas(std::ifstream &archivo, std::vector<std::string> &vectorFila, std::vector<std::vector<std::string>> &matrizResultado) const;

    // Funciones para crear archivos de salida
    bool crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const;
    bool crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const;
    bool crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const;
};

#endif // GESTORCSV_H