#include "SNIESController.h"
#include <iostream>     // For std::cerr, std::endl, std::cout
#include <string>       // For std::string, std::stoi
#include <vector>       // For std::vector
#include <string_view>  // For std::string_view
#include <list>         // For std::list
#include <memory>       // For std::unique_ptr
#include <utility>      // For std::make_unique
#include <execution>    // For parallel algorithms
#include <exception>    // For std::exception

/**
 * @class SNIESController
 * @brief Esta clase gestiona la lectura, procesamiento y escritura de datos CSV relacionados con programas académicos.
 *
 * La clase SNIESController utiliza la clase GestorCsv para leer y escribir archivos CSV. También maneja la lógica
 * para procesar los datos de los programas académicos y generar archivos de salida con los resultados.
 */

// Constructor por parámetros
SNIESController::SNIESController(const std::string &nuevaRutaProgramasCSV, const std::string &nuevaRutaAdmitidos, const std::string &nuevaRutaGraduados, const std::string &nuevaRutaInscritos, const std::string &nuevaRutaMatriculadosc, const std::string &nuevaRutaMatriculadosPrimerSemestre, const std::string &nuevaRutaOutput)
    : gestorCsvObj(), rutaProgramasCSV(nuevaRutaProgramasCSV), rutaAdmitidos(nuevaRutaAdmitidos), rutaGraduados(nuevaRutaGraduados), rutaInscritos(nuevaRutaInscritos), rutaMatriculados(nuevaRutaMatriculadosc), rutaMatriculadosPrimerSemestre(nuevaRutaMatriculadosPrimerSemestre), rutaOutput(nuevaRutaOutput)
{
}
// Destructor por defecto
SNIESController::~SNIESController() =default;

