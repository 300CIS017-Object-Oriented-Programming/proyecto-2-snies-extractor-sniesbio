#include "ProgramaAcademico.h"
#include <iostream>

ProgramaAcademico::ProgramaAcademico() : consolidados(8) {}

// Setters y Getters refactorizados con std::string_view en setters
void ProgramaAcademico::setCodigoDeLaInstitucion(int nuevoCodigoDeLaInstitucion)
{
    codigoDeLaInstitucion = nuevoCodigoDeLaInstitucion;
}

int ProgramaAcademico::getCodigoDeLaInstitucion() const
{
    return codigoDeLaInstitucion;
}

void ProgramaAcademico::setIesPadre(int nuevoIesPadre)
{
    iesPadre = nuevoIesPadre;
}

int ProgramaAcademico::getIesPadre() const
{
    return iesPadre;
}

void ProgramaAcademico::setInstitucionDeEducacionSuperiorIes(std::string_view nuevoInstitucionDeEducacionSuperiorIes)
{
    institucionDeEducacionSuperiorIes = nuevoInstitucionDeEducacionSuperiorIes;
}

const std::string &ProgramaAcademico::getInstitucionDeEducacionSuperiorIes() const
{
    return institucionDeEducacionSuperiorIes;
}

void ProgramaAcademico::setPrincipalOSeccional(std::string_view nuevoPrincipalOSeccional)
{
    principalOSeccional = nuevoPrincipalOSeccional;
}

const std::string &ProgramaAcademico::getPrincipalOSeccional() const
{
    return principalOSeccional;
}

void ProgramaAcademico::setIdSectorIes(int nuevoIdSectorIes)
{
    idSectorIes = nuevoIdSectorIes;
}

int ProgramaAcademico::getIdSectorIes() const
{
    return idSectorIes;
}

void ProgramaAcademico::setSectorIes(std::string_view nuevoSectorIes)
{
    sectorIes = nuevoSectorIes;
}

const std::string &ProgramaAcademico::getSectorIes() const
{
    return sectorIes;
}

void ProgramaAcademico::setIdCaracter(int nuevoIdCaracter)
{
    idCaracter = nuevoIdCaracter;
}

int ProgramaAcademico::getIdCaracter() const
{
    return idCaracter;
}

void ProgramaAcademico::setCaracterIes(std::string_view nuevoCaracterIes)
{
    caracterIes = nuevoCaracterIes;
}

const std::string &ProgramaAcademico::getCaracterIes() const
{
    return caracterIes;
}

void ProgramaAcademico::setCodigoDelDepartamentoIes(int nuevoCodigoDelDepartamentoIes)
{
    codigoDelDepartamentoIes = nuevoCodigoDelDepartamentoIes;
}

int ProgramaAcademico::getCodigoDelDepartamentoIes() const
{
    return codigoDelDepartamentoIes;
}

void ProgramaAcademico::setDepartamentoDeDomicilioDeLaIes(std::string_view nuevoDepartamentoDeDomicilioDeLaIes)
{
    departamentoDeDomicilioDeLaIes = nuevoDepartamentoDeDomicilioDeLaIes;
}

const std::string &ProgramaAcademico::getDepartamentoDeDomicilioDeLaIes() const
{
    return departamentoDeDomicilioDeLaIes;
}

void ProgramaAcademico::setCodigoDelMunicipioIes(int nuevoCodigoDelMunicipioIes)
{
    codigoDelMunicipioIes = nuevoCodigoDelMunicipioIes;
}

int ProgramaAcademico::getCodigoDelMunicipioIes() const
{
    return codigoDelMunicipioIes;
}

void ProgramaAcademico::setMunicipioDeDomicilioDeLaIes(std::string_view nuevoMunicipioDeDomicilioDeLaIes)
{
    municipioDeDomicilioDeLaIes = nuevoMunicipioDeDomicilioDeLaIes;
}

