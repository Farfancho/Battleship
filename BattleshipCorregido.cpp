#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int numerosValidos [10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 
const string filename = "historial.txt";
const string barcos[6] = {"Acorazado","Cazasubmarinos","Destructor","Explorador","Fragata","Navio"};

struct Jugador
{
    string nombre;
    int partidasGanadas;
    int partidasPerdidas;
    string matrizDefensiva[10][10];
    string matrizAtacante[10][10];
    Jugador(){}//? constructor vacio (por si algo)
    Jugador(string nombre, int partidasGanadas, int partidasPerdidas){
        this -> nombre = nombre;
        this -> partidasGanadas = partidasGanadas;
        this -> partidasPerdidas = partidasPerdidas;
    }
};

//funciones para cambiar nombres, añadirlos al archivo y obtener informacion
Jugador nombres(int indice);
Jugador asignar(Jugador &e, string nombre);
bool VerificarNombres(string nombre);
//Funciones para jugar
void vaciarMatrizJugador(Jugador &e);
bool verificarNumero(int n);

int main(){
    string frase;
    Jugador e1 = nombres(1);
    Jugador e2 = nombres(2);
    while (true)
    {
        system("clear");
        cout<<"Ingrese una accion!\n"<<
            "1. jugar\n"<<
            "2. cambiar nombres\n"<<
            "3. historial\n"<<
            "Otra. salir"<<endl;
        getline(cin, frase);
        if(frase == "1"){//TODO jugar
            vaciarMatrizJugador(e1);
            vaciarMatrizJugador(e2);
        }
        else if(frase == "2"){//! Terminado nombres
            system("clear");
            e1 = nombres(1);
            e2 = nombres(2);
        }
        else if(frase == "3"){//TODO Historial

        }
        else{
            cout<<"Gracias por Jugar"<<endl;
            exit(1);
        }
    }
    
    return 0;
}

void vaciarMatrizJugador(Jugador &e){
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            e.matrizAtacante[i][j] = " ";
            e.matrizDefensiva[i][j] = " ";
        }
    }
}

int capturarCoordenadas(){
    string frase;
    getline(cin, frase);
    int n = stoi(frase);
    if(verificarNumero(n) == false)
        capturarCoordenadas();
    return n;
}

bool verificarNumero(int n){
    for(int i = 0; i < 10; i++){
        if(n == numerosValidos[i])
            return true;
    }
    return false;
}

void definirTableros(Jugador &e){
//! Se requiere un apuntador a una matriz
}


Jugador nombres(int indice){
    Jugador e;
    string frase;
    cout<<"Jugador "<< indice <<", ingrese su nombre: "<<endl;
    getline(cin, frase);
    e.nombre = frase;
    if(VerificarNombres(e.nombre) == true){
        e = asignar(e, e.nombre);
    }
    return e;
}

Jugador asignar(Jugador &e, string nombre){
    string frase;
    ifstream file(filename);
    while(getline(file,frase)){
        stringstream ss(frase);
        ss >> e.nombre >> e.partidasGanadas >> e.partidasPerdidas;
        if(e.nombre == nombre)
            return e;        
    }
    return e;
}

bool VerificarNombres(string nombre){
    Jugador e;
    string frase;
    ifstream file(filename);
    while (getline(file, frase)){
        stringstream ss(frase);
        ss >> e.nombre >> e.partidasGanadas >> e.partidasPerdidas;
        if(nombre == e.nombre)
            return true;
    }
    ofstream fileToWrite(filename, ios::app);
    fileToWrite << "\n" << nombre <<" "<< 0 << " "<< 0;
    return false;
}