// Función para procesar los datos CSV
void SNIESController::procesarDatosCsv(const std::string &ano1, const std::string &ano2)
{
    std::vector<int> codigosSnies;
    try {
        codigosSnies = gestorCsvObj.leerProgramasCsv(rutaProgramasCSV);
    } catch (const std::exception& ex) {
        std::cerr << "Error al leer programas CSV: " << ex.what() << std::endl;
        return;
    }

    auto procesarArchivo = [&](const std::string &ruta, const std::string &ano, int columna, bool esPrimeraLectura) {
        auto programasAcademicosVector = esPrimeraLectura ?
            gestorCsvObj.leerArchivoPrimera(ruta, ano, codigosSnies) :
            gestorCsvObj.leerArchivo(ruta, ano, codigosSnies, columna);

        for (size_t i = esPrimeraLectura ? 1 : 0; i < programasAcademicosVector.size(); i += 4) {
            int codigoSnies = std::stoi(programasAcademicosVector[i][0]);
            auto it = programasAcademicos.find(codigoSnies);
            if (it == programasAcademicos.end() && esPrimeraLectura) {
                auto programaAcademico = std::make_unique<ProgramaAcademico>();
                try {
                    programaAcademico->setCodigoDeLaInstitucion(codigoSnies);
                } catch (const std::exception& ex) {
                    std::cerr << "Error al convertir el código de la institución: " << ex.what() << std::endl;
                    continue;
                }
                programaAcademico->setIesPadre(std::stoi(programasAcademicosVector[i][1]));
                programaAcademico->setInstitucionDeEducacionSuperiorIes(programasAcademicosVector[i][2]);
                programaAcademico->setPrincipalOSeccional(programasAcademicosVector[i][3]);
                programaAcademico->setIdSectorIes(std::stoi(programasAcademicosVector[i][4]));
                programaAcademico->setSectorIes(programasAcademicosVector[i][5]);
                programaAcademico->setMunicipioDeDomicilioDeLaIes(programasAcademicosVector[i][11]);
                programaAcademico->setCodigoSniesDelPrograma(codigoSnies);
                programaAcademico->setProgramaAcademico(programasAcademicosVector[i][13]);
                programaAcademico->setIdNivelAcademico(std::stoi(programasAcademicosVector[i][14]));
                programaAcademico->setNivelAcademico(programasAcademicosVector[i][15]);
                programaAcademico->setIdNivelDeFormacion(std::stoi(programasAcademicosVector[i][16]));
                programaAcademico->setNivelDeFormacion(programasAcademicosVector[i][17]);
                programaAcademico->setIdMetodologia(std::stoi(programasAcademicosVector[i][18]));
                programaAcademico->setMetodologia(programasAcademicosVector[i][19]);
                programaAcademico->setIdArea(std::stoi(programasAcademicosVector[i][20]));
                programaAcademico->setAreaDeConocimiento(programasAcademicosVector[i][21]);
                programaAcademico->setIdNucleo(std::stoi(programasAcademicosVector[i][22]));
                programaAcademico->setNucleoBasicoDelConocimientoNbc(programasAcademicosVector[i][23]);
                programaAcademico->setIdCineCampoAmplio(std::stoi(programasAcademicosVector[i][24]));
                programaAcademico->setDescCineCampoAmplio(programasAcademicosVector[i][25]);
                programaAcademico->setIdCineCampoEspecifico(std::stoi(programasAcademicosVector[i][26]));
                programaAcademico->setDescCineCampoEspecifico(programasAcademicosVector[i][27]);
                programaAcademico->setIdCineCodigoDetallado(std::stoi(programasAcademicosVector[i][28]));
                programaAcademico->setDescCineCodigoDetallado(programasAcademicosVector[i][29]);
                programaAcademico->setCodigoDelDepartamentoPrograma(std::stoi(programasAcademicosVector[i][30]));
                programaAcademico->setDepartamentoDeOfertaDelPrograma(programasAcademicosVector[i][31]);
                programaAcademico->setCodigoDelMunicipioPrograma(std::stoi(programasAcademicosVector[i][32]));
                programaAcademico->setMunicipioDeOfertaDelPrograma(programasAcademicosVector[i][33]);

                for (int m = 0; m < 4; ++m) {
                    Consolidado *consolidado = programaAcademico->getConsolidado(m + 4);
                    consolidado->setGraduados(std::stoi(programasAcademicosVector[i + m][1]));
                }
                programasAcademicos.emplace(codigoSnies, programaAcademico.release());
            } else if (it != programasAcademicos.end()) {
                for (int m = 0; m < 4; ++m) {
                    Consolidado *consolidado = it->second->getConsolidado(m + 4);
                    consolidado->setGraduados(std::stoi(programasAcademicosVector[i + m][1]));
                }
            }
        }
    };

    procesarArchivo(rutaAdmitidos, ano1, 0, true);
    procesarArchivo(rutaAdmitidos, ano2, 0, false);
    procesarArchivo(rutaGraduados, ano1, 13, false);
    procesarArchivo(rutaGraduados, ano2, 13, false);
    procesarArchivo(rutaInscritos, ano1, 12, false);
    procesarArchivo(rutaInscritos, ano2, (ano2 == "2022") ? 12 : 13, false);
    procesarArchivo(rutaMatriculados, ano1, 13, false);
    procesarArchivo(rutaMatriculados, ano2, 13, false);
    procesarArchivo(rutaMatriculadosPrimerSemestre, ano1, 13, false);
    procesarArchivo(rutaMatriculadosPrimerSemestre, ano2, 13, false);

    bool archivoCreado = gestorCsvObj.crearArchivo(rutaOutput, programasAcademicos, etiquetasColumnas);
    std::cout << archivoCreado << std::endl;
}

