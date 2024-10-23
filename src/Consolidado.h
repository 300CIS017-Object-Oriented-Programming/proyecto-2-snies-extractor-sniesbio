#ifndef CONSOLIDADO_H
#define CONSOLIDADO_H

#include <string>

// Estructura que encapsula los datos de los estudiantes.

struct DatosEstudiantes {
    int inscritos;
    int admitidos;
    int matriculados;
    int matriculadosPrimerSemestre;
    int graduados;
};
// Clase que encapsula los datos consolidados de los estudiantes.

class Consolidado {
private:
    int idSexo;
    std::string sexo;
    int ano;
    int semestre;
    DatosEstudiantes datosEstudiantes;

public:
    // Constructores
    Consolidado();
    Consolidado(int idSexo, std::string_view sexo, int ano, int semestre, const DatosEstudiantes &datosEstudiantes);

    // Getters y setters

    int getIdSexo() const;
    void setIdSexo(int idSexo);

    std::string getSexo() const;
    void setSexo(std::string_view sexo);

    int getAno() const;
    void setAno(int ano);

    int getSemestre() const;
    void setSemestre(int semestre);

    int getInscritos() const;
    void setInscritos(int inscritos);

    int getAdmitidos() const;
    void setAdmitidos(int admitidos);

    int getMatriculados() const;
    void setMatriculados(int matriculados);

    int getMatriculadosPrimerSemestre() const;
    void setMatriculadosPrimerSemestre(int matriculadosPrimerSemestre);

    int getGraduados() const;
    void setGraduados(int graduados);
};

#endif // CONSOLIDADO_H