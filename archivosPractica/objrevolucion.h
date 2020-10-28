// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

const static double PI = 3.14159265359;

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
        ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
        bool getTapaSuperior() const;
        bool getTapaInferior() const;
        void drawSinTapasInmediato();
        void drawSinTapasAjedrez();
        void drawSinTapasDiferido();
        void draw(int modo, bool ajedrez, bool tapas);

        
        // void draw(int modo, bool ajedrez);
        
    protected:
        void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);
        void crearMalla2(std::vector<Tupla3f> perfil_original, int num_instancias);
        void setTapa(bool tapaSup, bool tapaInf);
        bool tapa_superior,tapa_inferior;
        int numInstancias;
} ;




#endif
