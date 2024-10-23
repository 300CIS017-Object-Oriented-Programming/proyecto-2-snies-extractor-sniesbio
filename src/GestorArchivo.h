#ifndef GESTORARCHIVO_H
#define GESTORARCHIVO_H

#include <map>
#include <string>
#include <vector>
#include <list>
#include "ProgramaAcademico.h"

class GestorArchivo {
public:
    // Destructor
    virtual ~GestorArchivo() = default;

    // Crear un archivo con los datos de los programas académicos
    virtual bool crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const = 0;

    // Crear un archivo con los datos de los programas buscados
    virtual bool crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const = 0;

    // Crear un archivo con datos adicionales
    virtual bool crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const = 0;

protected:
    // Método de ayuda para manejar errores comunes
    void manejarErrores(const std::string& mensaje) const;

private:
    std::vector<std::string> datos;
};

#endif // GESTORDATOS_H
