#include "View.h"
#include "Settings.h"
#include <iostream>
#include <utility>
#include "Settings.h"

View::View() {
    controlador = SNIESController(Settings::PROGRAMAS_FILTRAR_FILE_PATH, Settings::ADMITIDOS_FILE_PATH,
                                  Settings::MATRICULADOS_FILE_PATH, Settings::INSCRITOS_FILE_PATH,
                                  Settings::MATRICULADOS_FILE_PATH, Settings::MATRICULADOS_FILE_PATH,
                                  "C:/SNIES_EXTRACTOR/outputs/");
}

// Metodo para mostrar la pantalla de bienvenida
bool View::mostrarPantallaBienvenido() {
    bool parametrizacionExitosa = false;

    std::cout << "Bienvenido al SNIES-Extractor!" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Recuerde que para el correcto funcionamiento del programa debió haber parametrizado..." << std::endl;
    std::cout << "Si ya hizo esto, escriba 'Y', de lo contrario 'N', y Enter: " << std::endl;
    char userAnswer;
    std::cin >> userAnswer;
    userAnswer = static_cast<char>(std::tolower(static_cast<unsigned char>(userAnswer)));

    if (userAnswer == 'y') {
        parametrizacionExitosa = true;
        auto [anio1, anio2] = obtenerRangoDeAnios();  // Función auxiliar para obtener los años
        controlador.procesarDatosCsv(anio1, anio2);
        std::cout << "Datos procesados con éxito!" << std::endl;
    }
    return parametrizacionExitosa;
}

// Función auxiliar para obtener los años y validarlos
std::pair<std::string, std::string> View::obtenerRangoDeAnios() const {
    std::string anio1;
    std::string anio2;
    std::cout << "Escriba el primer año de búsqueda: ";
    std::cin >> anio1;
    while (!isConvertibleToInt(anio1)) {
        std::cout << "El valor ingresado fue inválido. Ingrese nuevamente: ";
        std::cin >> anio1;
    }

    std::cout << "Escriba el segundo año de búsqueda: ";
    std::cin >> anio2;
    while (!isConvertibleToInt(anio2)) {
        std::cout << "El valor ingresado fue inválido. Ingrese nuevamente: ";
        std::cin >> anio2;
    }

    // Asegurarnos de que anio2 sea mayor o igual a anio1
    if (std::stoi(anio2) < std::stoi(anio1)) {
        std::swap(anio1, anio2);
    }

    return {anio1, anio2};
}

// Método para salir del programa
void View::salir() const {
    std::cout << "Cerrando programa..." << std::endl;
    std::cout << "Recuerde revisar la carpeta de outputs para los archivos exportados" << std::endl;
}

// Mostrar datos adicionales
void View::mostrarDatosExtra() {
    char opcionYN;
    std::cout << "Desea convertir los datos a un archivo CSV? (Y/N): ";
    std::cin >> opcionYN;
    opcionYN = static_cast<char>(std::tolower(static_cast<unsigned char>(opcionYN)));

    if (opcionYN == 'y') {
        controlador.calcularDatosExtra(true);
    } else if (opcionYN == 'n') {
        controlador.calcularDatosExtra(false);
    } else {
        std::cerr << "Opción inválida." << std::endl;
    }
}

// Búsqueda por palabra clave y formación
void View::buscarPorPalabraClaveYFormacion() {
    char opcionYN = 'y';
    while (opcionYN == 'y') {
        std::cout << "Desea hacer una búsqueda por palabra clave del nombre del programa? (Y/N): ";
        std::cin >> opcionYN;
        opcionYN = static_cast<char>(std::tolower(static_cast<unsigned char>(opcionYN)));

        if (opcionYN == 'y') {
            char opcionCSV;
            std::cout << "Deseas convertir los datos a un CSV? (Y/N): ";
            std::cin >> opcionCSV;
            bool convertirCSV = std::tolower(opcionCSV) == 'y';

            std::string palabraClave;
            std::cout << "Escriba la palabra clave para buscar los programas: ";
            std::cin >> palabraClave;

            int idFormacionAcademica;
            std::cout << "Seleccione un nivel de formación para filtrar (1-10, excluyendo 9): ";
            std::cin >> idFormacionAcademica;
            while ((idFormacionAcademica > 10) || (idFormacionAcademica == 9) || (idFormacionAcademica < 1)) {
                std::cout << "Seleccione una opción válida entre 1-10, excluyendo 9: ";
                std::cin >> idFormacionAcademica;
            }

            controlador.buscarProgramas(convertirCSV, std::string_view(palabraClave), idFormacionAcademica);
        }
    }
}

// Metodo privado para verificar si un string es convertible a entero
bool View::isConvertibleToInt(const std::string &str) const {
    try {
        std::size_t pos;
        std::stoi(str, &pos);
        return pos == str.length();
    } catch (const std::invalid_argument & /*e*/) {
        return false;
    } catch (const std::out_of_range & /*e*/) {
        return false;
    }
}