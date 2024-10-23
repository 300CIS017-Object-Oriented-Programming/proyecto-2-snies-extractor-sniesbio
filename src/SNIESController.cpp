#include "SNIESController.h"
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <list>
#include <memory>
#include <utility>
#include <sstream>
#include <exception>

SNIESController::SNIESController(const std::string &nuevaRutaProgramasCSV, const std::string &nuevaRutaAdmitidos, const std::string &nuevaRutaGraduados, const std::string &nuevaRutaInscritos, const std::string &nuevaRutaMatriculadosc, const std::string &nuevaRutaMatriculadosPrimerSemestre, const std::string &nuevaRutaOutput)
    : gestorCsvObj(), rutaProgramasCSV(nuevaRutaProgramasCSV), rutaAdmitidos(nuevaRutaAdmitidos), rutaGraduados(nuevaRutaGraduados), rutaInscritos(nuevaRutaInscritos), rutaMatriculados(nuevaRutaMatriculadosc), rutaMatriculadosPrimerSemestre(nuevaRutaMatriculadosPrimerSemestre), rutaOutput(nuevaRutaOutput)
{
}

SNIESController::~SNIESController() = default;

std::map<std::string, int, std::less<>> SNIESController::mapearColumnas(const std::string& encabezado, const std::string& delimitador) const {
    std::map<std::string, int, std::less<>> mapeo;
    std::istringstream stream(encabezado);
    std::string columna;
    int index = 0;

    // Dividir el encabezado por el delimitador
    while (std::getline(stream, columna, delimitador[0])) {
        mapeo[columna] = index++;
    }

    return mapeo;
}

void SNIESController::procesarDatosCsv(const std::string &ano1, const std::string &ano2)
{
    std::vector<int> codigosSnies;

    try {
        codigosSnies = gestorCsvObj.leerProgramasCsv(rutaProgramasCSV);
    } catch (const std::ios_base::failure& ioEx) {
        std::cerr << "Error de entrada/salida al leer programas CSV: " << ioEx.what() << std::endl;
        return;
    } catch (const std::invalid_argument& argEx) {
        std::cerr << "Error de conversión al leer programas CSV: " << argEx.what() << std::endl;
        return;
    } catch (const std::exception& ex) {
        std::cerr << "Error inesperado al leer programas CSV: " << ex.what() << std::endl;
        return;
    }

    auto procesarArchivo = [&](const std::string &ruta, const std::string &ano, bool esPrimeraLectura) {
        std::vector<std::vector<std::string>> programasAcademicosVector;

        try {
            programasAcademicosVector = esPrimeraLectura ?
                gestorCsvObj.leerArchivoPrimera(ruta, ano, codigosSnies) :
                gestorCsvObj.leerArchivo(ruta, ano, codigosSnies);
        } catch (const std::ios_base::failure& ioEx) {
            std::cerr << "Error de entrada/salida al procesar el archivo: " << ioEx.what() << std::endl;
            return;
        } catch (const std::invalid_argument& argEx) {
            std::cerr << "Error de conversión en el archivo: " << argEx.what() << std::endl;
            return;
        } catch (const std::exception& ex) {
            std::cerr << "Error inesperado al procesar el archivo: " << ex.what() << std::endl;
            return;
        }

        for (size_t i = esPrimeraLectura ? 1 : 0; i < programasAcademicosVector.size(); i += 4) {
            int codigoSnies = std::stoi(programasAcademicosVector[i][0]);
            auto it = programasAcademicos.find(codigoSnies);

            if (it == programasAcademicos.end() && esPrimeraLectura) {
                auto programaAcademico = std::make_unique<ProgramaAcademico>();

                try {
                    programaAcademico->setCodigoDeLaInstitucion(codigoSnies);
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
                } catch (const std::exception& ex) {
                    std::cerr << "Error al procesar los datos del programa: " << ex.what() << std::endl;
                    continue;
                }

                programasAcademicos.emplace(codigoSnies, programaAcademico.release());
            }
        }
    };

    procesarArchivo(rutaAdmitidos, ano1, true);
    procesarArchivo(rutaAdmitidos, ano2, false);
    procesarArchivo(rutaGraduados, ano1, false);
    procesarArchivo(rutaGraduados, ano2, false);
    procesarArchivo(rutaInscritos, ano1, false);
    procesarArchivo(rutaInscritos, ano2, false);
    procesarArchivo(rutaMatriculados, ano1, false);
    procesarArchivo(rutaMatriculados, ano2, false);
    procesarArchivo(rutaMatriculadosPrimerSemestre, ano1, false);
    procesarArchivo(rutaMatriculadosPrimerSemestre, ano2, false);

    try {
        bool archivoCreado = gestorCsvObj.crearArchivo(rutaOutput, programasAcademicos, etiquetasColumnas);
        std::cout << "Archivo creado: " << archivoCreado << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error al crear archivo de salida: " << ex.what() << std::endl;
    }
}

void SNIESController::procesarNuevoPrograma(const std::vector<std::vector<std::string>>& programasAcademicosVector, size_t i, int codigoSnies)
{
    auto programaAcademico = std::make_unique<ProgramaAcademico>();
    try {
        programaAcademico->setCodigoDeLaInstitucion(codigoSnies);
    } catch (const std::exception& ex) {
        std::cerr << "Error al convertir el código de la institución: " << ex.what() << std::endl;
        return;
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
        Consolidado* consolidado = programaAcademico->getConsolidado(m);
        if (consolidado != nullptr) {
            consolidado->setGraduados(std::stoi(programasAcademicosVector[i + m][1]));
        }
    }
    programasAcademicos.emplace(codigoSnies, programaAcademico.release());
}

