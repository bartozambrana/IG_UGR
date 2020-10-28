
#include "cilindro.h"
using namespace std;
Cilindro::Cilindro(const int num_instancias_perf, const float altura, const float radio,string imagen){
    vector<Tupla3f> perfil_original;

    //Unicos dos puntos necesarios para la realización de la geometría del cilindro.   
    perfil_original.push_back(Tupla3f(radio,0,0));
    perfil_original.push_back(Tupla3f(radio,altura,0));
    setTapa(true,true);
    numInstancias = num_instancias_perf;
    crearMalla(perfil_original,num_instancias_perf);
    
    for(int i= 0; i < v.size(); i++){
        color.push_back(Tupla3f(0.0,1.0,0.0));
        colorLineas.push_back(Tupla3f(0.0,1.0,1.0));
        colorPuntos.push_back(Tupla3f(0.2,0.1,1.0));
        color2Ajedrez.push_back(Tupla3f(0.0,1.0,0.0));
        colorAmarillo.push_back(Tupla3f(1.0,1.0,0.0));
    }

    calcular_normales();

    textura = new Textura(imagen);
}
