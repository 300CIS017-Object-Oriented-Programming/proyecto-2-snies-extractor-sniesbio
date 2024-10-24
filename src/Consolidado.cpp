#include "Consolidado.h"
#include <string>

/**
 * @class Consolidado
 * @brief Esta clase representa un registro consolidado de datos de estudiantes.
 *
 * La clase Consolidado encapsula varios atributos relacionados con los datos de los estudiantes,
 * como el género, el año, el semestre y otras estadísticas relacionadas con los estudiantes.
 */

//Constructor por defecto.
Consolidado::Consolidado() = default;

//Constructor por parámetros
Consolidado::Consolidado(int idSexo, std::string_view sexo, int ano, int semestre, const DatosEstudiantes &datosEstudiantes)
    : idSexo(idSexo), sexo(sexo), ano(ano), semestre(semestre), datosEstudiantes(datosEstudiantes) {}


//Getters y Setters
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