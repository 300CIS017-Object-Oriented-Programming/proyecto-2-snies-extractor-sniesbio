#include "GestorCsv.h"
// FIXME: LA LECTURA DE ARCHIVOS CON GETLINE FUNCIONA HORRIBLEMENTE, NO TENEMOS IDEA DE POR QUÉ
vector<int> GestorCsv::leerProgramasCsv(string &ruta) const
{
    vector<int> codigosSniesRetorno;
    ifstream archivoProgramasCsv(ruta);
    if (!(archivoProgramasCsv.is_open()))
    {
        cout << "Archivo " << ruta << " no se pudo abrir correctamente" << endl;
    }
    else
    {
        string linea;
        string dato;
        // Mantenimiento (Revisión): Se puede mejorar la lectura de archivos con getline y
        // No debería saltarse la primera linea para así determinar qué está leyendo.
        // Saltarse la primera linea
        getline(archivoProgramasCsv, linea);
        // Leer los programas
        while (getline(archivoProgramasCsv, linea))
        {
            stringstream streamLinea(linea);
            getline(streamLinea, dato, ';');
            // Manteniemiento: Se puede mejorar la forma de leer los datos de la línea y
            // los nombres de los métodos y variables.
            codigosSniesRetorno.push_back(stoi(dato));
        }
    }
    archivoProgramasCsv.close();
    return codigosSniesRetorno;
}

// Complejidad: Este metodo tiene una alta complejidad ciclomática y computacional, reducir en metodos más pequeños
// Estructuras de control anidadas profundamente.
vector<string> GestorCsv::leerFila(ifstream &archivo, int numColumnas) const
{
    vector<string> vectorFila(numColumnas);
    string fila;
    string dato;
    stringstream streamFila;

    if (getline(archivo, fila))
    {
        streamFila = stringstream(fila);
        int columna = 0;
        while (getline(streamFila, dato, ';') && columna < numColumnas)
        {
            vectorFila[columna] = dato;
            columna++;
        }
    }

    return vectorFila;
}

bool GestorCsv::verificarPrograma(const vector<string> &vectorFila, const vector<int> &codigosSnies) const
{
    if (vectorFila[12] != "Sin programa especifico")
    {
        return find(codigosSnies.begin(), codigosSnies.end(), stoi(vectorFila[12])) != codigosSnies.end();
    }
    return false;
}

void GestorCsv::leerFilasRestantes(ifstream &archivo, vector<vector<string>> &matrizResultado, int numFilas) const
{
    for (int j = 0; j < numFilas; j++)
    {
        matrizResultado.push_back(leerFila(archivo, 39));
    }
}

vector<vector<string>> GestorCsv::leerArchivoPrimera(string &rutaBase, string &ano, vector<int> &codigosSnies) const
{
    vector<vector<string>> matrizResultado;
    string rutaCompleta = rutaBase + ano + ".csv";
    ifstream archivoPrimero(rutaCompleta);

    if (!archivoPrimero.is_open())
    {
        cout << "Archivo " << rutaCompleta << " no se pudo abrir correctamente" << endl;
        return matrizResultado;
    }

    // Leer etiquetas
    matrizResultado.push_back(leerFila(archivoPrimero, 39));

    // Leer filas de datos
    while (archivoPrimero)
    {
        vector<string> vectorFila = leerFila(archivoPrimero, 13);

        if (verificarPrograma(vectorFila, codigosSnies))
        {
            matrizResultado.push_back(vectorFila);
            leerFilasRestantes(archivoPrimero, matrizResultado, 3);
        }
    }

    archivoPrimero.close();
    return matrizResultado;
}

// Complejidad: Este metodo tiene una alta complejidad ciclomática y computacional, reducir en metodos más pequeños
// Parece hacer lo mismo que el metodo leerArchivoPrimera
vector<vector<string>> GestorCsv::leerArchivoSegunda(const string &rutaBase, const string &ano, const vector<int> &codigosSnies) const
{
    vector<vector<string>> matrizResultado;
    string rutaCompleta = rutaBase + ano + ".csv";
    ifstream archivoSegundo(rutaCompleta);

    if (!archivoSegundo.is_open())
    {
        cout << "Archivo " << rutaCompleta << " no se pudo abrir correctamente" << endl;
        return matrizResultado;
    }

    // Leer etiquetas (primera fila)
    matrizResultado.push_back(leerFila(archivoSegundo, 13));

    // Leer el resto del archivo
    while (archivoSegundo)
    {
        vector<string> vectorFila = leerFila(archivoSegundo, 13);

        if (!vectorFila.empty() && verificarPrograma(vectorFila, codigosSnies))
        {
            matrizResultado.push_back(vectorFila);
            agregarFilasAdicionales(archivoSegundo, matrizResultado, 3, 13);
        }
    }

    archivoSegundo.close();
    return matrizResultado;
}

