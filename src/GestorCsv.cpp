#include "GestorCsv.h"
#include <stdexcept>
#include <iostream>
#include <string_view>
#include <utility>

std::vector<int> GestorCsv::leerProgramasCsv(const std::string &ruta) const
{
    std::vector<int> codigosSniesRetorno;
    std::ifstream archivoProgramasCsv(ruta);
    if (!archivoProgramasCsv.is_open())
    {
        std::cerr << "Archivo " << ruta << " no se pudo abrir correctamente" << std::endl;
        return codigosSniesRetorno;
    }

    std::string linea;
    std::string dato;
    // Leer los programas, comenzando desde la segunda línea (se asume que la primera es un encabezado)
    std::getline(archivoProgramasCsv, linea);  // Saltar la primera línea
    while (std::getline(archivoProgramasCsv, linea))
    {
        std::stringstream streamLinea(linea);
        std::getline(streamLinea, dato, ';');
        try
        {
            codigosSniesRetorno.push_back(std::stoi(dato));  // Convertir el dato a entero y añadirlo al vector
        }
        catch (const std::invalid_argument &)
        {
            std::cerr << "Error al convertir el dato a entero: " << dato << std::endl;
        }
    }

    archivoProgramasCsv.close();
    return codigosSniesRetorno;
}

// Función genérica para leer archivos y reutilizar en leerArchivoPrimera y leerArchivoSegunda
std::vector<std::vector<std::string>> GestorCsv::leerArchivoComun(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies, int numColumnas, int filasAdicionales) const
{
    std::vector<std::vector<std::string>> matrizResultado;
    std::string rutaCompleta = rutaBase + ano + ".csv";
    std::ifstream archivo(rutaCompleta);

    if (!archivo.is_open())
    {
        std::cerr << "Archivo " << rutaCompleta << " no se pudo abrir correctamente" << std::endl;
        return matrizResultado;
    }

    // Leer etiquetas (primera fila)
    matrizResultado.push_back(leerFila(archivo, numColumnas));

    // Leer filas de datos
    while (archivo)
    {
        std::vector<std::string> vectorFila = leerFila(archivo, numColumnas);

        if (!vectorFila.empty() && verificarPrograma(vectorFila, codigosSnies))
        {
            matrizResultado.push_back(vectorFila);
            agregarFilasAdicionales(archivo, matrizResultado, filasAdicionales, numColumnas);
        }
    }

    archivo.close();
    return matrizResultado;
}

