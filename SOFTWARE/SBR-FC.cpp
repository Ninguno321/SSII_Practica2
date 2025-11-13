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
            Nment=seleccionarMeta(NuevasMetas);
            Eliminar(NMet,NuevasMetas);
            Verificado=VERIFICAR(Nmet,BH);
        si Verificado entonces Añadir(Meta,BH);
    devolver(Verificado);

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
#include <vector>

using namespace std;

enum operador {AND, OR};

struct Regla {
    string id;                      //Identificador de la regla
    vector<string> antecedentes;    //Almacenamiento de los antecedentes
    operador op;                //Operador usado en la regla, AND u OR
    string consecuente;             //Almacenamiento del consecuente
    double fc;                      //Factor de certeza de la regla
};


vector<Regla> BC;                   //Vector de tipo Regla para la base de conocimientos
map<string, double> BH;             //Map para la base de hechos
string OBJETIVO;                    //Global para el objetivo


/*
double combinaFC(Regla e1){
    
    //CASO 1
    if (e1.op == AND || e1.op == OR){
        if (e1.op == AND)
            return min(BH[e1.antecedentes[0]], BH[e1.antecedentes[1]]);  //Lo estoy haciendo solo para dos pero puede que sean muchos mas antecedentes
        else return max(BH[e1.antecedentes[0]], BH[e1.antecedentes[1]]);
    }else if () {

    }

    //CASO 2


    //CASO 3
}
*/


/*R1: Si h2 o h3 Entonces h1, FC=0.5*/
void rellenaBC(string & linea){
    //h2, FC=0.3
    size_t pos_dpuntos = linea.find(':');
    string id = linea.substr(0, pos_dpuntos);
    
    //Falta sacar el operador y los antecedentes.

    size_t pos_entonces = linea.find("Entonces");
    size_t pos_coma = linea.find(',');
    string consecuente = linea.substr(pos_entonces+1, pos_coma);

    size_t pos_igual = linea.find('=');
    string fc = linea.substr(pos_igual+1);

    cout << "Rellenando los valores de la regla" << endl;
    Regla re;
    re.id = id;
    re.antecedentes;
    re.consecuente = consecuente;
    re.fc = stod(fc);
    cout << "Rellenando el vector" << endl;
    BC.push_back(re);
    
    
    /*
    vector<string> antecedentes;    //Almacenamiento de los antecedentes
    operador op;                //Operador usado en la regla, AND u OR
    string consecuente;             //Almacenamiento del consecuente
    double fc; 
    
    */
}

//primero tenemos que leer la base de conocimientos y luego la de hechos.
//Está sin modificar, lo hace mal.
/*
4
R1: Si h2 o h3 Entonces h1, FC=0.5
*/
void leer_BC(string & BC){
    ifstream archivo(BC); // 1. Crea un objeto ifstream y lo asocia al archivo
    string linea;
    int n;
    string basura;

    if (archivo.is_open()) { // 2. Comprueba si el archivo se abrió correctamente
        archivo >> n;
        archivo.ignore(); // ignoramos el salto de linea.
        for (int i = 0 ;  i < n ; i++){
            getline(archivo, linea);
            rellenaBC(linea);
        }
        archivo.close(); // 4. Cierra el archivo
    } else {
        cerr << "No se pudo abrir el archivo " << BC << " para lectura. Asegúrate de que existe." << endl;
    }
}

//hace las cosas bien en principio 
void rellenaBH(string & linea){
    //h2, FC=0.3
    size_t pos_coma = linea.find(',');
    string hecho = linea.substr(0, pos_coma);
    
    size_t pos_igual = linea.find('=');
    string fc = linea.substr(pos_igual+1);


    size_t pos_igual = linea.find('=');
    string fc = linea.substr(pos_igual+1);

    cout << "Rellenando el mapa" << endl;
    cout << hecho << " y "<<fc << endl;
    BH[hecho] = stod(fc);
}

//Tambien lo hace bien, según yo.
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






