const std::string &ProgramaAcademico::getMunicipioDeDomicilioDeLaIes() const
{
    return municipioDeDomicilioDeLaIes;
}

void ProgramaAcademico::setCodigoSniesDelPrograma(int nuevoCodigoSniesDelPrograma)
{
    codigoSniesDelPrograma = nuevoCodigoSniesDelPrograma;
}

int ProgramaAcademico::getCodigoSniesDelPrograma() const
{
    return codigoSniesDelPrograma;
}

void ProgramaAcademico::setProgramaAcademico(std::string_view nuevoProgramaAcademico)
{
    programaAcademico = nuevoProgramaAcademico;
}

const std::string &ProgramaAcademico::getProgramaAcademico() const
{
    return programaAcademico;
}

void ProgramaAcademico::setIdNivelAcademico(int nuevoIdNivelAcademico)
{
    idNivelAcademico = nuevoIdNivelAcademico;
}

int ProgramaAcademico::getIdNivelAcademico() const
{
    return idNivelAcademico;
}

void ProgramaAcademico::setNivelAcademico(std::string_view nuevoNivelAcademico)
{
    nivelAcademico = nuevoNivelAcademico;
}

const std::string &ProgramaAcademico::getNivelAcademico() const
{
    return nivelAcademico;
}

void ProgramaAcademico::setIdNivelDeFormacion(int nuevoIdNivelDeFormacion)
{
    idNivelDeFormacion = nuevoIdNivelDeFormacion;
}

int ProgramaAcademico::getIdNivelDeFormacion() const
{
    return idNivelDeFormacion;
}

void ProgramaAcademico::setNivelDeFormacion(std::string_view nuevoNivelDeFormacion)
{
    nivelDeFormacion = nuevoNivelDeFormacion;
}

const std::string &ProgramaAcademico::getNivelDeFormacion() const
{
    return nivelDeFormacion;
}

void ProgramaAcademico::setIdMetodologia(int nuevoIdMetodologia)
{
    idMetodologia = nuevoIdMetodologia;
}

int ProgramaAcademico::getIdMetodologia() const
{
    return idMetodologia;
}

void ProgramaAcademico::setMetodologia(std::string_view nuevaMetodologia)
{
    metodologia = nuevaMetodologia;
}

const std::string &ProgramaAcademico::getMetodologia() const
{
    return metodologia;
}

void ProgramaAcademico::setIdArea(int nuevoIdArea)
{
    idArea = nuevoIdArea;
}

int ProgramaAcademico::getIdArea() const
{
    return idArea;
}

void ProgramaAcademico::setAreaDeConocimiento(std::string_view areaConocimiento)
{
    areaDeConocimiento = areaConocimiento;
}

const std::string &ProgramaAcademico::getAreaDeConocimiento() const
{
    return areaDeConocimiento;
}

void ProgramaAcademico::setIdNucleo(int nuevoIdNucleo)
{
    idNucleo = nuevoIdNucleo;
}

int ProgramaAcademico::getIdNucleo() const
{
    return idNucleo;
}

void ProgramaAcademico::setNucleoBasicoDelConocimientoNbc(std::string_view nuevoNucleoBasicoDelConocimientoNbc)
{
    nucleoBasicoDelConocimientoNbc = nuevoNucleoBasicoDelConocimientoNbc;
}

const std::string &ProgramaAcademico::getNucleoBasicoDelConocimientoNbc() const
{
    return nucleoBasicoDelConocimientoNbc;
}

void ProgramaAcademico::setIdCineCampoAmplio(int nuevoIdCineCampoAmplio)
{
    idCineCampoAmplio = nuevoIdCineCampoAmplio;
}

int ProgramaAcademico::getIdCineCampoAmplio() const
{
    return idCineCampoAmplio;
}

void ProgramaAcademico::setDescCineCampoAmplio(std::string_view nuevoDescCineCampoAmplio)
{
    descCineCampoAmplio = nuevoDescCineCampoAmplio;
}

