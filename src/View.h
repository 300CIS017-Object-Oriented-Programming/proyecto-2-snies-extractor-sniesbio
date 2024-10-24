#ifndef VIEW_H
#define VIEW_H
#include "SNIESController.h"
#include <cctype>
#include <string>

class View
{
private:
    SNIESController controlador;
    bool isConvertibleToInt(const std::string &str) const;
    std::pair<std::string, std::string> obtenerRangoDeAnios() const;

public:
    View();
    ~View() = default;

    bool mostrarPantallaBienvenido();
    void mostrarDatosExtra();
    void buscarPorPalabraClaveYFormacion();
    void salir() const;
};

#endif