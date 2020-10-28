#include "esfera.h"
using namespace std;

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio){
    
    vector<Tupla3f> perfil_original;
    for(int i = 0; i < num_vert_perfil; i++)
        perfil_original.push_back(Tupla3f(radio*sin(PI*i/num_instancias_perf),
                                          radio*cos(PI*i/num_instancias_perf),
                                          0
                                        ));

    setTapa(true,true);
    crearMalla(perfil_original,num_instancias_perf);
    numInstancias = num_instancias_perf;
    for(int i= 0; i < v.size(); i++){
        color.push_back(Tupla3f(1.0,0.0,0.0));
        color2Ajedrez.push_back(Tupla3f(0.0,1.0,0.0));
    }
    calcular_normales();

}