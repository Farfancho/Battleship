#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

string tableroJugador1[10][10];
string tableroJugador2[10][10];
string ataqueJuga1[10][10];
string ataqueJuga2[10][10];
int X,Y;
string barcos[6] = {"P","P","C","D","E","F"};
string jugadores[2];
bool continuar = true;
string perdedor;
string ganador;
int puntuacionJuga1 = 0;
int puntuacionJuga2 = 0;
bool finalizacion;
string temp;

string Nombres[5];
string puntos [5];

void interfaz();
void tableros(string matrizDefensiva[][10], string jugador);
void imprimirMatriz(string matrizDefensiva[][10]);
void rotaciones(string  matrizDefensiva[][10], int tamano);
void coordenadas();
bool comprobacion(string matrizDefensiva[][10], char opcion, int tamano);
void errorColision();
void errorLimite();
void jugar();
void nombres();
void terminar();
bool vacia(string matrizDefensiva[][10]);
void ataque(string matrizDefensiva[][10], string matrizOfensiva[][10], string MatrizDefRival[][10], string jugador);
void felicitaciones();
void imprmirArchivo();
void leerArchivo();
void escribirArchivo();
void historial();
bool hundido(string matrizDefRival[][10]);

int main()
{
    nombres();
    interfaz();
}
void interfaz()
{
    finalizacion = false;
    system("cls");
    cout<<"Que accion desea realizar?"<<endl;
    cout<<"1. jugar"<<endl;
    cout<<"2. cambiar nombres"<<endl;
    cout<<"3. historial"<<endl;
    cout<<"4. salir"<<endl;
    char opcion = _getche();
    switch(opcion)
    {
    case '1':
        jugar();
        break;
    case '2':
        nombres();
        interfaz();
        break;
    case '3':
        historial();
        getch();
        interfaz();
        break;
    case '4':
        terminar();
        break;
    default:
        interfaz();
    }
}
void jugar()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            tableroJugador1[i][j] = " ";
            tableroJugador2[i][j] = " ";
            ataqueJuga1[i][j] = " ";
            ataqueJuga2[i][j] = " ";
        }
    }
    tableros(tableroJugador1, jugadores[0]);
    tableros(tableroJugador2, jugadores[1]);
    while(finalizacion == false)
    {
        ataque(tableroJugador1, ataqueJuga1, tableroJugador2, jugadores[0]);
        if(finalizacion == true)
            break;
        ataque(tableroJugador2, ataqueJuga2, tableroJugador1, jugadores[1]);
    }
    felicitaciones();
    interfaz();

}
void tableros(string matrizDefensiva [][10], string jugador)
{
    for(int k = 5; k > 1; k--)
    {

        //int k = 1; //provisional
        if(k == 2)
        {
            while(continuar == true)
            {
                k++;
                continuar = false;
            }
        }
        system("cls");
        cout<<jugador<<" ingrese coordenadas de su barco de "<<k<<" posiciones"<<endl;
        coordenadas();
        if(matrizDefensiva[Y][X] != " ")
        {
            cout<<"La coordenada esta ocupada"<<endl;
            coordenadas();
        }
        rotaciones(matrizDefensiva, k);
        imprimirMatriz(matrizDefensiva);
    }
    continuar = true;
}
void imprimirMatriz(string matrizDefensiva[][10])
{
    system("cls");
    cout<<"X  ";
    for (int i = 0; i < 10; i++) {
        cout<<i<<"   ";
    }
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        cout<<i<<" ";
        for (int j = 0; j < 10; j++)
        {
            cout<<"["<<matrizDefensiva[i][j]<<"] ";
        }
        cout<<endl;
    }
    getch();
}
void coordenadas()
{
    cin>>Y;
    while(Y < 0 or Y > 9)
    {
        cout<<"La coordenada se sale del tablero "<<endl;
        cin>>Y;
    }

    while (cin.fail())
    {
        cout <<"El tipo de dato no concuerda con el requerido ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> Y;
    }

    cin>>X;
    while(X < 0 or X > 9)
    {
        cout<<"La coordenada se sale del tablero "<<endl;
        cin>>X;
    }

    while (cin.fail())
    {
        cout <<"El tipo de dato no concuerda con el requerido ";
        cin.clear();
        cin.ignore(256, '\n');
        cin>>X;
    }
}
void rotaciones(string matrizDefensiva[][10], int tamano)
{
    system("cls");
    cout<<"como desea orientar su barco?"<<endl;
    cout<<"(1) 90 grados a la derecha / abajo "<<endl;
    cout<<"(2) 90 grados a la izquierda / arriba "<<endl;
    cout<<"(3) 180 grados / izquierda "<<endl;
    cout<<"(4) No rotar / derecha "<<endl;
    cout<<"(5) Cambiar coordenada"<<endl;
    char orientacion = _getche();
    comprobacion(matrizDefensiva, orientacion, tamano);
    if(orientacion == '5')
    {
        system("cls");
        cout<<"ingrese las coordenadas nuevamente: "<<endl;
        coordenadas();
        rotaciones(matrizDefensiva, tamano);
    }
    else if(comprobacion(matrizDefensiva, orientacion, tamano) == false)
    {
        rotaciones(matrizDefensiva,tamano);
    }
    else
    {
        switch(orientacion)
        {
        case '1': // abajo
            for(int i = 0; i < tamano; i++)
            {
                matrizDefensiva[Y + i][X] = barcos[tamano];
            }
            break;
        case '2': //arriba
            for(int i = 0; i < tamano; i++)
            {
                matrizDefensiva[Y - i][X] = barcos[tamano];

            }
            break;
        case'3': //izquierda
                for(int i = 0; i < tamano; i++)
                {
                    matrizDefensiva[Y][X - i] = barcos[tamano];
                }
            break;
        case'4': //derecha
                for(int i = 0; i < tamano; i++)
                {
                    matrizDefensiva[Y][X + i] = barcos[tamano];
                }
            break;
        default:
            imprimirMatriz(matrizDefensiva);
            break;
        }
    }
}
bool comprobacion(string matrizDefensiva[][10], char opcion, int tamano)
{
    switch(opcion)
    {
    case '1': //abajo
        if((Y + tamano) > 10)
        {
            errorLimite();
            return false;
        }
        else
        {
            for(int i = 0; i < tamano; i++)
            {
                if(matrizDefensiva[Y + i][X] != " ")
                {
                    errorColision();
                    return false;
                }
            }
        }
        return true;
    case '2'://arriba
        if((Y - tamano) < -1)
        {
            errorLimite();
            return false;
        }
        else
        {
            for(int i = 0; i < tamano; i++)
            {
                if(matrizDefensiva[Y - i][X] != " ")
                {
                    errorColision();
                    return false;
                }
            }
        }
        return true;
    case'3'://izquierda
            if((X - tamano) < -1)
            {
                errorLimite();
                return false;
            }
            else
            {
                for(int i = 0; i < tamano; i++)
                {
                    if(matrizDefensiva[Y][X - i] != " ")
                    {
                        errorColision();
                        return false;
                    }
                }
            }
            return true;
    case'4': //derecha
            if((X + tamano) > 10)
            {
                errorLimite();
                return false;
            }
            else
            {
                for(int i = 0; i < tamano; i++)
                {
                    if(matrizDefensiva[Y][X + i] != " ")
                    {
                        errorColision();
                        return false;
                    }
                }
            }
            return true;
    default:
        return false;
    }
}
void errorLimite()
{
    system("cls");
    cout<<"\nEl barco se sale de los limites establecidos"<<endl;
    getch();
}
void errorColision()
{
    cout<<"Su barco ha colisionado con otros"<<endl;
    getch();
}
void nombres()
{
    system("cls");
    cout<<"ingrese el nombre del jugador 1: "<<endl;
    //getline(cin, jugadores[0]);
    cin>>jugadores[0];
    cout<<"ingrese el nombre del jugador 2: "<<endl;
    cin>>jugadores[1];
    //getline(cin, jugadores[1]);
}
void terminar()
{
    system("cls");
    cout<<"Gracias por jugar"<<endl;
    getch();
    exit(1);
}
void ataque(string matrizDefensiva[][10], string matrizOfensiva[][10], string MatrizDefRival[][10], string jugador)
{
    system("cls");
    cout<<jugador<<" ingrese una coordenada a atacar"<<endl;
    coordenadas();
    while(MatrizDefRival[Y][X] == "x" or MatrizDefRival[Y][X] == "o")
    {
        cout<<"no se puede atacar dos veces una misma coordenada"<<endl;
        coordenadas();
    }
    if(MatrizDefRival[Y][X] != " ")
    {
        temp = MatrizDefRival[Y][X];
        MatrizDefRival[Y][X] = "x";
        cout<<"Impacto en la coordenada "<<Y<<" "<<X<<endl;
        if(hundido(MatrizDefRival) == true)
        {
            cout<<"se ha hundido un barco";
        }
        matrizOfensiva[Y][X] = "x";
        getch();
        cout<<jugador<<" esta es su matriz ofensiva"<<endl;
        getch();
        imprimirMatriz(matrizOfensiva);
        system("cls");
        cout<<jugador<<" esta es su matriz defensiva"<<endl;
        getch();
        imprimirMatriz(matrizDefensiva);
    }
    else
    {
        cout<<"Fallaste en la coordenada "<<Y<<" "<<X<<endl;
        matrizOfensiva[Y][X] = "o";
        MatrizDefRival[Y][X] = "o";
        getch();
        cout<<jugador<<" esta es su matriz ofensiva"<<endl;
        getch();
        imprimirMatriz(matrizOfensiva);
        system("cls");
        cout<<jugador<<" esta es su matriz defensiva"<<endl;
        getch();
        imprimirMatriz(matrizDefensiva);
    }
    finalizacion = vacia(MatrizDefRival);
    if(finalizacion == true)
        {
            ganador = jugador;
            if(jugador == jugadores[0]){
                puntuacionJuga1 = puntuacionJuga1 + 1;
            }else{
                puntuacionJuga2 = puntuacionJuga2 + 1;
            }
        }

}
bool vacia(string matrizDefensiva[][10])
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(matrizDefensiva[i][j] == "x" or matrizDefensiva[i][j] == " "){}
            else
            return false;
        }
    }
    return true;
}
bool hundido(string matrizDefRival[][10])
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(matrizDefRival[i][j] == temp)
                return false;
        }
    }
    return true;
}



