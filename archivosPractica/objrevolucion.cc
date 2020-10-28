#include "objrevolucion.h"
#include "ply_reader.h"
#include <queue>
using namespace std;
using namespace ply;
// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)
ObjRevolucion::ObjRevolucion(){}
ObjRevolucion::ObjRevolucion(const string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)
   vector<Tupla3f> perfil;
   read_vertices(archivo,perfil);
   setTapa(tapa_sup,tapa_inf);
   crearMalla(perfil,30);
   numInstancias = num_instancias;
   for(int i = 0; i < f.size(); i++){
      color.push_back(Tupla3f(255,0,0));
      color2Ajedrez.push_back(Tupla3f(0,255,0));
   }
   calcular_normales();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    crearMalla(archivo,num_instancias);
    setTapa(tapa_sup,tapa_inf);
    numInstancias = num_instancias;
    for(int i= 0; i < v.size(); i++){
        color.push_back(Tupla3f(255,0,0));
        color2Ajedrez.push_back(Tupla3f(0,255,0));
    }
    calcular_normales();
}

bool ObjRevolucion::getTapaInferior()const{
   return tapa_inferior;
}

bool ObjRevolucion::getTapaSuperior()const{
   return tapa_superior;
}

void ObjRevolucion::setTapa(bool tapaSup,bool tapaInf){
   tapa_superior = tapaSup;
   tapa_inferior = tapaInf;
}

