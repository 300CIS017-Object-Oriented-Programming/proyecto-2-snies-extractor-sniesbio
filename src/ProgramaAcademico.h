#ifndef PROGRAMA_ACADEMICO_H
#define PROGRAMA_ACADEMICO_H

#include <string>
#include <vector>
#include <memory>  // Para std::unique_ptr
#include "Consolidado.h"

using std::string;
using std::vector;

class ProgramaAcademico
{
    int codigoDeLaInstitucion;
    int iesPadre;
    string institucionDeEducacionSuperiorIes;
    string principalOSeccional;
    int idSectorIes;
    string sectorIes;
    int idCaracter;
    string caracterIes;
    int codigoDelDepartamentoIes;
    string departamentoDeDomicilioDeLaIes;
    int codigoDelMunicipioIes;
    string municipioDeDomicilioDeLaIes;
    int codigoSniesDelPrograma;
    string programaAcademico;
    int idNivelAcademico;
    string nivelAcademico;
    int idNivelDeFormacion;
    string nivelDeFormacion;
    int idMetodologia;
    string metodologia;
    int idArea;
    string areaDeConocimiento;
    int idNucleo;
    string nucleoBasicoDelConocimientoNbc;
    int idCineCampoAmplio;
    string descCineCampoAmplio;
    int idCineCampoEspecifico;
    string descCineCampoEspecifico;
    int idCineCodigoDetallado;
    string descCineCodigoDetallado;
    int codigoDelDepartamentoPrograma;
    string departamentoDeOfertaDelPrograma;
    int codigoDelMunicipioPrograma;
    string municipioDeOfertaDelPrograma;
    vector<std::unique_ptr<Consolidado>> consolidados;  // Manejo de memoria automática con unique_ptr

public:
    ProgramaAcademico();

    // Métodos set y get
    void setCodigoDeLaInstitucion(int nuevoCodigoDeLaInstitucion);
    int getCodigoDeLaInstitucion() const;

    void setIesPadre(int nuevoIesPadre);
    int getIesPadre() const;

    void setInstitucionDeEducacionSuperiorIes(std::string_view nuevoInstitucionDeEducacionSuperiorIes);
    string getInstitucionDeEducacionSuperiorIes() const;

    void setPrincipalOSeccional(std::string_view nuevoPrincipalOSeccional);
    string getPrincipalOSeccional() const;

    void setIdSectorIes(int nuevoIdSectorIes);
    int getIdSectorIes() const;

    void setSectorIes(std::string_view nuevoSectorIes);
    string getSectorIes() const;

    void setIdCaracter(int nuevoIdCaracter);
    int getIdCaracter() const;

    void setCaracterIes(std::string_view nuevoCaracterIes);
    string getCaracterIes() const;

    void setCodigoDelDepartamentoIes(int nuevoCodigoDelDepartamentoIes);
    int getCodigoDelDepartamentoIes() const;

    void setDepartamentoDeDomicilioDeLaIes(std::string_view nuevoDepartamentoDeDomicilioDeLaIes);
    string getDepartamentoDeDomicilioDeLaIes() const;

    void setCodigoDelMunicipioIes(int nuevoCodigoDelMunicipioIes);
    int getCodigoDelMunicipioIes() const;

    void setMunicipioDeDomicilioDeLaIes(std::string_view nuevoMunicipioDeDomicilioDeLaIes);
    string getMunicipioDeDomicilioDeLaIes() const;

    void setCodigoSniesDelPrograma(int nuevoCodigoSniesDelPrograma);
    int getCodigoSniesDelPrograma() const;

    void setProgramaAcademico(std::string_view nuevoProgramaAcademico);
    string getProgramaAcademico() const;

    void setIdNivelAcademico(int nuevoIdNivelAcademico);
    int getIdNivelAcademico() const;

    void setNivelAcademico(std::string_view nuevoNivelAcademico);
    string getNivelAcademico() const;

    void setIdNivelDeFormacion(int nuevoIdNivelDeFormacion);
    int getIdNivelDeFormacion() const;

    void setNivelDeFormacion(std::string_view nuevoNivelDeFormacion);
    string getNivelDeFormacion() const;

    void setIdMetodologia(int nuevoIdMetodologia);
    int getIdMetodologia() const;

    void setMetodologia(std::string_view nuevaMetodologia);
    string getMetodologia() const;

    void setIdArea(int nuevoIdArea);
    int getIdArea() const;

    void setAreaDeConocimiento(std::string_view areaConocimiento);
    string getAreaDeConocimiento() const;

    void setIdNucleo(int nuevoIdNucleo);
    int getIdNucleo() const;

    void setNucleoBasicoDelConocimientoNbc(std::string_view nuevoNucleoBasicoDelConocimientoNbc);
    string getNucleoBasicoDelConocimientoNbc() const;

    void setIdCineCampoAmplio(int nuevoIdCineCampoAmplio);
    int getIdCineCampoAmplio() const;

    void setDescCineCampoAmplio(std::string_view nuevoDescCineCampoAmplio);
    string getDescCineCampoAmplio() const;

    void setIdCineCampoEspecifico(int nuevoIdCineCampoEspecifico);
    int getIdCineCampoEspecifico() const;

    void setDescCineCampoEspecifico(std::string_view nuevoDescCineCampoEspecifico);
    string getDescCineCampoEspecifico() const;

    void setIdCineCodigoDetallado(int nuevoIdCineCodigoDetallado);
    int getIdCineCodigoDetallado() const;

    void setDescCineCodigoDetallado(std::string_view nuevoDescCineCodigoDetallado);
    string getDescCineCodigoDetallado() const;

    void setCodigoDelDepartamentoPrograma(int nuevoCodigoDelDepartamentoPrograma);
    int getCodigoDelDepartamentoPrograma() const;

    void setDepartamentoDeOfertaDelPrograma(std::string_view nuevoDepartamentoDeOfertaDelPrograma);
    string getDepartamentoDeOfertaDelPrograma() const;

    void setCodigoDelMunicipioPrograma(int nuevoCodigoDelMunicipioPrograma);
    int getCodigoDelMunicipioPrograma() const;

    void setMunicipioDeOfertaDelPrograma(std::string_view nuevoMunicipioDeOfertaDelPrograma);
    string getMunicipioDeOfertaDelPrograma() const;

    void setConsolidado(std::unique_ptr<Consolidado> nuevoConsolidado, int pos);
    const Consolidado* getConsolidado(int posicionConsolidado) const;
};

#endif