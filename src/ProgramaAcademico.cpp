#include "ProgramaAcademico.h"
#include <utility>  // Para std::move

using namespace std;

ProgramaAcademico::ProgramaAcademico()
    : codigoDeLaInstitucion(0), iesPadre(0), idSectorIes(0), idCaracter(0),
      codigoDelDepartamentoIes(0), codigoDelMunicipioIes(0), codigoSniesDelPrograma(0),
      idNivelAcademico(0), idNivelDeFormacion(0), idMetodologia(0), idArea(0), idNucleo(0),
      idCineCampoAmplio(0), idCineCampoEspecifico(0), idCineCodigoDetallado(0),
      codigoDelDepartamentoPrograma(0), codigoDelMunicipioPrograma(0),
      consolidados(8)
{
}

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

string ProgramaAcademico::getInstitucionDeEducacionSuperiorIes() const
{
    return institucionDeEducacionSuperiorIes;
}

void ProgramaAcademico::setPrincipalOSeccional(std::string_view nuevoPrincipalOSeccional)
{
    principalOSeccional = nuevoPrincipalOSeccional;
}

string ProgramaAcademico::getPrincipalOSeccional() const
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

string ProgramaAcademico::getSectorIes() const
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

string ProgramaAcademico::getCaracterIes() const
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

string ProgramaAcademico::getDepartamentoDeDomicilioDeLaIes() const
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

string ProgramaAcademico::getMunicipioDeDomicilioDeLaIes() const
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

string ProgramaAcademico::getProgramaAcademico() const
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

string ProgramaAcademico::getNivelAcademico() const
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

string ProgramaAcademico::getNivelDeFormacion() const
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

string ProgramaAcademico::getMetodologia() const
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

string ProgramaAcademico::getAreaDeConocimiento() const
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

string ProgramaAcademico::getNucleoBasicoDelConocimientoNbc() const
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

string ProgramaAcademico::getDescCineCampoAmplio() const
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

string ProgramaAcademico::getDescCineCampoEspecifico() const
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

string ProgramaAcademico::getDescCineCodigoDetallado() const
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

string ProgramaAcademico::getDepartamentoDeOfertaDelPrograma() const
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

string ProgramaAcademico::getMunicipioDeOfertaDelPrograma() const
{
    return municipioDeOfertaDelPrograma;
}

// Cambiamos std::unique_ptr en lugar de punteros crudos para manejo automático de memoria
void ProgramaAcademico::setConsolidado(std::unique_ptr<Consolidado> nuevoConsolidado, int pos)
{
    consolidados[pos] = std::move(nuevoConsolidado);  // Transferimos la propiedad del puntero
}

const Consolidado* ProgramaAcademico::getConsolidado(int posicionConsolidado) const
{
    return consolidados[posicionConsolidado].get();  // Devolvemos un puntero crudo constante
}