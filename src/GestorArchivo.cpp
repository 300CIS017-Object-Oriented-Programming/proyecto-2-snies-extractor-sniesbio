#include "GestorArchivo.h"
#include <iostream>
#include <fstream>

/**
 * @class GestorArchivo
 * @brief Esta clase gestiona la lectura y escritura de archivos de texto. Clase padre
 */
// Método de ayuda para manejar errores comunes
void GestorArchivo::manejarErrores(const std::string& mensaje) {
    std::cerr << "Error: " << mensaje << std::endl;

    std::ofstream logFile("error_log.txt", std::ios::app); // Abrir en modo append para no sobrescribir
    if (logFile) {
        logFile << "Error: " << mensaje << std::endl;
    } else {
        std::cerr << "No se pudo abrir el arc   hivo de log para registrar el error." << std::endl;
    }
    logFile.close();

    // Lanza una excepción para manejo crítico si es necesario
    throw std::runtime_error(mensaje);
}

