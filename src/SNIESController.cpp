#include "SNIESController.h"
#include <memory>  // Para std::unique_ptr
#include <utility> // Para std::make_unique

using namespace std;

SNIESController::SNIESController(const string &nuevaRutaProgramasCSV, const string &nuevaRutaAdmitidos, const string &nuevaRutaGraduados, const string &nuevaRutaInscritos, const string &nuevaRutaMatriculadosc, const string &nuevaRutaMatriculadosPrimerSemestre, const string &nuevaRutaOutput)
{
    gestorCsvObj = GestorCsv();
    rutaProgramasCSV = nuevaRutaProgramasCSV;
    rutaAdmitidos = nuevaRutaAdmitidos;
    rutaGraduados = nuevaRutaGraduados;
    rutaInscritos = nuevaRutaInscritos;
    rutaMatriculados = nuevaRutaMatriculadosc;
    rutaMatriculadosPrimerSemestre = nuevaRutaMatriculadosPrimerSemestre;
    rutaOutput = nuevaRutaOutput;
}

SNIESController::~SNIESController()
{
    for (auto &pair : programasAcademicos)
    {
        delete pair.second;
    }
}

void SNIESController::procesarDatosCsv(const string &ano1, const string &ano2)
{
    vector<int> codigosSnies = gestorCsvObj.leerProgramasCsv(rutaProgramasCSV);
    vector<vector<string>> programasAcademicosVector = gestorCsvObj.leerArchivoPrimera(rutaAdmitidos, ano1, codigosSnies);
    etiquetasColumnas = programasAcademicosVector[0];

    for (size_t i = 1; i < programasAcademicosVector.size(); i += 4)
    {
        auto programaAcademico = make_unique<ProgramaAcademico>();

        programaAcademico->setCodigoDeLaInstitucion(stoi(programasAcademicosVector[i][0]));
        programaAcademico->setIesPadre(stoi(programasAcademicosVector[i][1]));
        programaAcademico->setInstitucionDeEducacionSuperiorIes(programasAcademicosVector[i][2]);
        programaAcademico->setPrincipalOSeccional(programasAcademicosVector[i][3]);
        programaAcademico->setIdSectorIes(stoi(programasAcademicosVector[i][4]));
        programaAcademico->setSectorIes(programasAcademicosVector[i][5]);
        programaAcademico->setIdCaracter(stoi(programasAcademicosVector[i][6]));
        programaAcademico->setCaracterIes(programasAcademicosVector[i][7]);
        programaAcademico->setCodigoDelDepartamentoIes(stoi(programasAcademicosVector[i][8]));
        programaAcademico->setDepartamentoDeDomicilioDeLaIes(programasAcademicosVector[i][9]);
        programaAcademico->setCodigoDelMunicipioIes(stoi(programasAcademicosVector[i][10]));
        programaAcademico->setMunicipioDeDomicilioDeLaIes(programasAcademicosVector[i][11]);
        programaAcademico->setCodigoSniesDelPrograma(stoi(programasAcademicosVector[i][12]));
        programaAcademico->setProgramaAcademico(programasAcademicosVector[i][13]);
        programaAcademico->setIdNivelAcademico(stoi(programasAcademicosVector[i][14]));
        programaAcademico->setNivelAcademico(programasAcademicosVector[i][15]);
        programaAcademico->setIdNivelDeFormacion(stoi(programasAcademicosVector[i][16]));
        programaAcademico->setNivelDeFormacion(programasAcademicosVector[i][17]);
        programaAcademico->setIdMetodologia(stoi(programasAcademicosVector[i][18]));
        programaAcademico->setMetodologia(programasAcademicosVector[i][19]);
        programaAcademico->setIdArea(stoi(programasAcademicosVector[i][20]));
        programaAcademico->setAreaDeConocimiento(programasAcademicosVector[i][21]);
        programaAcademico->setIdNucleo(stoi(programasAcademicosVector[i][22]));
        programaAcademico->setNucleoBasicoDelConocimientoNbc(programasAcademicosVector[i][23]);
        programaAcademico->setIdCineCampoAmplio(stoi(programasAcademicosVector[i][24]));
        programaAcademico->setDescCineCampoAmplio(programasAcademicosVector[i][25]);
        programaAcademico->setIdCineCampoEspecifico(stoi(programasAcademicosVector[i][26]));
        programaAcademico->setDescCineCampoEspecifico(programasAcademicosVector[i][27]);
        programaAcademico->setIdCineCodigoDetallado(stoi(programasAcademicosVector[i][28]));
        programaAcademico->setDescCineCodigoDetallado(programasAcademicosVector[i][29]);
        programaAcademico->setCodigoDelDepartamentoPrograma(stoi(programasAcademicosVector[i][30]));
        programaAcademico->setDepartamentoDeOfertaDelPrograma(programasAcademicosVector[i][31]);
        programaAcademico->setCodigoDelMunicipioPrograma(stoi(programasAcademicosVector[i][32]));
        programaAcademico->setMunicipioDeOfertaDelPrograma(programasAcademicosVector[i][33]);

        for (int m = 0; m < 4; ++m)
        {
            auto consolidado = make_unique<Consolidado>();
            consolidado->setIdSexo(stoi(programasAcademicosVector[i + m][34]));
            consolidado->setSexo(programasAcademicosVector[i + m][35]);
            consolidado->setAno(stoi(programasAcademicosVector[i + m][36]));
            consolidado->setSemestre(stoi(programasAcademicosVector[i + m][37]));
            consolidado->setAdmitidos(stoi(programasAcademicosVector[i + m][38]));
            programaAcademico->setConsolidado(move(consolidado), m);
        }
        programasAcademicos[programaAcademico->getCodigoSniesDelPrograma()] = programaAcademico.release();
    }

    programasAcademicosVector = gestorCsvObj.leerArchivoSegunda(rutaAdmitidos, ano2, codigosSnies);

    for (size_t j = 0; j < programasAcademicosVector.size(); j += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[j][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                auto consolidado = make_unique<Consolidado>();
                consolidado->setIdSexo(stoi(programasAcademicosVector[j + m][1]));
                consolidado->setSexo(programasAcademicosVector[j + m][2]);
                consolidado->setAno(stoi(programasAcademicosVector[j + m][3]));
                consolidado->setSemestre(stoi(programasAcademicosVector[j + m][4]));
                consolidado->setAdmitidos(stoi(programasAcademicosVector[j + m][5]));
                programa->setConsolidado(move(consolidado), m + 4);
            }
        }
    }

    programasAcademicosVector = gestorCsvObj.leerArchivo(rutaGraduados, ano1, codigosSnies, 13);
    for (size_t k = 0; k < programasAcademicosVector.size(); k += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[k][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                Consolidado *consolidado = programa->getConsolidado(m);
                consolidado->setGraduados(stoi(programasAcademicosVector[k + m][1]));
            }
        }
    }

    programasAcademicosVector = gestorCsvObj.leerArchivo(rutaGraduados, ano2, codigosSnies, 13);
    for (size_t k = 0; k < programasAcademicosVector.size(); k += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[k][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                Consolidado *consolidado = programa->getConsolidado(m + 4);
                consolidado->setGraduados(stoi(programasAcademicosVector[k + m][1]));
            }
        }
    }

    programasAcademicosVector = gestorCsvObj.leerArchivo(rutaInscritos, ano1, codigosSnies, 12);
    for (size_t k = 0; k < programasAcademicosVector.size(); k += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[k][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                Consolidado *consolidado = programa->getConsolidado(m);
                consolidado->setInscritos(stoi(programasAcademicosVector[k + m][1]));
            }
        }
    }

    int columna = (ano2 == "2022") ? 12 : 13;
    programasAcademicosVector = gestorCsvObj.leerArchivo(rutaInscritos, ano2, codigosSnies, columna);
    for (size_t k = 0; k < programasAcademicosVector.size(); k += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[k][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                Consolidado *consolidado = programa->getConsolidado(m + 4);
                consolidado->setInscritos(stoi(programasAcademicosVector[k + m][1]));
            }
        }
    }

    programasAcademicosVector = gestorCsvObj.leerArchivo(rutaMatriculados, ano1, codigosSnies, 13);
    for (size_t k = 0; k < programasAcademicosVector.size(); k += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[k][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                Consolidado *consolidado = programa->getConsolidado(m);
                consolidado->setMatriculados(stoi(programasAcademicosVector[k + m][1]));
            }
        }
    }

    programasAcademicosVector = gestorCsvObj.leerArchivo(rutaMatriculados, ano2, codigosSnies, 13);
    for (size_t k = 0; k < programasAcademicosVector.size(); k += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[k][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                Consolidado *consolidado = programa->getConsolidado(m + 4);
                consolidado->setMatriculados(stoi(programasAcademicosVector[k + m][1]));
            }
        }
    }

    programasAcademicosVector = gestorCsvObj.leerArchivo(rutaMatriculadosPrimerSemestre, ano1, codigosSnies, 13);
    for (size_t k = 0; k < programasAcademicosVector.size(); k += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[k][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                Consolidado *consolidado = programa->getConsolidado(m);
                consolidado->setMatriculadosPrimerSemestre(stoi(programasAcademicosVector[k + m][1]));
            }
        }
    }

    programasAcademicosVector = gestorCsvObj.leerArchivo(rutaMatriculadosPrimerSemestre, ano2, codigosSnies, 13);
    for (size_t k = 0; k < programasAcademicosVector.size(); k += 4)
    {
        auto it = programasAcademicos.find(stoi(programasAcademicosVector[k][0]));
        if (it != programasAcademicos.end())
        {
            ProgramaAcademico *programa = it->second;

            for (int m = 0; m < 4; ++m)
            {
                Consolidado *consolidado = programa->getConsolidado(m + 4);
                consolidado->setMatriculadosPrimerSemestre(stoi(programasAcademicosVector[k + m][1]));
            }
        }
    }

    bool archivoCreado = gestorCsvObj.crearArchivo(rutaOutput, programasAcademicos, etiquetasColumnas);
    cout << archivoCreado << endl;
}