// Función para agregar filas adicionales al archivo
void GestorCsv::agregarFilasAdicionales(ifstream &archivo, vector<vector<string>> &matrizResultado, int numFilas, int numColumnas) const
{
    string fila;
    string dato;
    for (int j = 0; j < numFilas; j++)
    {
        getline(archivo, fila);
        stringstream streamFila(fila);
        vector<string> vectorFila(numColumnas);
        int columna = 0;

        while ((getline(streamFila, dato, ';')) && (columna < numColumnas))
        {
            vectorFila[columna] = dato;
            columna++;
        }
        matrizResultado.push_back(vectorFila);
    }
}


vector<vector<string>> GestorCsv::leerArchivo(string &rutaBase, string &ano, vector<int> &codigosSnies, int columnaCodigoSnies) const
{
    vector<vector<string>> matrizResultado;
    string rutaCompleta = rutaBase + ano + ".csv";
    ifstream archivo(rutaCompleta);

    if (!archivo.is_open())
    {
        cout << "Archivo " << rutaCompleta << " no se pudo abrir correctamente" << endl;
        return matrizResultado;
    }

    // Leer etiquetas
    matrizResultado.push_back(leerFila(archivo, 39));

    // Leer filas de datos
    while (archivo)
    {
        vector<string> vectorFila = leerFila(archivo, columnaCodigoSnies + 1);

        // Verificar si el programa es válido
        if (verificarPrograma(vectorFila, codigosSnies, columnaCodigoSnies))
        {
            matrizResultado.push_back(vectorFila);
            agregarFilasAdicionales(archivo, matrizResultado, 3, columnaCodigoSnies + 1);
        }
    }

    archivo.close();
    return matrizResultado;
}

// Verificar si la fila corresponde a un programa válido
bool GestorCsv::verificarPrograma(const vector<string> &vectorFila, const vector<int> &codigosSnies, int columnaCodigoSnies) const
{
    if (vectorFila[columnaCodigoSnies] != "Sin programa especifico")
    {
        return find(codigosSnies.begin(), codigosSnies.end(), stoi(vectorFila[columnaCodigoSnies])) != codigosSnies.end();
    }
    return false;
}