void ObjRevolucion::drawSinTapasInmediato(){
   
   //Indices de las tapas superior e inferior en el caso de que haya.
   int numeroCaras = numInstancias;
   if(getTapaSuperior() && getTapaInferior()){
       numeroCaras = 2*numInstancias;
      
   }else if((getTapaSuperior() && !getTapaInferior()) || (!getTapaSuperior() && getTapaInferior()))
      numeroCaras = numInstancias;

   if (glIsEnabled(GL_TEXTURE_2D) == GL_TRUE && textura != nullptr){
      if(ct.size() == 0 ){
         asignacionTexturaAutomatica();
      }else{
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2,GL_FLOAT,0,ct.data());
         
      }
      textura->activar();
      
   }

   if (glIsEnabled(GL_LIGHTING) == GL_TRUE && tieneMaterial){
      material.aplicar();
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_FLOAT,0,nv.data());
      
   }
      //Habilitamos el array del color de los vértices
      glEnableClientState(GL_COLOR_ARRAY);
      if(solido){
         glColorPointer(3,GL_FLOAT,0,color.data());
      }else if(lineas)
         glColorPointer(3,GL_FLOAT,0,colorLineas.data());
      else if(puntos)
         glColorPointer(3,GL_FLOAT,0,colorPuntos.data());
      else if(amarillo)
         glColorPointer(3,GL_FLOAT,0,colorAmarillo.data());
   
   
   
   

  //Habilitamos el array de vértices
  glEnableClientState(GL_VERTEX_ARRAY);
  //Especificamos la tabla de coordenadas de los vértices
  glVertexPointer(3,GL_FLOAT,0,v.data());
  
  glDrawElements(GL_TRIANGLES,3*(f.size()-numeroCaras), GL_UNSIGNED_INT, f.data());//dibujamos los triangulos indexados
  
  //Desabilitamos el array de vértices.
  glDisable(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  if(ct.size() == 0 && glIsEnabled(GL_TEXTURE_2D) == GL_TRUE){
      glDisable( GL_TEXTURE_GEN_S ); // desactivado inicialmente
      glDisable( GL_TEXTURE_GEN_T );
   }

}
void ObjRevolucion::crearMalla(vector<Tupla3f> perfil_original, int num_instancias) {

   //Eliminamos aquellos vértices que nos imposibilitan hacer correctamente las tapas, (0,y,0).
   //Si queremos guardarlos para posteriormente insertarlos, hay que realizar lo siguiente:
   // si queremos eliminarlo lo quitamos del vector del perfil y posteriomente lo añadiremos.
   
    vector<Tupla3f> verticesGuardados;
   if(perfil_original[0][0] == 0 && perfil_original[0][2] == 0){
      verticesGuardados.push_back(perfil_original[0]);
      perfil_original.erase(perfil_original.begin());
   }else if(perfil_original[perfil_original.size()-1][0] == 0 && perfil_original[perfil_original.size()-1][2] == 0){
      verticesGuardados.push_back(perfil_original[perfil_original.size()-1]);
      perfil_original.erase(perfil_original.begin()+(perfil_original.size() -1));
      
   }
      
   //Comprobamos que se encuentran correctamente situados los vértices en plan en sentido 0,1,2 de forma descendente siendo 0 el de mayor altura.
   if(perfil_original.size() > 1)
      if(perfil_original[0](1) < perfil_original[1](1) ){ // hacemos un reverse del vector.
         vector<Tupla3f>::iterator first,last;
         first = perfil_original.begin();
         last = perfil_original.end();
         while ((first!=last)&&(first!=--last)) {
            iter_swap (first,last);
            ++first;
         }
         
      }
   
   //vértices
   for(int i = 0; i < num_instancias; i++)
      for(int j = 0; j < perfil_original.size(); j++){
         v.push_back(Tupla3f(
                     cos(2*PI*i/num_instancias)*perfil_original[j](0) + sin(2*PI*i/num_instancias)*perfil_original[j](2), //valor de x más la rotación
                     perfil_original[j](1),                                                                               //valor de y que no varía
                     cos(2*PI*i/num_instancias)*perfil_original[j](2) + sin(2*PI*i/num_instancias)*perfil_original[j](0)  //valor de z más una rotación
                     ));
      }
   
   //caras
   int a,b;
   for(int i = 0; i < num_instancias; i++)
      for(int j = 0; j < perfil_original.size()-1; j++){
         a = perfil_original.size()*i + j;
         b = perfil_original.size()*((i+1)%num_instancias) + j;
         f.push_back(Tupla3i(a,b,b+1));
         f.push_back(Tupla3i(a,b+1,a+1)); 
      }

   
   //tapa superior
   
	if(getTapaSuperior()){
      if(verticesGuardados.size() == 2){
         v.push_back(verticesGuardados[0]);
      }else if(verticesGuardados.size() == 1 && verticesGuardados[0](1) > perfil_original[0](1) ){
         v.push_back(verticesGuardados[0]);
      }else
         v.push_back(Tupla3f(0, perfil_original[0][1], 0));

		for(int i=0; i < num_instancias-1; ++i){
			f.push_back(Tupla3i(
                     v.size()-1,
                     (i+1)*(perfil_original.size()),
                     i*perfil_original.size()));
		}
		
		f.push_back(Tupla3i(v.size()-1,0,(num_instancias -1 )*perfil_original.size()));
   }
	
	//Tapa inferior
	if(perfil_original[perfil_original.size()-1][0] > 0 && getTapaInferior()){ //Comprobación Es decir el último punto no se encuentra apegado al eje 1 pudiéndose realizar la tapa.

         if(verticesGuardados.size() == 2){
            v.push_back(verticesGuardados[1]);
         }else if(verticesGuardados.size() == 1 && verticesGuardados[0](1) < perfil_original[0](1) ){
            v.push_back(verticesGuardados[0]);
         }else{
            v.push_back(Tupla3f(0, perfil_original[perfil_original.size()-1][1], 0));
            
         }

         for(int i=0; i< num_instancias-1; ++i)
            f.push_back(Tupla3i(
                        v.size()-1,
                        (i+1)*(perfil_original.size())-1,
                        (i+2)*(perfil_original.size())-1));

         int ultimoVerticeFigura;
         if(!getTapaSuperior())
            ultimoVerticeFigura = v.size()-2;
         else
            ultimoVerticeFigura = v.size()-3;

         f.push_back(Tupla3i(v.size()-1, ultimoVerticeFigura,perfil_original.size()-1)); //v.size()-2 sin polo norte v.size()-3 con polo norte
      
	}
}

