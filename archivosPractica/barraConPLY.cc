#include "barraConPLY.h"

BarraConPLY::BarraConPLY(ObjPLY * ply,string imagenBarra){
    this->cilindro = new Cilindro(50,1,1,imagenBarra);
    this->ply = ply;
}

void BarraConPLY::setColor(Tupla3f color){
    cilindro->setColor(color);
    ply->setColor(color);
}

void BarraConPLY::setMaterial(const Material & material,const Material & material2){
    cilindro->setMaterial(material);
    ply->setMaterial(material2);
}

void BarraConPLY::draw(int modo, bool ajedrez, bool tapas, float translacionPLY, float giroZPLY){
    //Resultado un objeto PLY situado en torno a la altura 10 del cilindro en el origen
    glPushMatrix(); 
        //Barra
        glPushMatrix();
            glScalef(0.5,20,0.5); //Cilindro de diámetro 1 y 20 de alto en el origen
            cilindro->draw( modo , ajedrez , tapas );
        glPopMatrix();

        //ObjetoPly
        glPushMatrix();
            //2 GRADOS DE LIBERTAD
            glTranslatef(-7.0 , translacionPLY + 10.0 ,0.0); //permite que el objeto se desplaze hacia arriba y abajo entorno a la altura 10
            glRotatef(giroZPLY , 0.0 , 0.0 , 1.0);           //Rotamos el objeto dependiendo giroObjPly grados en el eje Z
            ply->draw( modo , ajedrez );
        glPopMatrix();
    glPopMatrix();
}

void BarraConPLY::setColorSeleccionado(int color){
    
    cilindro->setColorSeleccionado(color);
    ply->setColorSeleccionado(color);
}

void BarraConPLY::setAFalseColores(){
    cilindro->setAFalseColores();
    ply->setAFalseColores();
}