#ifndef VIEW_H
#define VIEW_H
#include "SNIESController.h"
#include <string_view>

class View
{
private:
    SNIESController controlador;
    std::string pedirAno(const std::string& mensaje)const;
    void verificarAnios(std::string &anio1, std::string &anio2)const;

public:
    View();
    ~View() = default;

    bool mostrarPantallaBienvenido();
    void mostrarDatosExtra();
    void buscarPorPalabraClaveYFormacion();
    void salir()const;
    bool esConvertibleAEntero(const std::string &str)const;
};

#endif