#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'
// Interfaz en el dibujado
void Malla3D::draw_ModoInmediato()
{

   if (glIsEnabled(GL_TEXTURE_2D) == GL_TRUE && textura != nullptr){
      if(ct.size() == 0 ){
         asignacionTexturaAutomatica();
      }else{
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2,GL_FLOAT,0,ct.data());
         
      }
      textura->activar();
      
   }

   if (glIsEnabled(GL_LIGHTING) == GL_TRUE){
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_FLOAT,0,nv.data());
      material.aplicar();
      
   }
      glEnableClientState(GL_COLOR_ARRAY);

      //glColorPointer(3,GL_FLOAT,0,color.data());
      if(solido){
         glColorPointer(3,GL_FLOAT,0,color.data());
      }else if(lineas)
         glColorPointer(3,GL_FLOAT,0,colorLineas.data());
      else if(puntos)
         glColorPointer(3,GL_FLOAT,0,colorPuntos.data());
      else if(amarillo){
         glColorPointer(3,GL_FLOAT,0,colorAmarillo.data());
      }
         
   
   
   
  //Habilitamos el array de vértices
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,v.data());//Especificamos la tabla de coordenadas de los vértices
  glDrawElements(GL_TRIANGLES,3*f.size(), GL_UNSIGNED_INT, f.data());//dibujamos los triangulos indexados
  
  //Desabilitamos el array de vértices.
   glDisable(GL_VERTEX_ARRAY);
   
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glBindTexture(GL_TEXTURE_2D, 0);

   //Desabilitamos la autoasignación de textura
   if(ct.size() == 0 && glIsEnabled(GL_TEXTURE_2D) == GL_TRUE){
      glDisable( GL_TEXTURE_GEN_S ); // desactivado inicialmente
      glDisable( GL_TEXTURE_GEN_T );
   }
   //glDisable(GL_LIGHTNING);
   
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
GLuint Malla3D::crearVBO(GLuint tipo_vbo,GLuint tamanio_bytes, GLvoid * punturo_ram){
   GLuint id_vbo;
   glGenBuffers(1,&id_vbo);
   glBindBuffer(tipo_vbo,id_vbo);
   glBufferData(tipo_vbo,tamanio_bytes,punturo_ram,GL_STATIC_DRAW);
   glBindBuffer(tipo_vbo,0);
   return id_vbo;
}
void Malla3D::draw_ModoDiferido()
{

   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   if (id_vbo_vertices == 0) 
      id_vbo_vertices = crearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),v.data());
   if (id_vbo_triangulos == 0)
      id_vbo_triangulos = crearVBO(GL_ELEMENT_ARRAY_BUFFER,3*f.size()*sizeof(int),f.data());
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
      glEnableClientState(GL_NORMAL_ARRAY);    //Habilitamos normales
      

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
   
   
   glDrawElements(GL_TRIANGLES,3*f.size(), GL_UNSIGNED_INT,0);
   
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);

   //Desabilitamos la autoasignación de textura
   if(ct.size() == 0 && glIsEnabled(GL_TEXTURE_2D) == GL_TRUE){
      glDisable( GL_TEXTURE_GEN_S ); // desactivado inicialmente
      glDisable( GL_TEXTURE_GEN_T );
   }
   //setAFalseColores();
   id_vbo_color = 0; // para permitir pintar los objetos con puntos, lineas y solido de colores difrerentes

}

void Malla3D::draw_ajedrez(){
   
   glEnableClientState(GL_COLOR_ARRAY);
  //Habilitamos el array de vértices
  glEnableClientState(GL_VERTEX_ARRAY);
  //Especificamos la tabla de coordenadas de los vértices
  glVertexPointer(3,GL_FLOAT,0,v.data());

   vector<Tupla3i> pares,impares; 
   for(int i = 0; i < f.size(); i++){
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

void Malla3D::setColor(const Tupla3f rgb){
   for(int i = 0; i < color.size(); i++){
      color[i]=rgb;
   }
      

}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(int modo, bool ajedrez)
{
   if(ajedrez)
      draw_ajedrez();
   else if(modo == 1)
      draw_ModoInmediato();
   else
      draw_ModoDiferido();
   
   

}

void Malla3D::calcular_normales(){
   //Obtenemos las normales de las caras
   vector<Tupla3f> aux;
   vector<Tupla3f> nc;
   aux.resize(v.size());
   for(int i= 0; i < aux.size(); i++)
      aux[i] = Tupla3f(0.0,0.0,0.0);
   
   Tupla3f producVec,a,b,p,q,r;
   
   for(int i = 0; i < f.size(); i++){
      //PRODUCTO VECTORIAL
      p = v[f[i][0]];
      q = v[f[i][1]];
      r = v[f[i][2]];

      a = q-p;
      b = r-p;
      producVec = a.cross(b);
    

      //NORMALIZAMOS
    //  producVec = producVec.normalized();
     
      aux[f[i][0]] = aux[f[i][0]] + producVec;
      aux[f[i][1]] = aux[f[i][1]] + producVec;
      aux[f[i][2]] = aux[f[i][2]] + producVec;
         
   }

   for(int i = 0; i< aux.size(); i++)
      nv.push_back(aux[i].normalized());
   

   

      
}



void Malla3D::setMaterial( const Material m){
      material = m;
      tieneMaterial = true;
} 

Material Malla3D::getMaterial()const{
   return material;
}

void Malla3D::aplicarMaterial(){
   material.aplicar();
}

void Malla3D::asignacionTexturaAutomatica(){
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);

   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
}


 
void Malla3D::setColorSeleccionado(int color){
   
   switch (color)
   {
   case 1: //linea
      lineas = true;
      break;
   case 2: //puntos
      puntos = true;
      break;

   case 3: //solido
      solido = true;
      break;
   case 4: //amarillo
      amarillo = true;
      break;

   }
}

void Malla3D::setAFalseColores(){
   lineas = solido = puntos = amarillo = false;
}

void Malla3D::escalarCoordenadasTextura(int escalar){
   for(int i = 0; i < ct.size(); i++)
      ct[i] = ct[i]*escalar;
}