const std::string &ProgramaAcademico::getDescCineCampoAmplio() const
{
    return descCineCampoAmplio;
}

void ProgramaAcademico::setIdCineCampoEspecifico(int nuevoIdCineCampoEspecifico)
{
    idCineCampoEspecifico = nuevoIdCineCampoEspecifico;
}

int ProgramaAcademico::getIdCineCampoEspecifico() const
{
    return idCineCampoEspecifico;
}

void ProgramaAcademico::setDescCineCampoEspecifico(std::string_view nuevoDescCineCampoEspecifico)
{
    descCineCampoEspecifico = nuevoDescCineCampoEspecifico;
}

const std::string &ProgramaAcademico::getDescCineCampoEspecifico() const
{
    return descCineCampoEspecifico;
}

void ProgramaAcademico::setIdCineCodigoDetallado(int nuevoIdCineCodigoDetallado)
{
    idCineCodigoDetallado = nuevoIdCineCodigoDetallado;
}

int ProgramaAcademico::getIdCineCodigoDetallado() const
{
    return idCineCodigoDetallado;
}

void ProgramaAcademico::setDescCineCodigoDetallado(std::string_view nuevoDescCineCodigoDetallado)
{
    descCineCodigoDetallado = nuevoDescCineCodigoDetallado;
}

const std::string &ProgramaAcademico::getDescCineCodigoDetallado() const
{
    return descCineCodigoDetallado;
}

void ProgramaAcademico::setCodigoDelDepartamentoPrograma(int nuevoCodigoDelDepartamentoPrograma)
{
    codigoDelDepartamentoPrograma = nuevoCodigoDelDepartamentoPrograma;
}

int ProgramaAcademico::getCodigoDelDepartamentoPrograma() const
{
    return codigoDelDepartamentoPrograma;
}

void ProgramaAcademico::setDepartamentoDeOfertaDelPrograma(std::string_view nuevoDepartamentoDeOfertaDelPrograma)
{
    departamentoDeOfertaDelPrograma = nuevoDepartamentoDeOfertaDelPrograma;
}

const std::string &ProgramaAcademico::getDepartamentoDeOfertaDelPrograma() const
{
    return departamentoDeOfertaDelPrograma;
}

void ProgramaAcademico::setCodigoDelMunicipioPrograma(int nuevoCodigoDelMunicipioPrograma)
{
    codigoDelMunicipioPrograma = nuevoCodigoDelMunicipioPrograma;
}

int ProgramaAcademico::getCodigoDelMunicipioPrograma() const
{
    return codigoDelMunicipioPrograma;
}

void ProgramaAcademico::setMunicipioDeOfertaDelPrograma(std::string_view nuevoMunicipioDeOfertaDelPrograma)
{
    municipioDeOfertaDelPrograma = nuevoMunicipioDeOfertaDelPrograma;
}

const std::string &ProgramaAcademico::getMunicipioDeOfertaDelPrograma() const
{
    return municipioDeOfertaDelPrograma;
}

void ProgramaAcademico::setConsolidado(std::unique_ptr<Consolidado> nuevoConsolidado, int pos)
{
    if (pos >= 0 && pos < consolidados.size())
    {
        consolidados[pos] = std::move(nuevoConsolidado);  // Asignamos con std::move para transferir la propiedad
    }
    else
    {
        std::cerr << "Error: Posición fuera de rango al intentar establecer un consolidado." << std::endl;
    }
}

Consolidado *ProgramaAcademico::getConsolidado(int posicionConsolidado) const
{
    if (posicionConsolidado >= 0 && posicionConsolidado < consolidados.size())
    {
        return consolidados[posicionConsolidado].get();  // Accedemos al puntero gestionado
    }
    std::cerr << "Error: Posición fuera de rango al intentar obtener un consolidado." << std::endl;
    return nullptr;
}