std::vector<int> SNIESController::leerCodigosSnies() {
    try {
        return gestorCsvObj.leerProgramasCsv(rutaProgramasCSV);
    } catch (const std::exception& ex) {
        std::cerr << "Error al leer programas CSV: " << ex.what() << std::endl;
        return {};
    }
}
// Función para leer los datos del primer archivo. Retorna una matriz de datos leidos
std::vector<std::vector<std::string>> SNIESController::leerDatosPrimera(std::string_view ano1, const std::vector<int>& codigosSnies) {
    try {
        return gestorCsvObj.leerArchivoPrimera(rutaAdmitidos, std::string(ano1), codigosSnies);
    } catch (const std::exception& ex) {
        std::cerr << "Error al leer datos: " << ex.what() << std::endl;
        return {};
    }
}
// Función para procesar un programa académico
void SNIESController::procesarProgramaAcademico(const std::vector<std::vector<std::string>>& datos, int i) {
    auto programaAcademico = std::make_unique<ProgramaAcademico>();
    try {
        programaAcademico->setCodigoDeLaInstitucion(std::stoi(datos[i][0]));
        // Other set methods...
    } catch (const std::exception& ex) {
        std::cerr << "Error al procesar el programa académico: " << ex.what() << std::endl;
        return;
    }
    programasAcademicos.emplace(programaAcademico->getCodigoSniesDelPrograma(), std::move(programaAcademico).get());
}
// Función para buscar programas académicos
void SNIESController::buscarProgramas(bool flag, const std::string &palabraClave, int idComparacion)
{
    std::list<ProgramaAcademico *> listaProgramas;
    for (auto& [codigoSnies, programaAcademico] : programasAcademicos)
    {
        ProgramaAcademico *programa = programaAcademico;
        std::string nombre = programa->getProgramaAcademico();
        int id = programa->getIdNivelDeFormacion();
        if (nombre.find(palabraClave) != std::string::npos && id == idComparacion)
        {
            listaProgramas.push_back(programa);
            std::cout << programa->getCodigoSniesDelPrograma() << ";" << programa->getProgramaAcademico() << ";" << programa->getCodigoDeLaInstitucion() << ";" << programa->getInstitucionDeEducacionSuperiorIes() << ";" << programa->getMetodologia() << std::endl;
        }
    }

    if (flag)
    {
        gestorCsvObj.crearArchivoBuscados(rutaOutput, listaProgramas, etiquetasColumnas);
    }
}

// Función para calcular datos adicionales
void SNIESController::calcularDatosExtra(bool flag)
{
    std::vector<std::vector<std::string>> matrizFinal;
    auto matrizEtiquetas1 = generarMatrizEtiquetas1();
    auto matrizEtiquetas2 = generarMatrizEtiquetas2();
    auto matrizEtiquetas3 = generarMatrizEtiquetas3();

    int sumaPrimerAno = 0;
    int sumaSegundoAno = 0;

    procesarDatos(matrizEtiquetas1, sumaPrimerAno, sumaSegundoAno, flag);

    if (flag) {
        gestorCsvObj.crearArchivoExtra(rutaOutput, matrizFinal);
    }
}


/**
* La función generarMatrizEtiquetas crea una matriz que contiene etiquetas para la suma de alumnos
* matriculados en los programas seleccionados. Inicializa un std::vector de std::vector<std::string> para
* contener la matriz y luego define un std::vector<std::string> llamado etiquetas1 con dos etiquetas:
* «Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual) Primer año» y “Suma
* Estudiantes Matriculados )”.

 */

std::vector<std::vector<std::string>> SNIESController::generarMatrizEtiquetas1() {
    std::vector<std::vector<std::string>> matrizEtiquetas1;
    std::vector<std::string> etiquetas1 = {
        "Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual) Primer año",
        "Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual)"
    };
    matrizEtiquetas1.push_back(etiquetas1);
    return matrizEtiquetas1;
}

std::vector<std::vector<std::string>> SNIESController::generarMatrizEtiquetas2() {
    std::vector<std::vector<std::string>> matrizEtiquetas2;
    std::vector<std::string> etiquetas2 = {
        "Codigo Snies", "Nombre del Programa", "Nombre del Institucion",
        "Diferencial porcentual anual de NEOS"
    };
    matrizEtiquetas2.push_back(etiquetas2);
    return matrizEtiquetas2;
}

std::vector<std::vector<std::string>> SNIESController::generarMatrizEtiquetas3() {
    std::vector<std::vector<std::string>> matrizEtiquetas3;
    std::vector<std::string> etiquetas3 = {
        "Codigo Snies", " Nombre del Programa sin NEOS en los ultimos 3 semestres"
    };
    matrizEtiquetas3.push_back(etiquetas3);
    return matrizEtiquetas3;
}

/**
*La función procesarDatos de la clase SNIESController procesa los datos de los programas académicos para generar
*matrices de etiquetas y sumas de alumnos matriculados. Recorre los programas académicos, calcula las sumas y
*diferencias de nuevos alumnos (NEOS) para los años especificados y genera matrices para diferentes informes. Si el
*parámetro flag es true, crea un fichero de salida con los datos procesados.

 */
