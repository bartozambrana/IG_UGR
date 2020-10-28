#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "aux.h"

class Material{
    private:
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;
        float brillo;
    public:
        Material();
        Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo);
        void aplicar();
        void setMaterial(Material mat);
};

#endif