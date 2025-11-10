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

ecutable en windows.  - SBR-FC debe ejecutarse en línea de comando con parámetros “BC” y “BH” (en este orden).   - La salida debe generar un fichero (donde el nombre de fichero debe indicar a qué base de 
hechos y de conocimiento corresponde). Este fichero de salida debe contener:   
o los nombres de la BC y BH utilizados,  
o el objetivo y, 
o el proceso de inferencia seguido para obtener la solución.  
Este proceso de inferencia será como un “log” del proceso seguido en la resolución del caso. 
A modo de ejemplo, véase la salida mostrada en la transparencia 15 del documento “P2.1
Fundamentos-Teoricos.pdf”. En esa salida deben incluirse obligatoriamente las activaciones 
de las reglas y hechos con los FCs. Estas activaciones deben mostrarse como:  
··· 
Ri  (regla activada) 
Caso 1  (si se necesita): hecho, FC 
Caso 3: hecho, FC 
··· 
Caso 2: hecho, FC 
··· 
Objetivo, FC=… 

        */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


map<string, double> BaseHechos;
string OBJETIVO;

//primero tenemos que leer la base de conocimientos y luego la de hechos.

void leer_BC(string & BC){
    ifstream archivo(BC); // 1. Crea un objeto ifstream y lo asocia al archivo
    string linea;

    if (archivo.is_open()) { // 2. Comprueba si el archivo se abrió correctamente
        while (archivo >> linea) { // 3. Lee línea por línea hasta el final
            cout << "Leído: " << linea << endl;
        }
        archivo.close(); // 4. Cierra el archivo
    } else {
        cerr << "No se pudo abrir el archivo " << BC << " para lectura. Asegúrate de que existe." << endl;
    }
}


void rellenaBH(string & linea){
    //h2, FC=0.3
    size_t pos_coma = linea.find(',');
    string hecho = linea.substr(0, pos_coma);
    
    size_t pos_igual = linea.find('=');
    string fc = linea.substr(pos_igual+1);

    cout << "Rellenando el mapa" << endl;
    cout << hecho << " y "<<fc << endl;
    BaseHechos[hecho] = stod(fc);
}

void leer_BH(string & BH){
    ifstream archivo(BH); // 1. Crea un objeto ifstream y lo asocia al archivo
    string linea;
    int n;
    string basura;

    if (archivo.is_open()) { // 2. Comprueba si el archivo se abrió correctamente
        archivo >> n;
        archivo.ignore(); // ignoramos el salto de linea.
        for (int i = 0 ;  i < n ; i++){
            getline(archivo, linea);
            rellenaBH(linea);
        }
        archivo >> basura;
        archivo >> OBJETIVO;
        cout << "Leído OBJETIVO: " << OBJETIVO << endl;

        archivo.close(); // 4. Cierra el archivo
    } else {
        cerr << "No se pudo abrir el archivo " << BH << " para lectura. Asegúrate de que existe." << endl;
    }
}




int main(int argc, char * argv[]){
    /* BASE DE CONOCIMIENTOS
    4
    R1: Si h2 o h3 Entonces h1, FC=0.5
    R2: Si h4 Entonces h1, FC=1
    R3: Si h5 y h6 Entonces h3, FC=0.7
    R4: Si h7 Entonces h3, FC=-0.5
    */
   //string ficheroBC = argv[1];
   string ficheroBH = argv[2];
    
   //leer_BC(ficheroBC);
   leer_BH(ficheroBH);
   

}






