void SNIESController::buscarProgramas(bool flag, const string &palabraClave, int idComparacion)
{
    list<ProgramaAcademico *> listaProgramas;
    for (auto &pair : programasAcademicos)
    {
        ProgramaAcademico *programa = pair.second;
        string nombre = programa->getProgramaAcademico();
        int id = programa->getIdNivelDeFormacion();
        if (nombre.find(palabraClave) != string::npos && id == idComparacion)
        {
            listaProgramas.push_back(programa);
            cout << programa->getCodigoSniesDelPrograma() << ";" << programa->getProgramaAcademico() << ";" << programa->getCodigoDeLaInstitucion() << ";" << programa->getInstitucionDeEducacionSuperiorIes() << ";" << programa->getMetodologia() << endl;
        }
    }

    if (flag)
    {
        gestorCsvObj.crearArchivoBuscados(rutaOutput, listaProgramas, etiquetasColumnas);
    }
}

void SNIESController::calcularDatosExtra(bool flag)
{
    vector<vector<string>> matrizFinal;
    vector<vector<string>> matrizEtiquetas1;
    vector<vector<string>> matrizEtiquetas2;
    vector<vector<string>> matrizEtiquetas3;
    vector<string> etiquetas1 = {"Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual) Primer año", "Suma Estudiantes Matriculados de Programas Seleccionados (Presencial o Virtual)"};
    matrizEtiquetas1.push_back(etiquetas1);
    vector<string> etiquetas2 = {"Codigo Snies", "Nombre del Programa", "Nombre del Institucion", "Diferencial porcentual anual de NEOS"};
    matrizEtiquetas2.push_back(etiquetas2);
    vector<string> etiquetas3 = {"Codigo Snies", " Nombre del Programa sin NEOS en los ultimos 3 semestres"};
    matrizEtiquetas3.push_back(etiquetas3);
    vector<string> datosEtiquetas1;
    vector<string> datosEtiquetas2;
    int sumaPrimerAno = 0;
    int sumaSegundoAno = 0;

    for (map<int, ProgramaAcademico *>::iterator it = programasAcademicos.begin(); it != programasAcademicos.end(); ++it)
    {
        int neosPrimerAno = 0;
        int neosSegundoAno = 0;
        int diferenciaNeos = 0;
        ProgramaAcademico *programa = it->second;
        int idMetodologiaBuscada = programa->getIdMetodologia();
        if (idMetodologiaBuscada == 1 || idMetodologiaBuscada == 3)
        {
            for (int i = 0; i < 4; ++i)
            {
                Consolidado *consolidado = programa->getConsolidado(i);
                int matriculados = consolidado->getMatriculados();
                sumaPrimerAno += matriculados;
            }

            for (int i = 0; i < 4; ++i)
            {
                Consolidado *consolidado = programa->getConsolidado(i + 4);
                int matriculados = consolidado->getMatriculados();
                sumaSegundoAno += matriculados;
            }
        }
        for (int i = 0; i < 4; ++i)
        {
            Consolidado *consolidado = programa->getConsolidado(i);
            int numNeos = consolidado->getMatriculadosPrimerSemestre();
            neosPrimerAno += numNeos;
        }

        for (int i = 0; i < 4; ++i)
        {
            Consolidado *consolidado = programa->getConsolidado(i + 4);
            int numNeos = consolidado->getMatriculadosPrimerSemestre();
            neosSegundoAno += numNeos;
        }

        if (neosPrimerAno != 0)
        {
            diferenciaNeos = ((neosSegundoAno - neosPrimerAno) * 100) / neosPrimerAno;
        }
        else
        {
            diferenciaNeos = 0;
        }
        datosEtiquetas2 = {to_string(programa->getCodigoSniesDelPrograma()), programa->getProgramaAcademico(), programa->getInstitucionDeEducacionSuperiorIes(), to_string(diferenciaNeos)};
        matrizEtiquetas2.push_back(datosEtiquetas2);
        int SumaNeosPrimerSemestre;
        int SumaNeosSegundoSemestre;
        int SumaNeosTercerSemestre;
        int SumaNeosCuartoSemestre;
        for (int i = 0; i < 4; ++i)
        {
            Consolidado *consolidados[8];
            if (i == 0)
            {
                consolidados[0] = programa->getConsolidado(i);
                consolidados[1] = programa->getConsolidado(i + 2);
                int neosHombres = consolidados[0]->getMatriculadosPrimerSemestre();
                int neosMujeres = consolidados[1]->getMatriculadosPrimerSemestre();
                SumaNeosPrimerSemestre = neosHombres + neosMujeres;
            }
            else if (i == 1)
            {
                consolidados[2] = programa->getConsolidado(i);
                consolidados[3] = programa->getConsolidado(i + 2);
                int neosHombres = consolidados[2]->getMatriculadosPrimerSemestre();
                int neosMujeres = consolidados[3]->getMatriculadosPrimerSemestre();
                SumaNeosSegundoSemestre = neosHombres + neosMujeres;
            }
            else if (i == 2)
            {
                consolidados[4] = programa->getConsolidado(i + 2);
                consolidados[5] = programa->getConsolidado(i + 4);
                int neosHombres = consolidados[4]->getMatriculadosPrimerSemestre();
                int neosMujeres = consolidados[5]->getMatriculadosPrimerSemestre();
                SumaNeosTercerSemestre = neosHombres + neosMujeres;
            }
            else if (i == 3)
            {
                consolidados[6] = programa->getConsolidado(i + 2);
                consolidados[7] = programa->getConsolidado(i + 4);
                int neosHombres = consolidados[6]->getMatriculadosPrimerSemestre();
                int neosMujeres = consolidados[7]->getMatriculadosPrimerSemestre();
                SumaNeosCuartoSemestre = neosHombres + neosMujeres;
            }
        }

        if ((SumaNeosPrimerSemestre == 0 && SumaNeosSegundoSemestre == 0 && SumaNeosTercerSemestre == 0) || (SumaNeosSegundoSemestre == 0 && SumaNeosTercerSemestre == 0 && SumaNeosCuartoSemestre == 0))
        {
            etiquetas3 = {to_string(programa->getCodigoSniesDelPrograma()),
                          programa->getProgramaAcademico()};
        }
    }
    etiquetas1 = {to_string(sumaPrimerAno), to_string(sumaSegundoAno)};
    matrizEtiquetas1.push_back(etiquetas1);
    matrizFinal.insert(matrizFinal.end(), matrizEtiquetas1.begin(), matrizEtiquetas1.end());
    matrizFinal.insert(matrizFinal.end(), matrizEtiquetas2.begin(), matrizEtiquetas2.end());
    matrizFinal.insert(matrizFinal.end(), matrizEtiquetas3.begin(), matrizEtiquetas3.end());

    for (const auto &fila : matrizFinal)
    {
        for (size_t i = 0; i < fila.size(); ++i)
        {
            cout << fila[i];
            if (i < fila.size() - 1)
            {
                cout << ";";
            }
        }
        cout << endl;
    }

    if (flag)
    {
        bool creado;
        creado = gestorCsvObj.crearArchivoExtra(rutaOutput, matrizFinal);
    }
}