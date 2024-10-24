#include "GestorTxt.h"
#include "GestorArchivo.h"
#include <fstream>
#include <iostream>

// Crear archivo TXT estándar
bool GestorTXT::crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const {
    std::ofstream archivoResultados(ruta + "resultados.txt");
    if (!archivoResultados.is_open()) {
        manejarErrores("No se pudo abrir el archivo TXT para escribir: " + ruta);
        return false;
    }

    // Escribir las etiquetas de las columnas
    for (const auto &etiqueta : etiquetasColumnas) {
        archivoResultados << etiqueta << "\t";  // Usamos tabulaciones en lugar de ";"
    }
    archivoResultados << "\n";

    // Escribir los datos de cada programa académico
    for (const auto &[codigo, programa] : mapaProgramas) {
        archivoResultados << programa->getCodigoDeLaInstitucion() << "\t"
                          << programa->getIesPadre() << "\t"
                          << programa->getInstitucionDeEducacionSuperiorIes() << "\n";
    }

    archivoResultados.close();
    if (!archivoResultados) {
        manejarErrores("Error al cerrar el archivo TXT: " + ruta);
        return false;
    }

    return true;
}

// Crear archivo de programas buscados en formato TXT
bool GestorTXT::crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const {
    std::ofstream archivoResultados(ruta + "buscados.txt");
    if (!archivoResultados.is_open()) {
        manejarErrores("No se pudo abrir el archivo TXT para escribir: " + ruta);
        return false;
    }

    // Escribir las etiquetas
    for (const auto &etiqueta : etiquetasColumnas) {
        archivoResultados << etiqueta << "\t";
    }
    archivoResultados << "\n";

    // Escribir los datos de los programas buscados
    for (const auto &programa : programasBuscados) {
        archivoResultados << programa->getCodigoDeLaInstitucion() << "\t"
                          << programa->getIesPadre() << "\t"
                          << programa->getInstitucionDeEducacionSuperiorIes() << "\n";
    }

    archivoResultados.close();
    if (!archivoResultados) {
        manejarErrores("Error al cerrar el archivo TXT: " + ruta);
        return false;
    }

    return true;
}

// Crear archivo con datos adicionales en formato TXT
bool GestorTXT::crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const {
    std::ofstream archivoResultados(ruta + "extras.txt");
    if (!archivoResultados.is_open()) {
        manejarErrores("No se pudo abrir el archivo TXT para escribir: " + ruta);
        return false;
    }

    // Escribir los datos
    for (const auto &fila : datosAImprimir) {
        for (const auto &dato : fila) {
            archivoResultados << dato << "\t";
        }
        archivoResultados << "\n";
    }

    archivoResultados.close();
    if (!archivoResultados) {
        manejarErrores("Error al cerrar el archivo TXT: " + ruta);
        return false;
    }

    return true;
}