void ObjRevolucion::crearMalla2(vector<Tupla3f> perfil_original, int num_instancias) {

   vector<float> distancias;
   
   
   //Eliminamos aquellos vértices que nos imposibilitan hacer correctamente las tapas, (0,y,0).
   //Si queremos guardarlos para posteriormente insertarlos, hay que realizar lo siguiente:
   // si queremos eliminarlo lo quitamos del vector del perfil y posteriomente lo añadiremos.
   
    vector<Tupla3f> verticesGuardados;
   if(perfil_original[0][0] == 0 && perfil_original[0][2] == 0){
      verticesGuardados.push_back(perfil_original[0]);
      perfil_original.erase(perfil_original.begin());
   }else if(perfil_original[perfil_original.size()-1][0] == 0 && perfil_original[perfil_original.size()-1][2] == 0){
      verticesGuardados.push_back(perfil_original[perfil_original.size()-1]);
      perfil_original.erase(perfil_original.begin()+(perfil_original.size() -1));
      
   }
   
   //Comprobamos que se encuentran correctamente situados los vértices en plan en sentido 0,1,2 de forma descendente siendo 0 el de mayor altura.
   if(perfil_original.size() > 1)
      if(perfil_original[0](1) < perfil_original[1](1) ){ // hacemos un reverse del vector.
         vector<Tupla3f>::iterator first,last;
         first = perfil_original.begin();
         last = perfil_original.end();
         while ((first!=last)&&(first!=--last)) {
            iter_swap (first,last);
            ++first;
         }
         
      }
   
   //vértices
   for(int i = 0; i < num_instancias; i++){

      for(int j = 0; j < perfil_original.size(); j++){
         v.push_back(Tupla3f(
                     cos(2*PI*i/num_instancias)*perfil_original[j](0) + sin(2*PI*i/num_instancias)*perfil_original[j](2), //valor de x más la rotación
                     perfil_original[j](1),                                                                               //valor de y que no varía
                     cos(2*PI*i/num_instancias)*perfil_original[j](2) + sin(2*PI*i/num_instancias)*perfil_original[j](0)  //valor de z más una rotación
                     ));
      }
   }



   //caras
   int a,b;
   for(int i = 0; i < num_instancias; i++)
      for(int j = 0; j < perfil_original.size()-1; j++){
         a = perfil_original.size()*i + j;
         b = perfil_original.size()*((i+1)%num_instancias) + j;
         f.push_back(Tupla3i(a,b,b+1));
         f.push_back(Tupla3i(a,b+1,a+1)); 
      }

   //Añadimos la última tira de caras
   
   for(int j = 0; j < perfil_original.size() -1; j++){
         a = perfil_original.size()*(num_instancias-1) + j;
         b = j+1;
         v.push_back(Tupla3f(
                     cos(2*PI*0/num_instancias)*perfil_original[j](0) + sin(2*PI*0/num_instancias)*perfil_original[j](2), //valor de x más la rotación
                     perfil_original[j](1),                                                                               //valor de y que no varía
                     cos(2*PI*0/num_instancias)*perfil_original[j](2) + sin(2*PI*0/num_instancias)*perfil_original[j](0)  //valor de z más una rotación
                     ));
         f.push_back(Tupla3i(j,j+1,a+1));
         f.push_back(Tupla3i(j,a+1,a)); 
   }
   //Coordenadas de textura
   distancias.push_back(0.0);
   for(int i = 1; i < perfil_original.size(); i++)
      distancias.push_back(distancias[i-1] + sqrt((perfil_original[i]-perfil_original[i-1]).lengthSq()));

   for(int i = 0; i < num_instancias; i++)
      for(int j = 0; j < perfil_original.size(); j++)
         ct.push_back(Tupla2f((float)i/(num_instancias-1) , 1 - (float)distancias[j] / distancias[perfil_original.size()-1]));
   //ct.push_back({0.0,0.0});
   //tapa superior
   
	if(getTapaSuperior()){
      if(verticesGuardados.size() == 2){
         v.push_back(verticesGuardados[0]);
      }else if(verticesGuardados.size() == 1 && verticesGuardados[0](1) > perfil_original[0](1) ){
         v.push_back(verticesGuardados[0]);
      }else
         v.push_back(Tupla3f(0, perfil_original[0][1], 0));

		for(int i=0; i < num_instancias-1; ++i){
			f.push_back(Tupla3i(
                     v.size()-1,
                     (i+1)*(perfil_original.size()),
                     i*perfil_original.size()));
		}
		
		f.push_back(Tupla3i(v.size()-1,0,(num_instancias -1 )*perfil_original.size()));
   }
	
	//Tapa inferior
	if(perfil_original[perfil_original.size()-1][0] > 0 && getTapaInferior()){ //Comprobación Es decir el último punto no se encuentra apegado al eje 1 pudiéndose realizar la tapa.

         if(verticesGuardados.size() == 2){
            v.push_back(verticesGuardados[1]);
         }else if(verticesGuardados.size() == 1 && verticesGuardados[0](1) < perfil_original[0](1) ){
            v.push_back(verticesGuardados[0]);
         }else{
            v.push_back(Tupla3f(0, perfil_original[perfil_original.size()-1][1], 0));
            
         }

         for(int i=0; i< num_instancias-1; ++i)
            f.push_back(Tupla3i(
                        v.size()-1,
                        (i+1)*(perfil_original.size())-1,
                        (i+2)*(perfil_original.size())-1));

         int ultimoVerticeFigura;
         if(!getTapaSuperior())
            ultimoVerticeFigura = v.size()-2;
         else
            ultimoVerticeFigura = v.size()-3;

         f.push_back(Tupla3i(v.size()-1, ultimoVerticeFigura,perfil_original.size()-1)); //v.size()-2 sin polo norte v.size()-3 con polo norte
      
	}
}


