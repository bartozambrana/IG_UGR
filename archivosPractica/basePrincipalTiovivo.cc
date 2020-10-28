#include "basePrincipalTiovivo.h"

BasePrincipalTiovivo::BasePrincipalTiovivo(string imagen){
    cilindro = new Cilindro(50,1,1,imagen);
}

void BasePrincipalTiovivo::setColor(Tupla3f color){
    cilindro->setColor(color);
}

void BasePrincipalTiovivo::setMaterial(const Material & material){
    cilindro->setMaterial(material);
}

void BasePrincipalTiovivo::draw(int modo,bool ajedrez,bool tapas){
    glPushMatrix(); //Resultado una base de diametro 25 y de altura 2 situada en el origen
        glScalef(25,2.0,25);
        cilindro->draw(modo,ajedrez,tapas);
    glPopMatrix();

}

void BasePrincipalTiovivo::setColorSeleccionado(int color){
    cilindro->setColorSeleccionado(color);
}

void BasePrincipalTiovivo::setAFalseColores(){
    cilindro->setAFalseColores();
}