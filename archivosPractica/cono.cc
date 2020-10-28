#include "cono.h"
#include <vector>
using namespace std;
Cono::Cono(const int num_instancias_perf, const float altura, const float radio, string imagen){
    
    //Preguntar como sacar los puntos del cono, cuando sean más dos o más, y cuando sean dos que sean distintos
    // de (0,y,0) al menos uno de ellos.
    vector<Tupla3f> perfil_original;
   
    perfil_original.push_back(Tupla3f(radio,0,0));
    perfil_original.push_back(Tupla3f(0,altura,0));
    setTapa(true,true);
    numInstancias = num_instancias_perf;
    crearMalla(perfil_original,num_instancias_perf);
   
        
    for(int i = 0; i < v.size(); i++){
        color.push_back(Tupla3f(0.0,1.0,0.0)); //azul verdoso
        colorLineas.push_back(Tupla3f(0.0,1.0,1.0));
        colorPuntos.push_back(Tupla3f(0.2,0.1,1.0));
        color2Ajedrez.push_back(Tupla3f(0.0,1.0,0.0));
        colorAmarillo.push_back(Tupla3f(1.0,1.0,0.0));
    }
        
    calcular_normales();

    //Cargamos la imagen
    textura = new Textura(imagen);
        
}