void felicitaciones()
{
    system("cls");
    cout<<"Felicidades "<<ganador<<" juegue otra vez para obtener mas puntos.";
    getch();
}


void imprimirArchivo()
{
    ifstream archivo;
    archivo.open("historial.txt",ios::in);
    if (!archivo)
    {
        cout<<"No se pudo abrir"<<endl;
        return;
    }
    string linea;
    int contador = 0;
    while (getline(archivo, linea))
    {
        if (contador % 2 == 0)
        {
            cout << "Jugador: " << linea << " - ";
        }
        else
        {
            cout << "Puntaje: " << linea << endl;
        }
        contador++;
    }

    archivo.close();
}

void leerArchivo()
{
    ifstream archivo;
    archivo.open("historial.txt", ios::in);
    if (!archivo)
    {
        cout <<"No se pudo abrir"<< endl;
        return;
    }
    string linea;
    int contadorLineas = 0;
    int contadorGrupos = 0;
    while (getline(archivo, linea))
    {
        if (contadorLineas % 2 == 0)
        {
            Nombres[contadorGrupos] = linea;
        }
        else
        {
            puntos[contadorGrupos] = linea;
            contadorGrupos++;
        }
        contadorLineas++;
    }
    archivo.close();
}

void escribirArchivo()
{
    ofstream archivo;
    archivo.open("historial.txt", ios::app);
    if (!archivo)
    {
        cout << "No se pudo abrir" << endl;
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        archivo << jugadores[i] << endl;
        if (i == 0)
            archivo << puntuacionJuga1 << endl;
        else
            archivo << puntuacionJuga2 << endl;
    }
    archivo.close();
}
void historial()
{
    system("cls");
    escribirArchivo();
    leerArchivo();
    imprimirArchivo();
}