bool GestorCsv::crearArchivo(string &ruta, map<int, ProgramaAcademico *> &mapadeProgramasAcademicos, vector<string> etiquetasColumnas) const
{
    // Este bool nos ayudará a saber si se creo exitosamente el archivo
    bool estadoCreacion = false;
    string rutaCompleta = ruta + "resultados.csv";
    ofstream archivoResultados(rutaCompleta);
    if (archivoResultados.is_open())
    {
        // Imprimimos en el archivo las etiquetas (Primera fila)
        for (int i = 0; i < etiquetasColumnas.size(); i++)
        {
            archivoResultados << etiquetasColumnas[i] << ";";
        }
        archivoResultados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS" << endl;

        map<int, ProgramaAcademico *>::iterator it;
        // Leemos todos los programas del mapa para imprimirlos en el archivo
        for (it = mapadeProgramasAcademicos.begin(); it != mapadeProgramasAcademicos.end(); it++)
        {
            // Imprimimos cada uno de los 8 consolidados por programa
            for (int i = 0; i < 8; i++)
            {
                // Imprimimos toda la información base del programa academico
                archivoResultados << (it->second)->getCodigoDeLaInstitucion() << ";";
                archivoResultados << (it->second)->getIesPadre() << ";";
                archivoResultados << (it->second)->getInstitucionDeEducacionSuperiorIes() << ";";
                archivoResultados << (it->second)->getPrincipalOSeccional() << ";";
                archivoResultados << (it->second)->getIdSectorIes() << ";";
                archivoResultados << (it->second)->getSectorIes() << ";";
                archivoResultados << (it->second)->getIdCaracter() << ";";
                archivoResultados << (it->second)->getCaracterIes() << ";";
                archivoResultados << (it->second)->getCodigoDelDepartamentoIes() << ";";
                archivoResultados << (it->second)->getDepartamentoDeDomicilioDeLaIes() << ";";
                archivoResultados << (it->second)->getCodigoDelMunicipioIes() << ";";
                archivoResultados << (it->second)->getMunicipioDeDomicilioDeLaIes() << ";";
                archivoResultados << (it->second)->getCodigoSniesDelPrograma() << ";";
                archivoResultados << (it->second)->getProgramaAcademico() << ";";
                archivoResultados << (it->second)->getIdNivelAcademico() << ";";
                archivoResultados << (it->second)->getNivelAcademico() << ";";
                archivoResultados << (it->second)->getIdNivelDeFormacion() << ";";
                archivoResultados << (it->second)->getNivelDeFormacion() << ";";
                archivoResultados << (it->second)->getIdMetodologia() << ";";
                archivoResultados << (it->second)->getMetodologia() << ";";
                archivoResultados << (it->second)->getIdArea() << ";";
                archivoResultados << (it->second)->getAreaDeConocimiento() << ";";
                archivoResultados << (it->second)->getIdNucleo() << ";";
                archivoResultados << (it->second)->getNucleoBasicoDelConocimientoNbc() << ";";
                archivoResultados << (it->second)->getIdCineCampoAmplio() << ";";
                archivoResultados << (it->second)->getDescCineCampoAmplio() << ";";
                archivoResultados << (it->second)->getIdCineCampoEspecifico() << ";";
                archivoResultados << (it->second)->getDescCineCampoEspecifico() << ";";
                archivoResultados << (it->second)->getIdCineCodigoDetallado() << ";";
                archivoResultados << (it->second)->getDescCineCodigoDetallado() << ";";
                archivoResultados << (it->second)->getCodigoDelDepartamentoPrograma() << ";";
                archivoResultados << (it->second)->getDepartamentoDeOfertaDelPrograma() << ";";
                archivoResultados << (it->second)->getCodigoDelMunicipioPrograma() << ";";
                archivoResultados << (it->second)->getMunicipioDeOfertaDelPrograma() << ";";

                // Imprimimos la información del consolidado: (ID SEXO;SEXO;AÑO;SEMESTRE;ADMITIDOS;GRADUADOS;INSCRITOS;MATRICULADOS;NEOS)
                Consolidado *consolidadoActual = (it->second)->getConsolidado(i);
                archivoResultados << consolidadoActual->getIdSexo() << ";";
                archivoResultados << consolidadoActual->getSexo() << ";";
                archivoResultados << consolidadoActual->getAno() << ";";
                archivoResultados << consolidadoActual->getSemestre() << ";";
                archivoResultados << consolidadoActual->getAdmitidos() << ";";
                archivoResultados << consolidadoActual->getGraduados() << ";";
                archivoResultados << consolidadoActual->getInscritos() << ";";
                archivoResultados << consolidadoActual->getMatriculados() << ";";
                archivoResultados << consolidadoActual->getMatriculadosPrimerSemestre();
                // Saltamos de linea para la siguiente fila
                archivoResultados << endl;
            }
        }

        // Cambiamos el valor del booleano si logramos llegar hasta este punto
        estadoCreacion = true;
        // Imprimimos ruta donde quedo el archivo
        cout << "Archivo Creado en: " << rutaCompleta << endl;
    }

    archivoResultados.close();
    return estadoCreacion;
}