void SNIESController::procesarDatos(const std::vector<std::vector<std::string>>& matrizEtiquetas1, int& sumaPrimerAno, int& sumaSegundoAno, bool flag)
{
    std::vector<std::vector<std::string>> matrizFinal;
    std::vector<std::vector<std::string>> matrizEtiquetas2;
    std::vector<std::vector<std::string>> matrizEtiquetas3;
    std::vector<std::string> etiquetas1 = {"Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual) Primer año", "Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual)"};
    matrizFinal.push_back(etiquetas1);
    std::vector<std::string> etiquetas2 = {"Codigo Snies", "Nombre del Programa", "Nombre del Institucion", "Diferencial porcentual anual de NEOS"};
    matrizEtiquetas2.push_back(etiquetas2);
    std::vector<std::string> etiquetas3 = {"Codigo Snies", " Nombre del Programa sin NEOS en los ultimos 3 semestres"};
    matrizEtiquetas3.push_back(etiquetas3);

    for (auto& [codigoSnies, programa] : programasAcademicos)
    {
        int neosPrimerAno = 0, neosSegundoAno = 0, diferenciaNeos = 0;
        if (programa->getIdMetodologia() == 1 || programa->getIdMetodologia() == 3)
        {
            for (int i = 0; i < 4; ++i)
            {
                sumaPrimerAno += programa->getConsolidado(i)->getMatriculados();
                sumaSegundoAno += programa->getConsolidado(i + 4)->getMatriculados();
            }
        }
        for (int i = 0; i < 4; ++i)
        {
            neosPrimerAno += programa->getConsolidado(i)->getMatriculadosPrimerSemestre();
            neosSegundoAno += programa->getConsolidado(i + 4)->getMatriculadosPrimerSemestre();
        }

        diferenciaNeos = neosPrimerAno != 0 ? ((neosSegundoAno - neosPrimerAno) * 100) / neosPrimerAno : 0;
        matrizEtiquetas2.push_back({std::to_string(programa->getCodigoSniesDelPrograma()), programa->getProgramaAcademico(), programa->getInstitucionDeEducacionSuperiorIes(), std::to_string(diferenciaNeos)});

        int SumaNeosPrimerSemestre = 0, SumaNeosSegundoSemestre = 0, SumaNeosTercerSemestre = 0, SumaNeosCuartoSemestre = 0;
        for (int i = 0; i < 4; ++i)
        {
            SumaNeosPrimerSemestre += programa->getConsolidado(i)->getMatriculadosPrimerSemestre() + programa->getConsolidado(i + 2)->getMatriculadosPrimerSemestre();
            SumaNeosSegundoSemestre += programa->getConsolidado(i + 2)->getMatriculadosPrimerSemestre() + programa->getConsolidado(i + 4)->getMatriculadosPrimerSemestre();
            SumaNeosTercerSemestre += programa->getConsolidado(i + 4)->getMatriculadosPrimerSemestre() + programa->getConsolidado(i + 6)->getMatriculadosPrimerSemestre();
            SumaNeosCuartoSemestre += programa->getConsolidado(i + 6)->getMatriculadosPrimerSemestre() + programa->getConsolidado(i + 8)->getMatriculadosPrimerSemestre();
        }

        if ((SumaNeosPrimerSemestre == 0 && SumaNeosSegundoSemestre == 0 && SumaNeosTercerSemestre == 0) || (SumaNeosSegundoSemestre == 0 && SumaNeosTercerSemestre == 0 && SumaNeosCuartoSemestre == 0))
        {
            matrizEtiquetas3.push_back({std::to_string(programa->getCodigoSniesDelPrograma()), programa->getProgramaAcademico()});
        }
    }
    matrizFinal.insert(matrizFinal.end(), matrizEtiquetas2.begin(), matrizEtiquetas2.end());
    matrizFinal.insert(matrizFinal.end(), matrizEtiquetas3.begin(), matrizEtiquetas3.end());

    for (const auto &fila : matrizFinal)
    {
        for (size_t i = 0; i < fila.size(); ++i)
        {
            std::cout << fila[i];
            if (i < fila.size() - 1)
            {
                std::cout << ";";
            }
        }
        std::cout << std::endl;
    }

    if (flag)
    {
        gestorCsvObj.crearArchivoExtra(rutaOutput, matrizFinal);
    }
}