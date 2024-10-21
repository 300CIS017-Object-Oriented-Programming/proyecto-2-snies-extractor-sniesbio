#ifndef GESTOR_CSV_H
#define GESTOR_CSV_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
#include "ProgramaAcademico.h"
#include "Consolidado.h"

class GestorCsv
{
public:
    GestorCsv() = default;
    std::vector<int> leerProgramasCsv(const std::string &ruta) const;
    std::vector<std::vector<std::string>> leerArchivoComun(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies, int numColumnas, int filasAdicionales) const;
    std::vector<std::vector<std::string>> leerArchivoPrimera(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;
    std::vector<std::vector<std::string>> leerArchivoSegunda(const std::string &rutaBase, const std::string &ano, const std::vector<int> &codigosSnies) const;
    std::vector<std::vector<std::string>> leerArchivo(std::string &rutaBase, std::string &ano, std::vector<int> &codigosSnies, int colmunaCodigoSnies) const;
    bool crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapadeProgramasAcademicos, const std::vector<std::string> &etiquetasColumnas) const;
    bool crearArchivoBuscados(const std::string &ruta, std::list<ProgramaAcademico *> &programasBuscados, std::vector<std::string> etiquetasColumnas) const;
    bool crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const;
    void agregarFilasAdicionales(std::ifstream &archivo, std::vector<std::vector<std::string>> &matrizResultado, int numFilas, int numColumnas) const;

private:
    std::vector<std::string> leerFila(std::ifstream &archivo, int numColumnas) const;
    bool verificarPrograma(const std::vector<std::string> &vectorFila, const std::vector<int> &codigosSnies) const;
    bool verificarPrograma(const std::vector<std::string> &vectorFila, const std::vector<int> &codigosSnies, int columnaCodigoSnies) const;
    void leerFilasRestantes(std::ifstream &archivo, std::vector<std::vector<std::string>> &matrizResultado, int numFilas) const;
    void imprimirFila(std::ofstream &archivo, const std::vector<std::string> &fila) const;
};

#endif // GESTOR_CSV_H