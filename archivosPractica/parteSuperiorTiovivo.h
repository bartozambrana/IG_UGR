#ifndef PARTESUPERIORTIOVIVO_H_INCLUDED
#define PARTESUPERIORTIOVIVO_H_INCLUDED

#include "malla.h"
#include "cilindro.h"
#include "cono.h"
#include "objply.h"
#include "baseSecundariaTiovivo.h"
#include "barraConPLY.h"

class ParteSuperiorTiovivo{
    private:
        Cilindro * cilindro = nullptr;
        Cono * cono = nullptr;
        BarraConPLY * barraConPLY = nullptr;
        BaseSecundariaTiovivo * base = nullptr;
        
    public:
        ParteSuperiorTiovivo(ObjPLY * ply, string imagenCono, string imagenBase, string imagenBarra);
        void setColor(Tupla3f color);
        void setMaterial(const Material & material, const Material & material2, const Material & material3);
        void setColorSeleccionado(int color);
        void draw(int modo, bool ajedrez, bool tapas, float translacionPLY, float giroZPLY, float giroParteSuperior);
        void setColoresAFalse();
};


#endif