std::vector<std::vector<std::string>> GestorCsv::leerArchivoPrimera(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const {
    std::vector<std::vector<std::string>> matrizResultado;
    std::string rutaCompleta = rutaBase + ano + ".csv";
    std::ifstream archivoPrimero(rutaCompleta);

    if (!archivoPrimero.is_open()) {
        std::cerr << "Archivo " << rutaCompleta << " no se pudo abrir correctamente" << std::endl;
        return matrizResultado;
    }

    // Leer etiquetas
    matrizResultado.push_back(leerFila(archivoPrimero, 39));

    // Leer filas de datos
    while (archivoPrimero) {
        std::vector<std::string> vectorFila = leerFila(archivoPrimero, 13);

        if (verificarPrograma(vectorFila, codigosSnies)) {
            matrizResultado.push_back(vectorFila);
            leerFilasRestantes(archivoPrimero, matrizResultado, 3);
        }
    }

    archivoPrimero.close();
    return matrizResultado;
}

// Refactorización de leerArchivoSegunda
std::vector<std::vector<std::string>> GestorCsv::leerArchivoSegunda(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const
{
    return leerArchivoComun(rutaBase, ano, codigosSnies, 13, 3);
}

// Función para leer una fila del archivo CSV
std::vector<std::string> GestorCsv::leerFila(std::ifstream &archivo, int numColumnas) const
{
    std::vector<std::string> vectorFila(numColumnas);
    if (std::string fila; std::getline(archivo, fila))
    {
        std::stringstream streamFila(fila);
        std::string dato;
        int columna = 0;
        while (std::getline(streamFila, dato, ';') && columna < numColumnas)
        {
            vectorFila[columna] = std::move(dato);  // Usar move para evitar copiar el dato
            columna++;
        }
    }

    return vectorFila;
}

// Verificar si la fila corresponde a un programa válido
bool GestorCsv::verificarPrograma(const std::vector<std::string> &vectorFila, const std::vector<int> &codigosSnies) const
{
    if (vectorFila[12] != "Sin programa especifico")
    {
        return std::find(codigosSnies.begin(), codigosSnies.end(), std::stoi(vectorFila[12])) != codigosSnies.end();
    }
    return false;
}

// Función para agregar filas adicionales al archivo
void GestorCsv::agregarFilasAdicionales(std::ifstream &archivo, std::vector<std::vector<std::string>> &matrizResultado, int numFilas, int numColumnas) const
{
    for (int j = 0; j < numFilas; j++)
    {
        matrizResultado.push_back(leerFila(archivo, numColumnas));
    }
}

// Función para crear archivos CSV
bool GestorCsv::crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapadeProgramasAcademicos, const std::vector<std::string> &etiquetasColumnas) const {
    bool estadoCreacion = false;
    std::string rutaCompleta = ruta + "resultados.csv";

    // Usando init-statement para la apertura del archivo
    if (std::ofstream archivoResultados(rutaCompleta); archivoResultados.is_open()) {
        // Imprimir las etiquetas (Primera fila)
        for (const auto &etiqueta : etiquetasColumnas) {
            archivoResultados << etiqueta << ";";
        }
        archivoResultados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS" << std::endl;

        for (const auto &[key, programa] : mapadeProgramasAcademicos) {
            for (int i = 0; i < 8; i++) {
                const Consolidado *consolidadoActual = programa->getConsolidado(i);
                archivoResultados << programa->getCodigoDeLaInstitucion() << ";";
                archivoResultados << programa->getIesPadre() << ";";
                archivoResultados << programa->getInstitucionDeEducacionSuperiorIes() << ";";
                archivoResultados << programa->getPrincipalOSeccional() << ";";
                archivoResultados << programa->getIdSectorIes() << ";";
                archivoResultados << programa->getSectorIes() << ";";
                archivoResultados << programa->getIdCaracter() << ";";
                archivoResultados << programa->getCaracterIes() << ";";
                archivoResultados << programa->getCodigoDelDepartamentoIes() << ";";
                archivoResultados << programa->getDepartamentoDeDomicilioDeLaIes() << ";";
                archivoResultados << programa->getCodigoDelMunicipioIes() << ";";
                archivoResultados << programa->getMunicipioDeDomicilioDeLaIes() << ";";
                archivoResultados << programa->getCodigoSniesDelPrograma() << ";";
                archivoResultados << programa->getProgramaAcademico() << ";";
                archivoResultados << programa->getIdNivelAcademico() << ";";
                archivoResultados << programa->getNivelAcademico() << ";";
                archivoResultados << programa->getIdNivelDeFormacion() << ";";
                archivoResultados << programa->getNivelDeFormacion() << ";";
                archivoResultados << programa->getIdMetodologia() << ";";
                archivoResultados << programa->getMetodologia() << ";";
                archivoResultados << programa->getIdArea() << ";";
                archivoResultados << programa->getAreaDeConocimiento() << ";";
                archivoResultados << programa->getIdNucleo() << ";";
                archivoResultados << programa->getNucleoBasicoDelConocimientoNbc() << ";";
                archivoResultados << programa->getIdCineCampoAmplio() << ";";
                archivoResultados << programa->getDescCineCampoAmplio() << ";";
                archivoResultados << programa->getIdCineCampoEspecifico() << ";";
                archivoResultados << programa->getDescCineCampoEspecifico() << ";";
                archivoResultados << programa->getIdCineCodigoDetallado() << ";";
                archivoResultados << programa->getDescCineCodigoDetallado() << ";";
                archivoResultados << programa->getCodigoDelDepartamentoPrograma() << ";";
                archivoResultados << programa->getDepartamentoDeOfertaDelPrograma() << ";";
                archivoResultados << programa->getCodigoDelMunicipioPrograma() << ";";
                archivoResultados << programa->getMunicipioDeOfertaDelPrograma() << ";";

                archivoResultados << consolidadoActual->getIdSexo() << ";";
                archivoResultados << consolidadoActual->getSexo() << ";";
                archivoResultados << consolidadoActual->getAno() << ";";
                archivoResultados << consolidadoActual->getSemestre() << ";";
                archivoResultados << consolidadoActual->getAdmitidos() << ";";
                archivoResultados << consolidadoActual->getGraduados() << ";";
                archivoResultados << consolidadoActual->getInscritos() << ";";
                archivoResultados << consolidadoActual->getMatriculados() << ";";
                archivoResultados << consolidadoActual->getMatriculadosPrimerSemestre() << std::endl;
            }
        }

        estadoCreacion = true;
        std::cout << "Archivo Creado en: " << rutaCompleta << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo: " << rutaCompleta << std::endl;
    }

    return estadoCreacion;
}

// Función para imprimir una fila
void GestorCsv::imprimirFila(std::ofstream &archivo, const std::vector<std::string> &fila) const
{
    for (size_t i = 0; i < fila.size(); ++i)
    {
        archivo << fila[i];
        if (i < fila.size() - 1)
        {
            archivo << ";";
        }
    }
    archivo << std::endl;
}

bool GestorCsv::crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const
{
    std::string rutaCompleta = ruta + "extras.csv";
    std::ofstream archivoExtra(rutaCompleta);

    if (!archivoExtra.is_open())
    {
        std::cerr << "No se pudo abrir el archivo: " << rutaCompleta << std::endl;
        return false;
    }

    // Imprimir las filas en el archivo
    for (const auto &fila : datosAImprimir)
    {
        imprimirFila(archivoExtra, fila);
    }

    std::cout << "Archivo Creado en: " << rutaCompleta << std::endl;
    archivoExtra.close();
    return true;
}

void GestorCsv::leerFilasRestantes(std::ifstream &archivo, std::vector<std::vector<std::string>> &matrizResultado, int numFilas) const
{
    for (int i = 0; i < numFilas; ++i)
    {
        std::vector<std::string> fila = leerFila(archivo, 13);
        if (!fila.empty())
        {
            matrizResultado.push_back(fila);
        }
    }
}

std::vector<std::vector<std::string>> GestorCsv::leerArchivo(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies, int columnaCodigoSnies) const
{
    std::vector<std::vector<std::string>> matrizResultado;
    std::string rutaCompleta = rutaBase + ano + ".csv";
    std::ifstream archivo(rutaCompleta);

    if (!archivo.is_open())
    {
        std::cerr << "Archivo " << rutaCompleta << " no se pudo abrir correctamente" << std::endl;
        return matrizResultado;
    }

    matrizResultado.push_back(leerFila(archivo, 39));

    while (archivo)
    {
        std::vector<std::string> vectorFila = leerFila(archivo, 13);

        if (verificarPrograma(vectorFila, codigosSnies, columnaCodigoSnies))
        {
            matrizResultado.push_back(vectorFila);
            leerFilasRestantes(archivo, matrizResultado, 3);
        }
    }

    archivo.close();
    return matrizResultado;
}

bool GestorCsv::crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const
{
    std::ofstream archivo(ruta);
    if (!archivo.is_open())
    {
        std::cerr << "No se pudo abrir el archivo: " << ruta << std::endl;
        return false;
    }

    for (const auto &etiqueta : etiquetasColumnas)
    {
        archivo << etiqueta << ";";
    }
    archivo << std::endl;

    for (const auto *programa : programasBuscados)
    {
        archivo << programa->getCodigoSniesDelPrograma() << ";";
        archivo << programa->getProgramaAcademico() << ";";
        archivo << std::endl;
    }

    archivo.close();
    return true;
}

bool GestorCsv::verificarPrograma(const std::vector<std::string> &vectorFila, const std::vector<int> &codigosSnies, int columnaCodigoSnies) const
{
    // Verificar que la columna del código SNIES no esté vacía y tenga un código válido
    if (!vectorFila[columnaCodigoSnies].empty())
    {
        // Convertir el código SNIES de la columna especificada a entero y verificar si está en la lista de códigos permitidos
        int codigoSnies = std::stoi(vectorFila[columnaCodigoSnies]);
        return std::find(codigosSnies.begin(), codigosSnies.end(), codigoSnies) != codigosSnies.end();
    }
    return false;
}