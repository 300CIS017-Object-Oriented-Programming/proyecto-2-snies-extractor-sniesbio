#include "View.h"
/**
 * @file main.cpp
 * @brief Punto de entrada principal para la aplicación.
 *
 * Este archivo contiene la función principal que inicializa y ejecuta el menú de la aplicación.
 */

int main()
{
    /* Esta función inicializa el menú de la aplicación, muestra la pantalla de bienvenida y
    dependiendo de la respuesta del usuario, muestra datos adicionales y permite la búsqueda
    por palabra clave y formación */

    View menu;
    if (bool archivosParametrizados = menu.mostrarPantallaBienvenido(); archivosParametrizados)
    {
        menu.mostrarDatosExtra();
        menu.buscarPorPalabraClaveYFormacion();
    }
    menu.salir();
    return 0;
}