#include "GestorCsv.h"
#include <iostream>
#include <sstream>
#include <algorithm> // Para std::find

/**
 * @class GestorCsv
 * @brief Esta clase gestiona la lectura y escritura de archivos CSV relacionados con datos de programas académicos.
 */

// Función auxiliar para procesar una fila
void procesarFila(const std::string &fila, std::vector<std::string> &vectorFila, const std::string &delimitador, int limiteColumnas)
{
    std::stringstream streamFila(fila);
    std::string dato;
    int columna = 0;

    while (getline(streamFila, dato, delimitador[0]) && columna < limiteColumnas)
    {
        vectorFila[columna] = dato;
        columna++;
    }
}

// Función auxiliar para leer y procesar tres filas asociadas
void leerTresFilasAsociadas(std::ifstream &archivo, std::vector<std::string> &vectorFila, std::vector<std::vector<std::string>> &matrizResultado, const std::string &delimitador)
{
    std::string fila;
    for (int i = 0; i < 3; ++i)
    {
        if (getline(archivo, fila))
        {
            procesarFila(fila, vectorFila, delimitador, 39); // Procesar fila con límite de 39 columnas
            matrizResultado.push_back(vectorFila);
        }
    }
}

// Metodo para leer los códigos SNIES de un archivo CSV
std::vector<int> GestorCsv::leerProgramasCsv(const std::string &ruta) const
{
    std::vector<int> codigosSniesRetorno;
    std::ifstream archivoProgramasCsv(ruta);

    if (!archivoProgramasCsv.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << ruta << std::endl;
        return codigosSniesRetorno;
    }

    std::string linea;
    std::string dato;
    getline(archivoProgramasCsv, linea);

    while (getline(archivoProgramasCsv, linea))
    {
        std::stringstream streamLinea(linea);
        getline(streamLinea, dato, ';');
        try
        {
            int codigoSnies = std::stoi(dato);
            codigosSniesRetorno.push_back(codigoSnies);
        }
        catch (const std::invalid_argument&)
        {
            std::cerr << "Error de conversión en la línea: " << linea << std::endl;
        }
    }
    archivoProgramasCsv.close();
    return codigosSniesRetorno;
}

