#ifndef PROGRAMA_ACADEMICO_H
#define PROGRAMA_ACADEMICO_H

#include <string>
#include <vector>
#include <string_view>
#include <memory>
#include "Consolidado.h"
/**
 * @class ProgramaAcademico
 * @brief Esta clase representa un programa académico con sus respectivos datos y consolidado.
 *
 * La clase ProgramaAcademico encapsula varios atributos relacionados con los programas académicos,
 * como el código de la institución, el sector, el nivel académico, entre otros. También maneja un
 * conjunto de objetos Consolidado.
 */
class ProgramaAcademico
{
    int codigoDeLaInstitucion;
    int iesPadre;
    std::string institucionDeEducacionSuperiorIes;
    std::string principalOSeccional;
    int idSectorIes;
    std::string sectorIes;
    int idCaracter;
    std::string caracterIes;
    int codigoDelDepartamentoIes;
    std::string departamentoDeDomicilioDeLaIes;
    int codigoDelMunicipioIes;
    std::string municipioDeDomicilioDeLaIes;
    int codigoSniesDelPrograma;
    std::string programaAcademico;
    int idNivelAcademico;
    std::string nivelAcademico;
    int idNivelDeFormacion;
    std::string nivelDeFormacion;
    int idMetodologia;
    std::string metodologia;
    int idArea;
    std::string areaDeConocimiento;
    int idNucleo;
    std::string nucleoBasicoDelConocimientoNbc;
    int idCineCampoAmplio;
    std::string descCineCampoAmplio;
    int idCineCampoEspecifico;
    std::string descCineCampoEspecifico;
    int idCineCodigoDetallado;
    std::string descCineCodigoDetallado;
    int codigoDelDepartamentoPrograma;
    std::string departamentoDeOfertaDelPrograma;
    int codigoDelMunicipioPrograma;
    std::string municipioDeOfertaDelPrograma;
    std::vector<std::unique_ptr<Consolidado>> consolidados;

public:
    // Constructor por defecto
    ProgramaAcademico();
    // Setters y Getters refactorizados con std::string_view en setters
    void setCodigoDeLaInstitucion(int);
    int getCodigoDeLaInstitucion() const;

    void setIesPadre(int);
    int getIesPadre() const;

    void setInstitucionDeEducacionSuperiorIes(std::string_view);
    const std::string &getInstitucionDeEducacionSuperiorIes() const;

    void setPrincipalOSeccional(std::string_view);
    const std::string &getPrincipalOSeccional() const;

    void setIdSectorIes(int);
    int getIdSectorIes() const;

    void setSectorIes(std::string_view);
    const std::string &getSectorIes() const;

    void setIdCaracter(int);
    int getIdCaracter() const;

    void setCaracterIes(std::string_view);
    const std::string &getCaracterIes() const;

    void setCodigoDelDepartamentoIes(int);
    int getCodigoDelDepartamentoIes() const;

    void setDepartamentoDeDomicilioDeLaIes(std::string_view);
    const std::string &getDepartamentoDeDomicilioDeLaIes() const;

    void setCodigoDelMunicipioIes(int);
    int getCodigoDelMunicipioIes() const;

    void setMunicipioDeDomicilioDeLaIes(std::string_view);
    const std::string &getMunicipioDeDomicilioDeLaIes() const;

    void setCodigoSniesDelPrograma(int);
    int getCodigoSniesDelPrograma() const;

    void setProgramaAcademico(std::string_view);
    const std::string &getProgramaAcademico() const;

    void setIdNivelAcademico(int);
    int getIdNivelAcademico() const;

    void setNivelAcademico(std::string_view);
    const std::string &getNivelAcademico() const;

    void setIdNivelDeFormacion(int);
    int getIdNivelDeFormacion() const;

    void setNivelDeFormacion(std::string_view);  // Cambio aquí a std::string_view
    const std::string &getNivelDeFormacion() const;

    void setIdMetodologia(int);
    int getIdMetodologia() const;

    void setMetodologia(std::string_view);
    const std::string &getMetodologia() const;

    void setIdArea(int);
    int getIdArea() const;

    void setAreaDeConocimiento(std::string_view);
    const std::string &getAreaDeConocimiento() const;

    void setIdNucleo(int);
    int getIdNucleo() const;

    void setNucleoBasicoDelConocimientoNbc(std::string_view);
    const std::string &getNucleoBasicoDelConocimientoNbc() const;

    void setIdCineCampoAmplio(int);
    int getIdCineCampoAmplio() const;

    void setDescCineCampoAmplio(std::string_view);
    const std::string &getDescCineCampoAmplio() const;

    void setIdCineCampoEspecifico(int);
    int getIdCineCampoEspecifico() const;

    void setDescCineCampoEspecifico(std::string_view);
    const std::string &getDescCineCampoEspecifico() const;

    void setIdCineCodigoDetallado(int);
    int getIdCineCodigoDetallado() const;

    void setDescCineCodigoDetallado(std::string_view);
    const std::string &getDescCineCodigoDetallado() const;

    void setCodigoDelDepartamentoPrograma(int);
    int getCodigoDelDepartamentoPrograma() const;

    void setDepartamentoDeOfertaDelPrograma(std::string_view);
    const std::string &getDepartamentoDeOfertaDelPrograma() const;

    void setCodigoDelMunicipioPrograma(int);
    int getCodigoDelMunicipioPrograma() const;

    void setMunicipioDeOfertaDelPrograma(std::string_view);
    const std::string &getMunicipioDeOfertaDelPrograma() const;

    void setConsolidado(std::unique_ptr<Consolidado> nuevoConsolidado, int pos);
    Consolidado *getConsolidado(int) const;

    ~ProgramaAcademico() = default;
};

#endif