void ObjRevolucion::drawSinTapasDiferido()
{
   int numeroCaras = numInstancias;
   if(getTapaSuperior() && getTapaInferior()){
       numeroCaras = 2*numInstancias;
      
   }else if((getTapaSuperior() && !getTapaInferior()) || (!getTapaSuperior() && getTapaInferior()))
      numeroCaras = numInstancias;

   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   if (id_vbo_vertices == 0) 
      id_vbo_vertices = crearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),v.data());
   if (id_vbo_triangulos == 0)
      id_vbo_triangulos = crearVBO(GL_ELEMENT_ARRAY_BUFFER,3*(f.size()-numeroCaras)*sizeof(int),f.data());
   if (id_vbo_color == 0){
      // id_vbo_color = crearVBO(GL_ARRAY_BUFFER,3*color.size()*sizeof(float),color.data());
     
      if(solido)
         id_vbo_color = crearVBO(GL_ARRAY_BUFFER,3*color.size()*sizeof(float),color.data());
      if (lineas)
         id_vbo_color = crearVBO(GL_ARRAY_BUFFER,3*colorLineas.size()*sizeof(float),colorLineas.data());
      if(puntos)
         id_vbo_color = crearVBO(GL_ARRAY_BUFFER,3*colorPuntos.size()*sizeof(float),colorPuntos.data());
      if(amarillo)
         id_vbo_color = crearVBO(GL_ARRAY_BUFFER,3*colorAmarillo.size()*sizeof(float),colorAmarillo.data());
   }
   
   glBindBuffer(GL_ARRAY_BUFFER,id_vbo_vertices); //activar VBO de vértices
   glVertexPointer(3,GL_FLOAT,0,0);               //especificar formato y offset
   glBindBuffer(GL_ARRAY_BUFFER,0);               //desactivar VBO de vértices
   glEnableClientState(GL_VERTEX_ARRAY);          //habilitar tabla de vértices

   glBindBuffer(GL_ARRAY_BUFFER,id_vbo_color);     //activar VBO de colores
   glColorPointer(3,GL_FLOAT,0,0);      
   glBindBuffer(GL_ARRAY_BUFFER,0);                //desactivar VBO de colores
   glEnableClientState(GL_COLOR_ARRAY);            //habilitar colores
   
   if (glIsEnabled(GL_LIGHTING) == GL_TRUE && tieneMaterial){
      material.aplicar();
      if (id_vbo_normales == 0)
         id_vbo_normales = crearVBO(GL_ARRAY_BUFFER,3*nv.size()*sizeof(float),nv.data());
      
      glBindBuffer(GL_ARRAY_BUFFER,id_vbo_normales);     //activar VBO de normales
      glNormalPointer(GL_FLOAT,0,0);      
      glBindBuffer(GL_ARRAY_BUFFER,0);                //desactivar VBO de normales
      glEnableClientState(GL_NORMAL_ARRAY);           //Habilitamos normales

   }

   if (glIsEnabled(GL_TEXTURE_2D) == GL_TRUE){
      textura->activar();
      if(ct.size() == 0)
         asignacionTexturaAutomatica();
      else{
         if (id_vbo_textura == 0)
            id_vbo_textura = crearVBO(GL_ARRAY_BUFFER,2*ct.size()*sizeof(float),ct.data());
      
         glBindBuffer(GL_ARRAY_BUFFER,id_vbo_textura);     //activar VBO de normales
         glTexCoordPointer(2,GL_FLOAT,0,0);    
         glBindBuffer(GL_ARRAY_BUFFER,0);                //desactivar VBO de normales
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);           //Habilitamos normales
      }   
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_triangulos);
   
   
   glDrawElements(GL_TRIANGLES,3*(f.size()-numeroCaras), GL_UNSIGNED_INT,0);
   
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   
    //Desabilitamos la autoasignación de textura
   
   if(ct.size() == 0 && glIsEnabled(GL_TEXTURE_2D) == GL_TRUE){
      glDisable( GL_TEXTURE_GEN_S ); // desactivado inicialmente
      glDisable( GL_TEXTURE_GEN_T );
   }
   id_vbo_color = 0;//Permite que tengamos simultaneamente puntos,linea y solido, o cualquier combinación de ellos
}

