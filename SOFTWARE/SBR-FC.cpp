/*
El fichero conteniendo la BC tendrá la siguiente estructura (palabras utilizadas no sensitivas):  
Nº Reglas 
Identificador: Regla, factor 
Reglas junto con su factor de certeza 
…..  - “Nº Reglas” indica la cantidad de reglas que compone la BC. - El “Identificador” está dado como Ri (desde i=1 hasta el Nº Reglas) - La “Regla” tendrá la forma Si  Entonces  donde  puede ser un literal, una conjunción de 
literales o una disyunción de literales, y   es un literal; y “factor” indica el factor de certeza 
asignado a la “regla”. Este se representa con FC=nº donde nº[-1,1] y “FC=” palabra reservada. 

• El fichero conteniendo la BH tendrá la forma siguiente (palabras utilizadas no sensitivas): 
Nº Hechos 
hecho, factor 
….. 
Objetivo 
hechoOBJ 
Hechos de entrada junto con su factor de certeza - “Nº Hechos” indicando la cantidad de hechos. - El “hecho” representa cada uno de los hechos de entrada y “factor” indica el factor de certeza 
asignado al “hecho”. Este se representa con FC=nº donde nº[-1,1] y “FC=” palabra reservada. - “Objetivo” palabra reservada.  -  
Y “hechoOBJ” será un atributo concreto que actuará como objetivo.  

Para ello, diseñaremos (e implementaremos) un motor de 
inferencia con encadenamiento hacia atrás adaptado al nuevo conocimiento disponible.



funcion ENCADENAMINETO-HACIA-ATRAS
BH = HechosIniciales;
Si verificar(Meta,BH) entonces devolver "exito";
si no devolver "fracaso"


funcion VERIFICAR
verificado=Falso;
si Contenida(Meta, BH) entonces devolver Verdadero
si no 
    CC = Equiparar(consecuentes(BC), Meta);
    mientras NoVacio(CC) y NO(Verificado) hacer
        R=Resolver(CC)
        Eliminar(R,CC);
        NuevasMetas=ExtraerAntecedentes(R);
        Verificado=Verdadero;
        MIENTRAS noVacio(NuevasMetas) y Verificado hacer
*/

#include <iostream>
using namespace std;

int main(int argc, char * argv[]){
    cout << "hola" << endl;
}






















