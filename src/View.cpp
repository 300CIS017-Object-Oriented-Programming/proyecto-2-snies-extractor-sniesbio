#include "View.h"
#include <stdexcept>
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>

View::View()
{
    std::ifstream configFile("config.txt");
    if (!configFile.is_open())
    {
        throw std::ios_base::failure("No se pudo abrir el archivo de configuración.");
    }

    std::string line;
    std::map<std::string, std::string, std::less<>> configMap;

    while (std::getline(configFile, line))
    {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '='))
        {
            std::string value;
            if (std::getline(is_line, value))
            {
                configMap[key] = value;
            }
        }
    }

    std::string ruta1 = configMap["rutaProgramas"];
    std::string ruta2 = configMap["rutaAdmitidos"];
    std::string ruta3 = configMap["rutaGraduados"];
    std::string ruta4 = configMap["rutaInscritos"];
    std::string ruta5 = configMap["rutaMatriculados"];
    std::string ruta6 = configMap["rutaMatriculadosPrimerSemestre"];
    std::string ruta7 = configMap["rutaOutput"];
    controlador = SNIESController(ruta1, ruta2, ruta3, ruta4, ruta5, ruta6, ruta7);
}


bool View::mostrarPantallaBienvenido()
{
    char userAnswer;
    std::cout << "Bienvenido al SNIES-Extractor!" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Recuerde que para el correcto funcionamiento del programa debió parametrizar "
              << "la carpeta SNIES_EXTRACTOR en el disco C:" << std::endl;
    std::cout << "Si ya hizo esto, escriba 'Y', de lo contrario 'N': " << std::endl;

    std::cin >> userAnswer;
    userAnswer = static_cast<char>(tolower(userAnswer));

    if (userAnswer == 'y')
    {
        std::string anio1 = pedirAno("Escriba el primer año de búsqueda: ");
        std::string anio2 = pedirAno("Escriba el segundo año de búsqueda: ");

        verificarAnios(anio1, anio2);

        std::cout << "Procesando datos..." << std::endl;
        controlador.procesarDatosCsv(anio1, anio2);
        std::cout << "Datos procesados con éxito!" << std::endl;

        return true;
    }

    std::cout << "Recuerde parametrizar los archivos CSV antes de continuar." << std::endl;
    return false;
}

void View::mostrarDatosExtra()
{
    char opcionYN;
    std::cout << "Desea convertir los datos a un archivo CSV? (Y/N): " << std::endl;
    std::cin >> opcionYN;
    opcionYN = static_cast<char>(tolower(opcionYN));

    controlador.calcularDatosExtra(opcionYN == 'y');
}

void View::buscarPorPalabraClaveYFormacion()
{
    char opcionYN = 'y';
    std::string palabraClave;
    int idFormacionAcademica;

    while (opcionYN == 'y')
    {
        std::cout << "Desea hacer una búsqueda por palabra clave? (Y/N): " << std::endl;
        std::cin >> opcionYN;
        opcionYN = static_cast<char>(tolower(opcionYN));

        if (opcionYN == 'y')
        {
            std::cout << "Escriba la palabra clave: " << std::endl;
            std::cin >> palabraClave;

            std::cout << "Seleccione un nivel de formación (1-10, excluyendo el 9): " << std::endl;
            std::cin >> idFormacionAcademica;

            while (idFormacionAcademica > 10 || idFormacionAcademica == 9 || idFormacionAcademica < 1)
            {
                std::cout << "Seleccione una opción válida (1-10, excluyendo el 9): " << std::endl;
                std::cin >> idFormacionAcademica;
            }

            bool convertirCSV = false;
            std::cout << "Desea convertir los resultados a CSV? (Y/N): " << std::endl;
            char opcionCSV;
            std::cin >> opcionCSV;
            convertirCSV = (tolower(opcionCSV) == 'y');

            controlador.buscarProgramas(convertirCSV, palabraClave, idFormacionAcademica);
        }
    }
}

std::string View::pedirAno(const std::string& mensaje)const
{
    std::string anio;
    do {
        std::cout << mensaje;
        std::cin >> anio;
    } while (!esConvertibleAEntero(anio));

    return anio;
}

void View::verificarAnios(std::string &anio1, std::string &anio2) const
{
    if (std::stoi(anio2) < std::stoi(anio1))
    {
        std::swap(anio1, anio2);
    }
}

bool View::esConvertibleAEntero(const std::string &str)const
{
    try
    {
        std::size_t pos;
        std::stoi(str, &pos);
        return pos == str.length();
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }
    catch (const std::out_of_range &)
    {
        return false;
    }
}

void View::salir()const
{
    std::cout << "Cerrando programa... Recuerde revisar los archivos exportados." << std::endl;
}