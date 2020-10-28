#include "material.h"
#include <iostream>
Material::Material(){}
Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo = 0.0){
    difuso = mdifuso;
    especular = mespecular;
    ambiente = mambiente;
    if (brillo < 0.0 || brillo > 128.0)
        this->brillo = 0.0;
    else
        this->brillo = brillo;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
}

void Material::setMaterial(Material mat){
    (*this) = mat;
}