void ObjRevolucion::drawSinTapasAjedrez(){
   //Buscamos las instacias de caras a quitar
   int numeroCaras = numInstancias;
   if(getTapaSuperior() && getTapaInferior()){
       numeroCaras = 2*numInstancias;
      
   }else if((getTapaSuperior() && !getTapaInferior()) || (!getTapaSuperior() && getTapaInferior()))
      numeroCaras = numInstancias;

   glEnableClientState(GL_COLOR_ARRAY);
  //Habilitamos el array de vértices
  glEnableClientState(GL_VERTEX_ARRAY);
  //Especificamos la tabla de coordenadas de los vértices
  glVertexPointer(3,GL_FLOAT,0,v.data());

   vector<Tupla3i> pares,impares; 
   for(int i = 0; i < (f.size()-numeroCaras); i++){
      if(i%2 == 0){
         pares.push_back(f[i]);         
      }else{
         impares.push_back(f[i]);
      }
         
   } 

   glColorPointer(3,GL_FLOAT,0,color.data());
   glDrawElements(GL_TRIANGLES,3*pares.size(), GL_UNSIGNED_INT,pares.data());

   glColorPointer(3,GL_FLOAT,0,color2Ajedrez.data());
   glDrawElements(GL_TRIANGLES,3*impares.size(), GL_UNSIGNED_INT,impares.data());
  
  //Desabilitamos el array de vértices.
  glDisable(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);//PREGUNTAR SI SERÍA CORRECTO;
}

void ObjRevolucion::draw(int modo,bool ajedrez, bool tapas){
   if (tapas){
      if(ajedrez)
         draw_ajedrez();
      else if (modo == 1)
         draw_ModoInmediato();
      else
         draw_ModoDiferido();
   }else if(ajedrez)
      drawSinTapasAjedrez();
      else if(modo == 1)
         drawSinTapasInmediato();
      else
         drawSinTapasDiferido();
      
}