#include "Consolidado.h"
#include <string>

Consolidado::Consolidado() = default;

Consolidado::Consolidado(int idSexo, std::string_view sexo, int ano, int semestre, const DatosEstudiantes &datosEstudiantes)
    : idSexo(idSexo), sexo(sexo), ano(ano), semestre(semestre), datosEstudiantes(datosEstudiantes) {}

int Consolidado::getIdSexo() const {
    return idSexo;
}

void Consolidado::setIdSexo(int nuevoIdSexo) {
    this->idSexo = nuevoIdSexo;
}

std::string Consolidado::getSexo() const {
    return sexo;
}

void Consolidado::setSexo(std::string_view nuevoSexo) {
    this->sexo = nuevoSexo;
}

int Consolidado::getAno() const {
    return ano;
}

void Consolidado::setAno(int nuevoAno) {
    this->ano = nuevoAno;
}

int Consolidado::getSemestre() const {
    return semestre;
}

void Consolidado::setSemestre(int nuevoSemestre) {
    this->semestre = nuevoSemestre;
}

int Consolidado::getInscritos() const {
    return datosEstudiantes.inscritos;
}

void Consolidado::setInscritos(int inscritos) {
    datosEstudiantes.inscritos = inscritos;
}

int Consolidado::getAdmitidos()  const{
    return datosEstudiantes.admitidos;
}

void Consolidado::setAdmitidos(int admitidos) {
    datosEstudiantes.admitidos = admitidos;
}

int Consolidado::getMatriculados()  const{
    return datosEstudiantes.matriculados;
}

void Consolidado::setMatriculados(int matriculados) {
    datosEstudiantes.matriculados = matriculados;
}

int Consolidado::getMatriculadosPrimerSemestre() const {
    return datosEstudiantes.matriculadosPrimerSemestre;
}

void Consolidado::setMatriculadosPrimerSemestre(int matriculadosPrimerSemestre) {
    datosEstudiantes.matriculadosPrimerSemestre = matriculadosPrimerSemestre;
}

int Consolidado::getGraduados()  const{
    return datosEstudiantes.graduados;
}

void Consolidado::setGraduados(int graduados) {
    datosEstudiantes.graduados = graduados;
}