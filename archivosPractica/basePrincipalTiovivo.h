#ifndef BASEPRINCIPALTIOVIVO_H_INCLUDED
#define BASEPRINCIPALTIOVIVO_H_INCLUDED

#include "malla.h"
#include "cilindro.h"
class BasePrincipalTiovivo{
    private:    
        Cilindro * cilindro = nullptr;
    public:

        BasePrincipalTiovivo(string imagenBase);
        void setColor(Tupla3f color);
        void setMaterial(const Material & material);
        void draw(int modo, bool ajedrez, bool tapas);
        void setColorSeleccionado(int color);
        void setAFalseColores();
};


#endif