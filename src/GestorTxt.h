#ifndef GESTORTXT_H
#define GESTORTXT_H

#include "GestorArchivo.h"
#include <map>
#include <list>
#include <vector>
#include <string>

/**
 * @class GestorTXT
 * @brief Clase hija que gestiona la creación de archivos en formato TXT.
 */
class GestorTXT : public GestorArchivo {
public:
    // Crear un archivo TXT con los datos de los programas académicos
    bool crearArchivo(const std::string &ruta, const std::map<int, ProgramaAcademico *> &mapaProgramas, const std::vector<std::string> &etiquetasColumnas) const override;

    // Crear un archivo TXT con los datos de los programas buscados
    bool crearArchivoBuscados(const std::string &ruta, const std::list<ProgramaAcademico *> &programasBuscados, const std::vector<std::string> &etiquetasColumnas) const override;

    // Crear un archivo TXT con datos adicionales
    bool crearArchivoExtra(const std::string &ruta, const std::vector<std::vector<std::string>> &datosAImprimir) const override;

private:
    // Utiliza el método de la clase base para manejar errores
    using GestorArchivo::manejarErrores;
};

#endif // GESTORTXT_H