void SNIESController::actualizarConsolidadosExistentes(ProgramaAcademico* programaAcademico, const std::vector<std::vector<std::string>>& programasAcademicosVector, size_t i) const
{
    for (int m = 0; m < 4; ++m) {
        Consolidado* consolidado = programaAcademico->getConsolidado(m);
        if (consolidado != nullptr) {
            consolidado->setGraduados(std::stoi(programasAcademicosVector[i + m][1]));
        }
    }
}

std::vector<int> SNIESController::leerCodigosSnies() const {
    try {
        return gestorCsvObj.leerProgramasCsv(rutaProgramasCSV);
    } catch (const std::exception& ex) {
        std::cerr << "Error al leer programas CSV: " << ex.what() << std::endl;
        return {};
    }
}

std::vector<std::vector<std::string>> SNIESController::leerDatosPrimera(std::string_view ano1, const std::vector<int>& codigosSnies) const {
    try {
        return gestorCsvObj.leerArchivoPrimera(rutaAdmitidos, std::string(ano1), codigosSnies);
    } catch (const std::exception& ex) {
        std::cerr << "Error al leer datos: " << ex.what() << std::endl;
        return {};
    }
}

void SNIESController::buscarProgramas(bool flag, std::string_view palabraClave, int idComparacion) const {
    std::list<ProgramaAcademico*> listaProgramas;
    for (const auto& [codigoSnies, programa] : programasAcademicos) {
        std::string nombrePrograma = programa->getProgramaAcademico();
        int idFormacion = programa->getIdNivelDeFormacion();

        if (nombrePrograma.find(palabraClave) != std::string::npos && idFormacion == idComparacion) {
            listaProgramas.push_back(programa);
            std::cout << programa->getCodigoSniesDelPrograma() << ";"
                      << programa->getProgramaAcademico() << ";"
                      << programa->getCodigoDeLaInstitucion() << ";"
                      << programa->getInstitucionDeEducacionSuperiorIes() << ";"
                      << programa->getMetodologia() << std::endl;
        }
    }

    if (flag) {
        gestorCsvObj.crearArchivoBuscados(rutaOutput, listaProgramas, etiquetasColumnas);
    }
}

void SNIESController::calcularDatosExtra(bool flag) const
{
    std::vector<std::vector<std::string>> matrizFinal;
    auto matrizEtiquetas1 = generarMatrizEtiquetas1();
    auto matrizEtiquetas2 = generarMatrizEtiquetas2();
    auto matrizEtiquetas3 = generarMatrizEtiquetas3();

    int sumaPrimerAno = 0;
    int sumaSegundoAno = 0;

    procesarDatos(sumaPrimerAno, sumaSegundoAno, flag);

    if (flag) {
        gestorCsvObj.crearArchivoExtra(rutaOutput, matrizFinal);
    }
}

std::vector<std::vector<std::string>> SNIESController::generarMatrizEtiquetas1() const {
    std::vector<std::vector<std::string>> matrizEtiquetas1;
    std::vector<std::string> etiquetas1 = {
        "Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual) Primer año",
        "Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual)"
    };
    matrizEtiquetas1.push_back(etiquetas1);
    return matrizEtiquetas1;
}

std::vector<std::vector<std::string>> SNIESController::generarMatrizEtiquetas2() const {
    std::vector<std::vector<std::string>> matrizEtiquetas2;
    std::vector<std::string> etiquetas2 = {
        "Codigo Snies", "Nombre del Programa", "Nombre del Institucion",
        "Diferencial porcentual anual de NEOS"
    };
    matrizEtiquetas2.push_back(etiquetas2);
    return matrizEtiquetas2;
}

std::vector<std::vector<std::string>> SNIESController::generarMatrizEtiquetas3() const {
    std::vector<std::vector<std::string>> matrizEtiquetas3;
    std::vector<std::string> etiquetas3 = {
        "Codigo Snies", " Nombre del Programa sin NEOS en los ultimos 3 semestres"
    };
    matrizEtiquetas3.push_back(etiquetas3);
    return matrizEtiquetas3;
}

void SNIESController::procesarDatos(int& sumaPrimerAno, int& sumaSegundoAno, bool flag) const
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
        int neosPrimerAno = 0;
        int neosSegundoAno = 0;
        int diferenciaNeos = 0;
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

        int sumaNeosPrimerSemestre = 0;
        int sumaNeosSegundoSemestre = 0;
        int sumaNeosTercerSemestre = 0;
        int sumaNeosCuartoSemestre = 0;
        for (int i = 0; i < 4; ++i)
        {
            sumaNeosPrimerSemestre += programa->getConsolidado(i)->getMatriculadosPrimerSemestre() + programa->getConsolidado(i + 2)->getMatriculadosPrimerSemestre();
            sumaNeosSegundoSemestre += programa->getConsolidado(i + 2)->getMatriculadosPrimerSemestre() + programa->getConsolidado(i + 4)->getMatriculadosPrimerSemestre();
            sumaNeosTercerSemestre += programa->getConsolidado(i + 4)->getMatriculadosPrimerSemestre() + programa->getConsolidado(i + 6)->getMatriculadosPrimerSemestre();
            sumaNeosCuartoSemestre += programa->getConsolidado(i + 6)->getMatriculadosPrimerSemestre() + programa->getConsolidado(i + 8)->getMatriculadosPrimerSemestre();
        }

        if ((sumaNeosPrimerSemestre == 0 && sumaNeosSegundoSemestre == 0 && sumaNeosTercerSemestre == 0) || (sumaNeosSegundoSemestre == 0 && sumaNeosTercerSemestre == 0 && sumaNeosCuartoSemestre == 0))
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