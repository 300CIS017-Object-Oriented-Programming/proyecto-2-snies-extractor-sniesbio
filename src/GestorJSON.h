#ifndef GESTORJSON_H
#define GESTORJSON_H

#include "GestorArchivo.h"
#include <map>
#include <list>
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

/**
 * @class GestorJSON
 * @brief Clase hija que gestiona la creación de archivos en formato JSON.
 */
class GestorJSON : public GestorArchivo {
public:
    // Crear un archivo JSON con los datos de los programas académicos
    bool crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const override;

    // Crear un archivo JSON con los datos de los programas buscados
    bool crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const override;

    // Crear un archivo JSON con datos adicionales
    bool crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const override;

private:
    // Utiliza el método de la clase base para manejar errores
    using GestorArchivo::manejarErrores;
};

#endif // GESTORJSON_H
