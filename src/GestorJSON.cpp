#include "GestorJSON.h"
#include <fstream>
#include <iostream>
#include "json.hpp"  // Usar librería para manejar JSON

using json = nlohmann::json;

// Crear archivo JSON estándar
bool GestorJSON::crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const {
    std::ofstream archivoResultados(ruta + "resultados.json");
    if (!archivoResultados.is_open()) {
        manejarErrores("No se pudo abrir el archivo JSON para escribir: " + ruta);
        return false;
    }

    json resultadoJson;
    for (const auto &[codigo, programa] : mapaProgramas) {
        json programaJson;
        programaJson[etiquetasColumnas[0]] = programa->getCodigoDeLaInstitucion();
        programaJson[etiquetasColumnas[1]] = programa->getIesPadre();
        // Otros datos...
        resultadoJson["Programa_" + std::to_string(codigo)] = programaJson;
    }

    archivoResultados << resultadoJson.dump(4);  // Formato con indentación de 4 espacios
    archivoResultados.close();

    if (!archivoResultados) {
        manejarErrores("Error al cerrar el archivo JSON: " + ruta);
        return false;
    }

    return true;
}

// Crear archivo de programas buscados en formato JSON
bool GestorJSON::crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const {
    std::ofstream archivoResultados(ruta + "buscados.json");
    if (!archivoResultados.is_open()) {
        manejarErrores("No se pudo abrir el archivo JSON para escribir: " + ruta);
        return false;
    }

    json resultadoJson;
    for (const auto &programa : programasBuscados) {
        json programaJson;
        programaJson[etiquetasColumnas[0]] = programa->getCodigoDeLaInstitucion();
        // Otros datos...
        resultadoJson["Programa_" + std::to_string(programa->getCodigoSniesDelPrograma())] = programaJson;
    }

    archivoResultados << resultadoJson.dump(4);  // Formato con indentación de 4 espacios
    archivoResultados.close();

    if (!archivoResultados) {
        manejarErrores("Error al cerrar el archivo JSON: " + ruta);
        return false;
    }

    return true;
}

// Crear archivo con datos adicionales en formato JSON
bool GestorJSON::crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const {
    std::ofstream archivoResultados(ruta + "extras.json");
    if (!archivoResultados.is_open()) {
        manejarErrores("No se pudo abrir el archivo JSON para escribir: " + ruta);
        return false;
    }

    json resultadoJson;
    for (const auto &fila : datosAImprimir) {
        json filaJson = json::array();
        for (const auto &dato : fila) {
            filaJson.push_back(dato);
        }
        resultadoJson.push_back(filaJson);
    }

    archivoResultados << resultadoJson.dump(4);  // Formato con indentación de 4 espacios
    archivoResultados.close();

    if (!archivoResultados) {
        manejarErrores("Error al cerrar el archivo JSON: " + ruta);
        return false;
    }

    return true;
}
