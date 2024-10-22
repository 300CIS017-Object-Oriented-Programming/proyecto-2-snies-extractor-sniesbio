#include "View.h"

int main()
{
    View menu;
    if (bool archivosParametrizados = menu.mostrarPantallaBienvenido(); archivosParametrizados)
    {
        menu.mostrarDatosExtra();
        menu.buscarPorPalabraClaveYFormacion();
    }
    menu.salir();
    return 0;
}