// Refactorización del metodo para leer el archivo del primer conjunto de datos (admitidos)
std::vector<std::vector<std::string>> GestorCsv::leerArchivoPrimera(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const
{
    std::vector<std::vector<std::string>> matrizResultado;
    std::string rutaCompleta = rutaBase + ano + ".csv";
    std::ifstream archivo(rutaCompleta);

    if (!archivo.is_open())
    {
        std::cerr << "No se pudo abrir el archivo: " << rutaCompleta << std::endl;
        return matrizResultado;
    }

    std::string fila;
    std::vector<std::string> vectorFila(39);
    std::string delimitador = ";";

    getline(archivo, fila);
    procesarFila(fila, vectorFila, delimitador, 39);
    matrizResultado.push_back(vectorFila);

    while (getline(archivo, fila))
    {
        procesarFila(fila, vectorFila, delimitador, 13); // Procesar fila con límite de 13 columnas

        int codigoSnies = std::stoi(vectorFila[12]);
        auto it = std::find(codigosSnies.begin(), codigosSnies.end(), codigoSnies);

        if (it != codigosSnies.end())
        {
            matrizResultado.push_back(vectorFila);

            leerTresFilasAsociadas(archivo, vectorFila, matrizResultado, delimitador);
        }
    }
    archivo.close();
    return matrizResultado;
}
// Metodo para leer el archivo del segundo conjunto de datos (matriculados)
std::vector<std::vector<std::string>> GestorCsv::leerArchivoSegunda(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const
{
    return leerArchivoPrimera(rutaBase, ano, codigosSnies);  // Reutilizamos la lógica para evitar duplicación
}

// Metodo para leer los archivos usando una columna específica
std::vector<std::vector<std::string>> GestorCsv::leerArchivo(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies, int columnaCodigoSnies) const
{
    std::vector<std::vector<std::string>> matrizResultado;
    std::string rutaCompleta = rutaBase + ano + ".csv";
    std::ifstream archivo(rutaCompleta);

    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << rutaCompleta << std::endl;
        return matrizResultado;
    }

    std::string fila;
    std::string dato;
    std::vector<std::string> vectorFila(2);
    std::string delimitador = ";";

    getline(archivo, fila);

    while (getline(archivo, fila))
    {
        std::stringstream streamFila(fila);
        int columna = 0;

        while (getline(streamFila, dato, delimitador[0]) && columna <= columnaCodigoSnies)
        {
            if (columna == columnaCodigoSnies)
            {
                vectorFila[0] = dato;
            }
            columna++;
        }

        int codigoSnies = std::stoi(vectorFila[0]);
        auto it = std::find(codigosSnies.begin(), codigosSnies.end(), codigoSnies);

        if (it != codigosSnies.end())
        {
            matrizResultado.push_back(vectorFila);
        }
    }

    archivo.close();
    return matrizResultado;
}

// Implementación mejorada de la creación de archivos
bool GestorCsv::crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const
{
    std::string rutaCompleta = ruta + "resultados.csv";
    std::ofstream archivoResultados(rutaCompleta);

    if (!archivoResultados.is_open())
    {
        std::cerr << "Error al crear el archivo: " << rutaCompleta << std::endl;
        return false;
    }

    for (const auto &etiqueta : etiquetasColumnas)
    {
        archivoResultados << etiqueta << ";";
    }
    archivoResultados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS\n";

    for (const auto &[codigo, programa] : mapaProgramas)
    {
        for (int i = 0; i < 8; ++i)
        {
            Consolidado *consolidado = programa->getConsolidado(i);
            archivoResultados << programa->getCodigoDeLaInstitucion() << ";"
                              << programa->getIesPadre() << ";"
                              << programa->getInstitucionDeEducacionSuperiorIes() << ";"
                              << consolidado->getAdmitidos() << ";"
                              << consolidado->getGraduados() << ";"
                              << consolidado->getInscritos() << ";"
                              << consolidado->getMatriculadosPrimerSemestre() << "\n";
        }
    }
    archivoResultados.close();
    return true;
}

// Implementación del metodo para crear archivos de los programas buscados
bool GestorCsv::crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const
{
    std::string rutaCompleta = ruta + "buscados.csv";
    std::ofstream archivoBuscados(rutaCompleta);

    if (!archivoBuscados.is_open())
    {
        std::cerr << "Error al crear el archivo: " << rutaCompleta << std::endl;
        return false;
    }

    for (const auto &etiqueta : etiquetasColumnas)
    {
        archivoBuscados << etiqueta << ";";
    }
    archivoBuscados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS\n";

    for (const auto &programa : programasBuscados)
    {
        for (int i = 0; i < 8; ++i)
        {
            Consolidado *consolidado = programa->getConsolidado(i);

            archivoBuscados << programa->getCodigoDeLaInstitucion() << ";"
                            << programa->getIesPadre() << ";"
                            << programa->getInstitucionDeEducacionSuperiorIes() << ";"
                            << programa->getPrincipalOSeccional() << ";"
                            << programa->getIdSectorIes() << ";"
                            << programa->getSectorIes() << ";"
                            << programa->getIdCaracter() << ";"
                            << programa->getCaracterIes() << ";"
                            << programa->getCodigoDelDepartamentoIes() << ";"
                            << programa->getDepartamentoDeDomicilioDeLaIes() << ";"
                            << programa->getCodigoDelMunicipioIes() << ";"
                            << programa->getMunicipioDeDomicilioDeLaIes() << ";"
                            << programa->getCodigoSniesDelPrograma() << ";"
                            << programa->getProgramaAcademico() << ";"
                            << consolidado->getIdSexo() << ";"
                            << consolidado->getSexo() << ";"
                            << consolidado->getAno() << ";"
                            << consolidado->getSemestre() << ";"
                            << consolidado->getAdmitidos() << ";"
                            << consolidado->getGraduados() << ";"
                            << consolidado->getInscritos() << ";"
                            << consolidado->getMatriculadosPrimerSemestre() << "\n";
        }
    }

    archivoBuscados.close();
    return true;
}

// Implementación del metodo para crear el archivo de extras
bool GestorCsv::crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const
{
    std::string rutaCompleta = ruta + "extras.csv";
    std::ofstream archivoExtra(rutaCompleta);

    if (!archivoExtra.is_open())
    {
        std::cerr << "Error al crear el archivo: " << rutaCompleta << std::endl;
        return false;
    }

    for (const auto &fila : datosAImprimir)
    {
        for (size_t i = 0; i < fila.size(); ++i)
        {
            archivoExtra << fila[i];
            if (i != (fila.size() - 1))
            {
                archivoExtra << ";";
            }
        }
        archivoExtra << "\n";
    }

    archivoExtra.close();
    return true;
}