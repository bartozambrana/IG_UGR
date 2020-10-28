#ifndef MODELOJERARQUICO_H_INCLUDED
#define MODELOJERARQUICO_H_INCLUDED

#include "parteSuperiorTiovivo.h"
#include "basePrincipalTiovivo.h"
#include "objply.h"
#include "material.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

// tipo para registrar el instante actual
typedef time_point<steady_clock> InstanteActual;

// tipo para las duraciones
typedef duration<float,ratio<1,1> > Duracion;




class Tiovivo{
    private:
        float translacionPLY;    // movimiento sube y baja del f16
        float giroZPLY;          // moviemiento hacia los lados del f16
        float giroParteSuperior; // giro de la parte superior del tiovivo en el sentido antihorario

        bool bajar ; //booleano para controlar que el avion suba y baje
        bool inclinarAbajo; //booleano para controlar la inclinación del avión

        float GiroTiovivo = 0;
float AnguloPLY = 0;
float TranslacionPLY = 0 ;

        //Elementos del tío vivo;
        ParteSuperiorTiovivo * parteSuperior = nullptr; // parte central 
        BasePrincipalTiovivo * base = nullptr;          // base sobre la que se apoya

        InstanteActual intanteUltimaAccion;
        float velocidad;//velocidad de la animación
    public:
        Tiovivo(ObjPLY * ply,string imagenCono,string imagenBases,string imagenBarra);
        void setColor(Tupla3f color);
        void setMaterial(const Material & material,const Material & material2,const Material & material3);
        void draw(int modo, bool ajedrez, bool tapas);
        void modificarGradosLibertad(int gradoLibertad, float valor);
        void acelerar();
        void desacelerar();
        void movimientoAutomatico();
        void inicioAnimaciones();
        void setColorSeleccionado(int color);
        void setColoresAFalse();


};

#endif