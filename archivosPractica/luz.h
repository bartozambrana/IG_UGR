#ifndef _LUZ_H
#define _LUZ_H

#include "aux.h"
#include<chrono>

using namespace std;
using namespace std::chrono;
// tipo para registrar el instante actual
typedef time_point<steady_clock> InstanteActual;

// tipo para las duraciones
typedef duration<float,ratio<1,1> > Duracion;
class Luz{
    public:
    void activar();
    void desactivar(); //para desactivar la luz, por si queremos desactivarla en una sección del código
    bool getLuzEncendida()const;
    void variarAnguloAlpha(float incremento);
    void variarAnguloBeta(float incremento);
    float getAlpha()const;
    float getBeta()const;
    void movimientoAutomatico();
    void inicioAnimaciones();
    void acelerar();
    void desacelerar();


    protected:
    float velocidad;//velocidad de la animación
    InstanteActual intanteUltimaAccion;
    float alpha = 0.0; //rotación respecto el eje Y
    float beta = 0.0; //rotación respecto el eje X
    bool luzEncendida = false; //indica si la luz se encuentra encendida o apagada dada un momento
    Tupla4f posicion; //posición de la luz
    GLenum id; //luz que se encuentra activada o desactivada
    //*******COLORES DE LUZ******//
    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;
    

};

#endif