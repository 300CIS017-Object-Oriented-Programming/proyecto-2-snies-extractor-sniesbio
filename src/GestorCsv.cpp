#include "GestorCsv.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

// Función para establecer el delimitador
void GestorCsv::setDelimitador(std::string_view nuevoDelimitador)
{
    delimitador = nuevoDelimitador;
}

// Función auxiliar para procesar una fila del CSV usando el delimitador
void GestorCsv::procesarFila(const std::string &fila, std::vector<std::string> &vectorFila) const
{
    std::stringstream streamFila(fila);
    std::string dato;
    int columna = 0;

    while (getline(streamFila, dato, delimitador[0]))
    {
        if (columna < vectorFila.size()) {
            vectorFila[columna] = dato;
        }
        columna++;
    }
}

// Función para leer tres filas asociadas en el archivo
void GestorCsv::leerTresFilasAsociadas(std::ifstream &archivo, std::vector<std::string> &vectorFila, std::vector<std::vector<std::string>> &matrizResultado) const
{
    std::string fila;
    for (int i = 0; i < 3; ++i) {
        if (getline(archivo, fila)) {
            procesarFila(fila, vectorFila);
            matrizResultado.push_back(vectorFila);
        }
    }
}

// Metodo para leer los códigos SNIES de un archivo CSV
std::vector<int> GestorCsv::leerProgramasCsv(const std::string &ruta) const
{
    std::vector<int> codigosSniesRetorno;
    std::ifstream archivoProgramasCsv(ruta);

    if (!archivoProgramasCsv.is_open()) {
        std::cerr << "Error al abrir el archivo: " << ruta << std::endl;
        return codigosSniesRetorno;
    }

    std::string linea;
    std::string dato;
    getline(archivoProgramasCsv, linea);

    while (getline(archivoProgramasCsv, linea)) {
        std::stringstream streamLinea(linea);
        getline(streamLinea, dato, delimitador[0]);
        try {
            int codigoSnies = std::stoi(dato);
            codigosSniesRetorno.push_back(codigoSnies);
        } catch (const std::invalid_argument &) {
            std::cerr << "Error de conversión en la línea: " << linea << std::endl;
        }
    }
    archivoProgramasCsv.close();
    return codigosSniesRetorno;
}

// Refactorización del metodo para leer el archivo del primer conjunto de datos
std::vector<std::vector<std::string>> GestorCsv::leerArchivoPrimera(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const
{
    std::vector<std::vector<std::string>> matrizResultado;
    std::string rutaCompleta = rutaBase + ano + ".csv";
    std::ifstream archivo(rutaCompleta);

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << rutaCompleta << std::endl;
        return matrizResultado;
    }

    std::string fila;
    std::vector<std::string> vectorFila(39);

    while (getline(archivo, fila)) {
        procesarFila(fila, vectorFila);

        try {
            int codigoSnies = std::stoi(vectorFila[0]);
            if (std::find(codigosSnies.begin(), codigosSnies.end(), codigoSnies) != codigosSnies.end()) {
                matrizResultado.push_back(vectorFila);
            }
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Error al convertir el código SNIES en la fila: " << fila << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Código SNIES fuera de rango en la fila: " << fila << std::endl;
        }
    }

    archivo.close();
    return matrizResultado;
}

// Refactorización del metodo para leer el segundo conjunto de datos (reutiliza la lógica del primero)
std::vector<std::vector<std::string>> GestorCsv::leerArchivoSegunda(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const
{
    return leerArchivoPrimera(rutaBase, ano, codigosSnies);
}

std::vector<std::vector<std::string>> GestorCsv::leerArchivo(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const
{
    std::vector<std::vector<std::string>> matrizResultado;
    std::string rutaCompleta = rutaBase + ano + ".csv";
    std::ifstream archivo(rutaCompleta);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << rutaCompleta << std::endl;
        return matrizResultado;
    }

    std::string fila;
    std::vector<std::string> vectorFila(39);

    while (getline(archivo, fila)) {
        procesarFila(fila, vectorFila);

        try {
            int codigoSnies = std::stoi(vectorFila[0]);
            if (std::find(codigosSnies.begin(), codigosSnies.end(), codigoSnies) != codigosSnies.end()) {
                matrizResultado.push_back(vectorFila);
            }
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Error al convertir el código SNIES en la fila: " << fila << std::endl;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Código SNIES fuera de rango en la fila: " << fila << std::endl;
        }
    }

    archivo.close();
    return matrizResultado;
}

// metodo para crear un archivo de salida en formato CSV
bool GestorCsv::crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const
{
    std::ofstream archivoResultados(ruta);
    if (!archivoResultados.is_open()) {
        std::cerr << "Error al crear el archivo: " << ruta << std::endl;
        return false;
    }

    // Escribir las etiquetas de columnas
    for (const auto &etiqueta : etiquetasColumnas) {
        archivoResultados << etiqueta << delimitador;
    }
    archivoResultados << "\n";

    // Escribir los datos
    for (const auto &[codigo, programa] : mapaProgramas) {
        for (int i = 0; i < 8; ++i) {
            const Consolidado *consolidado = programa->getConsolidado(i);
            archivoResultados << programa->getCodigoDeLaInstitucion() << delimitador
                              << programa->getIesPadre() << delimitador
                              << programa->getInstitucionDeEducacionSuperiorIes() << delimitador
                              << consolidado->getAdmitidos() << delimitador
                              << consolidado->getGraduados() << delimitador
                              << consolidado->getInscritos() << delimitador
                              << consolidado->getMatriculadosPrimerSemestre() << "\n";
        }
    }

    archivoResultados.close();
    return true;
}

// Implementación de crearArchivoBuscados
bool GestorCsv::crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const
{
    std::ofstream archivoBuscados(ruta);
    if (!archivoBuscados.is_open()) {
        std::cerr << "Error al abrir el archivo: " << ruta << std::endl;
        return false;
    }

    for (const auto &etiqueta : etiquetasColumnas) {
        archivoBuscados << etiqueta << delimitador;
    }
    archivoBuscados << "\n";

    for (const auto &programa : programasBuscados) {
        archivoBuscados << programa->getCodigoSniesDelPrograma() << delimitador
                        << programa->getProgramaAcademico() << delimitador
                        << programa->getInstitucionDeEducacionSuperiorIes() << "\n";
    }

    archivoBuscados.close();
    return true;
}

// Implementación de crearArchivoExtra
bool GestorCsv::crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const
{
    std::ofstream archivoExtra(ruta);
    if (!archivoExtra.is_open()) {
        std::cerr << "Error al abrir el archivo: " << ruta << std::endl;
        return false;
    }

    for (const auto &fila : datosAImprimir) {
        for (size_t i = 0; i < fila.size(); ++i) {
            archivoExtra << fila[i];
            if (i < fila.size() - 1) {
                archivoExtra << delimitador;
            }
        }
        archivoExtra << "\n";
    }

    archivoExtra.close();
    return true;
}