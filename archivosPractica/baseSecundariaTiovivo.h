#ifndef BASESECUNDARIATIOVIVO_H_INCLUDED
#define BASESECUNDARIATIOVIVO_H_INCLUDED

#include "malla.h"
#include "cilindro.h"
class BaseSecundariaTiovivo{
    private:
        Cilindro * cilindro = nullptr;
    public:
        BaseSecundariaTiovivo(string imagen);
        void setMaterial(const Material & material);
        void setColor(Tupla3f color);
        void draw(int modo, bool ajedrez, bool tapas);
        void setColorSeleccionado(int color);
        void setAFalseColores();
};


#endif