#include "luz.h"
#include <iostream>
void Luz::activar(){
    luzEncendida = true;
    //habilitación de la luz
    glEnable(id);
    //atributos de la luz
    glLightfv(id,GL_AMBIENT,(GLfloat*) &colorAmbiente);
    glLightfv(id,GL_SPECULAR,(GLfloat*) &colorEspecular);
    glLightfv(id,GL_DIFFUSE,(GLfloat*) &colorDifuso);
    //posicion o dirección de la luz
 
    glLightfv(id,GL_POSITION,(GLfloat*) &posicion);
}

void Luz::desactivar(){
    luzEncendida = false;
    //desabilitación de la luz
    glDisable(id);
}

void Luz::variarAnguloAlpha(float incremento){
    posicion[1] = (cos(alpha) * posicion[0]) + (sin(alpha) * posicion[2]);
    alpha = alpha + incremento;
    
}

void Luz::variarAnguloBeta(float incremento){
    beta = beta + incremento;
    posicion[0] = (cos(beta) * posicion[1]) - (sin(beta) * posicion[2]);
    
}

float Luz::getAlpha()const{
    return alpha;
}

float Luz::getBeta()const{
    return beta;
}


void Luz::inicioAnimaciones(){
    
    //instante de la primera animación
    intanteUltimaAccion = steady_clock::now();
}

void Luz::movimientoAutomatico(){
    
    //Calcular el tiempo desde la última acción
    const InstanteActual actual = steady_clock::now();
    const Duracion duracion = actual - intanteUltimaAccion ;
    const float segundos = duracion.count();

    intanteUltimaAccion = actual;

    //Evitamos que sobrepase el techo 
    
    float incremento = segundos*velocidad/10;
    if(incremento == 0)
        incremento = 0.0000003;
    
    variarAnguloAlpha(incremento);
    variarAnguloBeta(incremento);
}

void Luz::acelerar(){
    velocidad += 0.2; //incrementamos la velocidad poco a poco

    

}

void Luz::desacelerar(){
    //Establecemos la velocidad mínima como 0.2;
    velocidad = max(velocidad - 0.2, 0.2);
}