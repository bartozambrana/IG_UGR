#ifndef BARRACONPLY_H_INCLUDED
#define BARRACONPLY_H_INCLUDED

#include "malla.h"
#include "cilindro.h"
#include "objply.h"
class BarraConPLY {
    private:
        ObjPLY * ply = nullptr;
        Cilindro * cilindro = nullptr;
    public:
        BarraConPLY(ObjPLY * ply,string imagenBarra);
        void setColor(Tupla3f color);
        void setMaterial(const Material & material, const Material & material2);
        void draw(int modo, bool ajedrez, bool tapas, float translacionPLY, float giroZPLY);
        void setColorSeleccionado(int color);
        void setAFalseColores();
};


#endif