bool GestorCsv::crearArchivoBuscados(string &ruta, list<ProgramaAcademico *> &programasBuscados, vector<string> etiquetasColumnas) const
{
    // Este bool nos ayudará a saber si se creo exitosamente el archivo
    bool estadoCreacion = false;
    string rutaCompleta = ruta + "buscados.csv";
    ofstream archivoBuscados(rutaCompleta);
    if (archivoBuscados.is_open())
    {

        // Imprimimos en el archivo las etiquetas (Primera fila)
        for (int i = 0; i < etiquetasColumnas.size(); i++)
        {
            archivoBuscados << etiquetasColumnas[i] << ";";
        }
        archivoBuscados << "GRADUADOS;INSCRITOS;MATRICULADOS;NEOS" << endl;

        list<ProgramaAcademico *>::iterator it;
        // Leemos todos los programas de la lista de los programas buscados para imprimirlos
        for (it = programasBuscados.begin(); it != programasBuscados.end(); it++)
        {
            // Imprimimos los 8 consolidados del programa
            for (int i = 0; i < 8; i++)
            {
                // Imprimimos la informacion base del programa
                archivoBuscados << (*it)->getCodigoDeLaInstitucion() << ";";
                archivoBuscados << (*it)->getIesPadre() << ";";
                archivoBuscados << (*it)->getInstitucionDeEducacionSuperiorIes() << ";";
                archivoBuscados << (*it)->getPrincipalOSeccional() << ";";
                archivoBuscados << (*it)->getIdSectorIes() << ";";
                archivoBuscados << (*it)->getSectorIes() << ";";
                archivoBuscados << (*it)->getIdCaracter() << ";";
                archivoBuscados << (*it)->getCaracterIes() << ";";
                archivoBuscados << (*it)->getCodigoDelDepartamentoIes() << ";";
                archivoBuscados << (*it)->getDepartamentoDeDomicilioDeLaIes() << ";";
                archivoBuscados << (*it)->getCodigoDelMunicipioIes() << ";";
                archivoBuscados << (*it)->getMunicipioDeDomicilioDeLaIes() << ";";
                archivoBuscados << (*it)->getCodigoSniesDelPrograma() << ";";
                archivoBuscados << (*it)->getProgramaAcademico() << ";";
                archivoBuscados << (*it)->getIdNivelAcademico() << ";";
                archivoBuscados << (*it)->getNivelAcademico() << ";";
                archivoBuscados << (*it)->getIdNivelDeFormacion() << ";";
                archivoBuscados << (*it)->getNivelDeFormacion() << ";";
                archivoBuscados << (*it)->getIdMetodologia() << ";";
                archivoBuscados << (*it)->getMetodologia() << ";";
                archivoBuscados << (*it)->getIdArea() << ";";
                archivoBuscados << (*it)->getAreaDeConocimiento() << ";";
                archivoBuscados << (*it)->getIdNucleo() << ";";
                archivoBuscados << (*it)->getNucleoBasicoDelConocimientoNbc() << ";";
                archivoBuscados << (*it)->getIdCineCampoAmplio() << ";";
                archivoBuscados << (*it)->getDescCineCampoAmplio() << ";";
                archivoBuscados << (*it)->getIdCineCampoEspecifico() << ";";
                archivoBuscados << (*it)->getDescCineCampoEspecifico() << ";";
                archivoBuscados << (*it)->getIdCineCodigoDetallado() << ";";
                archivoBuscados << (*it)->getDescCineCodigoDetallado() << ";";
                archivoBuscados << (*it)->getCodigoDelDepartamentoPrograma() << ";";
                archivoBuscados << (*it)->getDepartamentoDeOfertaDelPrograma() << ";";
                archivoBuscados << (*it)->getCodigoDelMunicipioPrograma() << ";";
                archivoBuscados << (*it)->getMunicipioDeOfertaDelPrograma() << ";";

                // Imprimimos la información del consolidado: (ID SEXO;SEXO;AÑO;SEMESTRE;ADMITIDOS;GRADUADOS;INSCRITOS;MATRICULADOS;NEOS)
                Consolidado *consolidadoActual = (*it)->getConsolidado(i);
                archivoBuscados << consolidadoActual->getIdSexo() << ";";
                archivoBuscados << consolidadoActual->getSexo() << ";";
                archivoBuscados << consolidadoActual->getAno() << ";";
                archivoBuscados << consolidadoActual->getSemestre() << ";";
                archivoBuscados << consolidadoActual->getAdmitidos() << ";";
                archivoBuscados << consolidadoActual->getGraduados() << ";";
                archivoBuscados << consolidadoActual->getInscritos() << ";";
                archivoBuscados << consolidadoActual->getMatriculados() << ";";
                archivoBuscados << consolidadoActual->getMatriculadosPrimerSemestre();
                // Saltamos de linea para la siguiente fila
                archivoBuscados << endl;
            }
        }

        // Cambiamos el valor del booleano si logramos llegar hasta este punto
        estadoCreacion = true;
        // Imprimimos ruta donde quedo el archivo
        cout << "Archivo Creado en: " << rutaCompleta << endl;
    }

    archivoBuscados.close();
    return estadoCreacion;
}

bool GestorCsv::crearArchivoExtra(string &ruta, const vector<vector<string>> &datosAImprimir) const
{
    string rutaCompleta = ruta + "extras.csv";
    ofstream archivoExtra(rutaCompleta);

    if (!archivoExtra.is_open())
    {
        cout << "No se pudo abrir el archivo: " << rutaCompleta << endl;
        return false;
    }

    // Imprimir las filas en el archivo
    for (const auto &fila : datosAImprimir)
    {
        imprimirFila(archivoExtra, fila);
    }

    cout << "Archivo Creado en: " << rutaCompleta << endl;
    archivoExtra.close();
    return true;
}

// Nueva función para imprimir una fila
void GestorCsv::imprimirFila(ofstream &archivo, const vector<string> &fila) const
{
    for (size_t i = 0; i < fila.size(); ++i)
    {
        archivo << fila[i];
        if (i < fila.size() - 1)
        {
            archivo << ";";
        }
    }
    archivo << endl;
}
