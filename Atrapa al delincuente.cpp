#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<time.h>
#include<fstream>

int score = 0;

int vidas = 0;

int Tiempo = 0;

int op = 0;

int dato_aux1 = 0, dato_aux2 = 0;

bool alive = true;

//POWER UPS
int vel = 0;
bool family_L = false;
int freeze_time = 0;

//Armas
int *POWER;
int numero_p;
int borrar[3];
int arma[4];
int arma_num = 1;
int direc = 0;

struct coordenadas
{
    double x;
    double y;
    int exist;
}bala,bala1,bala2,bala3;

struct objeto{
    int value;
    coordenadas coord;
}object;

struct Personaje
{
    int direccion;
    coordenadas coord, balas[4];
}jugador, ladron, policia, ladrones[4];

int numl = 1;

using namespace std;

void you_lose();

void ocultar_mostar_consola(int i);

float distancia_entre_dos_puntos(int x1, int y1, int x2, int y2);

void gotoxy(double x, double y);

bool no_press_key();

void fondo();

void fondo1();

void guia();

void menu();

void menu1();

void spawn_criminal_mode();

void spawn_police_mode();

int numero_majico(int limI,int limS);

void movimiento_Ladrones(int NUM);

void ataque_ladrones(int NUM);

void borrar_balas(int NUM);

void movimiento_ladron();

void ataque_ladron();

void borrar_bala();

void respawn_policia();

void respawn_criminal(int&i);

void movimiento_policia();

void ataque_policia(int NUM);

void mostrar_arma();

void aumentar_tiempo();

void anadir_elemento(int XXX);

void delete_element(int XXX);

void GET_power();

void power_up();

void jugador_controles_ladron();

void mostrar_vida();

void game_ladron();

void game_policia();

int main(){
	object.value = 0;
    op = 1;
    Tiempo = 60;
    vidas = 5;
    arma[0] += 10;
    system("title Atrapa al delincuente!!!");
    system("cls");
    ocultar_mostar_consola(0);
    fondo();
    fondo1();
    ocultar_mostar_consola(1);

    menu();
    numero_p = 6;
    POWER = new int[numero_p];
    for(int i = 0; i < numero_p; i++)
    {
    	POWER[i] = i + 1;
	}

    if (op == 1)
    {
        arma[0] = 10;
        arma[1] = 0;
        arma[2] = 0;
        arma[3] = 0;
        game_ladron();
    }

    if (op == 2)
    {
        ladrones[0].coord.x = 0;
        for(int i = 1; i < 4; i++)
        {
            ladrones[i].coord.x = -1;
        }
        arma[0] = 100;
        arma[1] = 500;
        arma[2] = 400;
        arma[3] = 50;
        game_policia();
    }

    if(op == 3)
    {
        guia();
    }

    if (op != 4)
    {
        main();
    }
    
    ocultar_mostar_consola(0);

    delete POWER;
    return 0;
}

void you_lose(){
    system("cls");
    fondo1();
    gotoxy(53,15);
    cout<<"Has perdido";
    gotoxy(39,16);
    cout<<"Presione cualquier tecla para continuar";
    Sleep(1000);
    system("pause>nul");
}

void ocultar_mostar_consola(int i){
    HWND console = FindWindow("ConsoleWindowClass",NULL);
    if (i == 0)
    {
        ShowWindow(console,NULL);
    }
    else
    {
        ShowWindow(console,1);
    }
    
}

float distancia_entre_dos_puntos(int x1, int y1, int x2, int y2){
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

void gotoxy(double x, double y){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwpos;

    dwpos.X = x;
    dwpos.Y = y;

    SetConsoleCursorPosition(hcon,dwpos);
}

bool no_press_key(){

    if(GetAsyncKeyState(VK_UP) == -32767 || GetAsyncKeyState('W') == -32767)
    {
        return false;
    }
    if(GetAsyncKeyState(VK_DOWN) == -32767 || GetAsyncKeyState('S') == -32767)
    {
        return false;
    }
    
    return true;
}

void fondo(){
    //ASCII ART
    gotoxy(10,6);
    cout<<"    ___  _                                 _       _      _ _                             _       ";
    gotoxy(10,7);
    cout<<"   / _ \\| |                               | |     | |    | (_)                           | |      ";
    gotoxy(10,8);
    cout<<"  / /_\\ \\ |_ _ __ __ _ _ __   __ _    __ _| |   __| | ___| |_ _ __   ___ _   _  ___ _ __ | |_ ___ ";
    gotoxy(10,9);
    cout<<"  |  _  | __| '__/ _` | '_ \\ / _` |  / _` | |  / _` |/ _ \\ | | '_ \\ / __| | | |/ _ \\ '_ \\| __/ _ \\";
    gotoxy(10,10);
    cout<<"  | | | | |_| | | (_| | |_) | (_| | | (_| | | | (_| |  __/ | | | | | (__| |_| |  __/ | | | ||  __/";
    gotoxy(10,11);
    cout<<"  \\_| |_/\\__|_|  \\__,_| .__/ \\__,_|  \\__,_|_|  \\__,_|\\___|_|_|_| |_|\\___|\\__,_|\\___|_| |_|\\__\\___|";
    gotoxy(10,12);
    cout<<"                      | |                                                                         ";
    gotoxy(10,13);
    cout<<"                      | |                                                                         ";    
    gotoxy(10,14);     
    cout<<"                      |_|                           ";  
}

void fondo1(){
    //horizontal
    for (int i = 5; i < 115; i++)
    {
        gotoxy(i,2);
        printf("%c",205);
        gotoxy(i,27);
        printf("%c",205);
    }
    //vertical
    for (int i = 3; i < 27; i++)
    {
        gotoxy(4,i);
        printf("%c",186);
        gotoxy(115,i);
        printf("%c",186);
    }

    gotoxy(4,2);
    printf("%c",201);

    gotoxy(115,2);
    printf("%c",187);

    gotoxy(4,27);
    printf("%c",200);

    gotoxy(115,27);
    printf("%c",188);
}

void guia(){
    system("cls");
    cout<<"1. Modos de juego"<<endl;
    cout<<"El delincuente tiene como objetivos escapar de los policias y eliminarlos si es posible,"<<endl;
    cout<<"pero debe robar algun objeto antes de que se acabe el tiempo.\n";
    cout<<"Mientras tanto, el policia debe evitar que los ladrones roben los objetos dispersos en el mapa.\n";
    cout<<"2. Tiempo y vida\n";
    cout<<"Si se acaba tu tiempo, perderas una vida, y si se acaban tus vidas, se acaba el juego."<<endl;
    cout<<"Si eres un delincuente y te atrapa el policia, perderas una vida. Mientras que si eres"<<endl;
    cout<<"un policia y un malandro te dispara, perderas una vida."<<endl;
    cout<<"3. Objetos\n";
    cout<<"Los objetos apareceran aleatoriamente por el mapa, recogerlos te permitira recuperar\n tiempo, obtener armas y mejoras.\n";
    cout<<"4. Armas\n";
    cout<<"Hay en total 4, para acceder a ellas debes tocar las teclas numericas 1, 2, 3 y 4.\n Y para dispararlas deberaa presionar ENTER.\n";
    system("pause");
}

void menu(){
    
    gotoxy(47,15);
    cout<<"Jugar\n";
    gotoxy(47,16);
    cout<<"Guia\n";
    gotoxy(47,17);
    cout<<"Salir";
    if (op == 1 || op == 0)
    {
        op = 1;
        gotoxy(53,15);
    }
    else
    {
        gotoxy(52,16);
        op = 2;
    }

    while (true)
    {
        Sleep(50);
        if (GetAsyncKeyState(VK_RETURN) == -32767)
        {
            if(op == 1)
            {
                break;
            }
            if (op == 2)
            {
                op = 3;
                break;
            }
            if (op == 3)
            {
            	op = 4;
                break;
            }
            
        }

        if(GetAsyncKeyState(VK_UP) != 0 && op - 1 > 0 || GetAsyncKeyState('W') != 0 && op - 1 > 0)
        {          
            
            op = op - 1;
            if (op == 1)
            {
                gotoxy(53,15);
            }
            if (op == 2)
            {
                gotoxy(53,16);
            }
            if (op == 3)
            {
                gotoxy(53,17);
            }
        }

        if(GetAsyncKeyState(VK_DOWN) != 0 && op + 1 < 4 || GetAsyncKeyState('S') != 0 && op + 1 < 4)
        {          
            op = op + 1;            
            if (op == 1)
            {
                gotoxy(53,15);
            }
            if (op == 2)
            {
                gotoxy(53,16);
            }
            if (op == 3)
            {
                gotoxy(53,17);
            }
        }
    }

    if (op == 1)
    {
        op = 0;
        gotoxy(47,15);
        cout<<"Jugar \n";
        gotoxy(47,16);
        cout<<"-Delincuente \n";
        gotoxy(47,17);
        cout<<"-Policia ";
        gotoxy(47,18);
        cout<<"Guia";
        gotoxy(47,19);
        cout<<"Salir";
        gotoxy(52,15);
        menu1();
    }
    

}

void menu1(){                                          

    while (true)
    {
        Sleep(50);
        if (GetAsyncKeyState(VK_RETURN) == -32767 || op == 3)
        {
            if (op == 0 || op == 3)
            {
                for (int i = 0; i < 5; i++)
                {
                    gotoxy(47,15+i);
                    for (int j = 0; j < 25; j++)
                    {
                        cout<<" ";
                    }
                    
                }
                menu();
            }
            return;
            
        }
        
        if(GetAsyncKeyState(VK_UP) == -32767 && op - 1 >= 0 || GetAsyncKeyState('W') == -32767 && op - 1 >= 0)
        {          
            for (int i = 0; i < 2; i++)
            {
                gotoxy(47,15+i);
                for (int j = 0; j < 25; j++)
                {
                    cout<<" ";
                }
                
            }
            
            op = op - 1;
            gotoxy(47,15);
            cout<<"Jugar \n";
            gotoxy(47,16);
            cout<<"-Delincuente \n";
            gotoxy(47,17);
            cout<<"-Policia ";

            if (op == 0)
            {
                gotoxy(52,15);
            }
            
            if (op == 1)
            {
                gotoxy(59,16);
            }
            if (op == 2)
            {
                gotoxy(55,17);
            }
        }

        if(GetAsyncKeyState(VK_DOWN) == -32767 && op + 1 < 4 || GetAsyncKeyState('S') == -32767 && op + 1 < 4)
        {          
            for (int i = 0; i < 3; i++)
            {
                gotoxy(47,15+i);
                for (int j = 0; j < 25; j++)
                {
                    cout<<" ";
                }
                
            }
            op = op + 1;
            gotoxy(47,15);
            cout<<"Jugar \n";
            gotoxy(47,16);
            cout<<"-Delincuente \n";
            gotoxy(47,17);
            cout<<"-Policia ";
            

            if (op == 0)
            {
                gotoxy(52,15);
            }
            
            if (op == 1)
            {
                gotoxy(47,16);
                cout<<"-Delincuente \n";
                gotoxy(47,17);
                cout<<"-Policia \n";
                gotoxy(59,16);
            }
            if (op == 2)
            {
                gotoxy(47,16);
                cout<<"-Delincuente \n";
                gotoxy(47,17);
                cout<<"-Policia \n";
                gotoxy(55,17);
            }
            
        }
		
    }
    
    system("cls");

    if(op == 2)
    {
        game_ladron();
    }
    else
    {
        
    }
    
}

void spawn_criminal_mode(){ 

    jugador.coord.x = 54;
    jugador.coord.y = 12;
    gotoxy(jugador.coord.x,jugador.coord.y);
    printf("%c",254);

    respawn_policia();
}

void spawn_police_mode(){

    policia.coord.x = 54;
    policia.coord.y = 12;
    gotoxy(policia.coord.x,policia.coord.y);
    printf("%c",254);

    for(int i = 0; i < 4; i++)
    {
        if(ladrones[i].coord.x != -1)
        {
            respawn_criminal(i);
        }
    }

}

int numero_majico(int limI,int limS){
    srand(time(NULL));
    return limI + rand()% (limS + 1 - limI);
}

void respawn_policia(){
    gotoxy(policia.coord.x,policia.coord.y);
    cout<<" ";

    int POS[4] = {5,114,3,26};
    do
    {
        policia.coord.x = POS[numero_majico(1,2)-1];
        policia.coord.y = POS[4-numero_majico(1,2)];
    } while(distancia_entre_dos_puntos(jugador.coord.x, jugador.coord.y, policia.coord.x, policia.coord.y) <= 20);

    if (op == 1)
    {
        gotoxy(policia.coord.x,policia.coord.y);
        cout<<"P";
    }
    else
    {
        vidas -= 1;
        gotoxy(policia.coord.x,policia.coord.y);
        printf("%c",254);
    }
    
}

void respawn_criminal(int&i){
    for (int I = 0;true; I = 0)
            {
                for (int i = 0; i < 4; i++)
                {
                    if(ladrones[i].coord.x != -1)
                    {
                        I ++;
                    }
                }

                if (I == 1)
                {
                    break;
                }
                
                for(int i = 0; i < 4; i++)
                {
                    if(ladrones[i].coord.x != -1
                       && 
                       ladrones[i].coord.x > 4 && ladrones[i].coord.y < 115
                       && 
                       ladrones[i].coord.y > 2 && ladrones[i].coord.y < 27)
                    {
                        gotoxy(ladrones[i].coord.x,ladrones[i].coord.y);
                        cout<<" ";
                        ladrones[i].coord.x = -1;
                        break;
                    }
                    
                }
                break;
            }

    gotoxy(ladrones[i].coord.x,ladrones[i].coord.y);
    cout<<" ";

    int POS[4] = {5,114,3,26};

    ladrones[i].coord.x = POS[numero_majico(1,2)-1];
    ladrones[i].coord.y = POS[4-numero_majico(1,2)];
    gotoxy(ladrones[i].coord.x,ladrones[i].coord.y);
    cout<<"L";

}

void movimiento_Ladrones(int NUM){

    if(ladrones[NUM].coord.x == policia.coord.x && ladrones[NUM].coord.y == policia.coord.y)
    {
        aumentar_tiempo();
        respawn_criminal(NUM);
    }

    int distancia_jugador_policia;
    int distancia_jugador_policia_1;
    
    coordenadas aux;

    distancia_jugador_policia = distancia_entre_dos_puntos(policia.coord.x, policia.coord.y, ladrones[NUM].coord.x, ladrones[NUM].coord.y);

    char *array;
    array = new char[8];
    
    for (int c = 0; true ; c = c)
    {
        for (char i = '1'; i < '9'; i++)
        {
            array[c] = i;
            c++;
        }
        break;
    }

    int size = 0;

    char *aux_array;
    char num_aux;

    do
    {

        aux.x = ladrones[NUM].coord.x;
        aux.y = ladrones[NUM].coord.y;

        num_aux = *(array+numero_majico(0,7-size));

        switch (num_aux)
        {
        case '1':
            aux.x -= 1;
            aux.y -= 1;
            break;
        case '2':
            //x
            aux.y -= 1;
            break;
        case '3':
            aux.x += 1;
            aux.y -= 1;
            break;
        case '4':
            aux.x += 1;
            //y
            break;
        case '5':
            aux.x += 1;
            aux.y += 1;
            break;
        case '6':
            //x
            aux.y += 1;
            break;
        case '7':
            aux.x -= 1;
            aux.y += 1;
            break;
        case '8':
            aux.x -= 1;
            //y
            break;
        }
        
        distancia_jugador_policia_1 = distancia_entre_dos_puntos(aux.x,aux.y,policia.coord.x,policia.coord.y);

        if (object.value == 0)
        {

            if (aux.x < 5 || aux.y < 3 || aux.x > 114 || aux.y > 26 || distancia_jugador_policia_1 <= distancia_jugador_policia )
            {
                size++;
                if (size == 8)
                {
                    return;
                }
                
                aux_array = new char [8-size];
                for (int i = 0, c = 0; c < 8-size; i++)
                {
                    if(array[i] != num_aux)
                    {
                        aux_array[c] = array[i];
                        c++;
                    }
                }
                
                delete[] array;
                array = new char[8-size];

                for (int i = 0; i < 8-size; i++)
                {
                    array[i] = aux_array[i];
                }
                
            }
            else
            {
                break;
            }
        }
        else
        {
            if (aux.x >= 5 && aux.y >= 3 && aux.x <= 114 && aux.y <= 26)
            {
                if (distancia_jugador_policia_1 > 0)
                {
                    if (distancia_entre_dos_puntos(aux.x,aux.y,object.coord.x,object.coord.y) < distancia_entre_dos_puntos(ladrones[NUM].coord.x,ladrones[NUM].coord.y,object.coord.x,object.coord.y))
                    {
                        break;
                    }
                }
                else
                {
                    if (distancia_jugador_policia_1 > distancia_jugador_policia)
                    {
                        break;
                    }
                }
            }
            if(true)
            {
                size++;
                if (size == 8)
                {
                    return;
                }
                
                aux_array = new char [8-size];
                for (int i = 0, c = 0; c < 8-size; i++)
                {
                    if(array[i] != num_aux)
                    {
                        aux_array[c] = array[i];
                        c++;
                    }
                }
                
                delete[] array;
                array = new char[8-size];

                for (int i = 0; i < 8-size; i++)
                {
                    array[i] = aux_array[i];
                }
            }
        }
        

    } while (true);  

    
    gotoxy(ladrones[NUM].coord.x, ladrones[NUM].coord.y);
    cout<<" ";
    

    if (ladrones[NUM].coord.x > aux.x)
    {
        ladrones[NUM].direccion = 0;
    }
    if (ladrones[NUM].coord.x < aux.x)
    {
        ladrones[NUM].direccion = 1;
    }

    ladrones[NUM].coord.x = aux.x;
    ladrones[NUM].coord.y = aux.y;
    
    ///*
    gotoxy(ladrones[NUM].coord.x, ladrones[NUM].coord.y);
    cout<<"L";
    //*/

    ataque_ladrones(NUM);

}
 
void ataque_ladrones(int NUM){
    jugador.coord.x = ladrones[NUM].coord.x;
    jugador.coord.y = ladrones[NUM].coord.y;
    double m = 0, b = 0;
    if( NUM+1 != 0){
        //Duales
        if(NUM+1 == 1)
        {
            if(jugador.coord.x-1 > 4)
            {
                ladrones[NUM].balas[1].x = jugador.coord.x-1;
                ladrones[NUM].balas[1].y = jugador.coord.y;
                if (ladron.coord.x != ladrones[NUM].balas[1].x && ladron.coord.y != ladrones[NUM].balas[1].y && family_L == true || family_L == false)
                {
                    gotoxy(ladrones[NUM].balas[1].x,ladrones[NUM].balas[1].y);
                    printf("%c",196);
                    ladrones[NUM].balas[1].exist = 1;
                }

            }
            if (jugador.coord.x+1 < 115)
            {
                ladrones[NUM].balas[0].x = jugador.coord.x+1;
                ladrones[NUM].balas[0].y = jugador.coord.y;
                if (ladron.coord.x != ladrones[NUM].balas[0].x && ladron.coord.y != ladrones[NUM].balas[0].y && family_L == true || family_L == false)
                {
                    gotoxy(ladrones[NUM].balas[0].x,ladrones[NUM].balas[0].y);
                    printf("%c",196);
                    ladrones[NUM].balas[0].exist = 1;
                }

            }
            ladrones[NUM].balas[0].exist = 1;
            //Ecuacion de la recta
            m = (ladrones[NUM].balas[0].y-jugador.coord.y)/(ladrones[NUM].balas[0].x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }
        }
        //Ametralladora
        if (NUM+1 == 2)
        {

            if(ladrones[NUM].direccion == 0 && jugador.coord.x-1 > 4)
            {
                ladrones[NUM].balas[0].x = jugador.coord.x-1;
                ladrones[NUM].balas[0].y = jugador.coord.y;
                if (ladron.coord.x != ladrones[NUM].balas[0].x && ladron.coord.y != ladrones[NUM].balas[0].y && family_L == true || family_L == false)
                {
                    gotoxy(ladrones[NUM].balas[0].x,ladrones[NUM].balas[0].y);
                    printf("%c",196);
                    ladrones[NUM].balas[0].exist = 1;
                }

            }
            if (ladrones[NUM].direccion == 1 && jugador.coord.x+1 < 115)
            {
                ladrones[NUM].balas[0].x = jugador.coord.x+1;
                ladrones[NUM].balas[0].y = jugador.coord.y;
                if (ladron.coord.x != ladrones[NUM].balas[0].x && ladron.coord.y != ladrones[NUM].balas[0].y && family_L == true || family_L == false)
                {
                    gotoxy(ladrones[NUM].balas[0].x,ladrones[NUM].balas[0].y);
                    printf("%c",196);
                    ladrones[NUM].balas[0].exist = 1;
                }
            }

            if (jugador.coord.y - 1 > 2)
            {
                ladrones[NUM].balas[1].x = jugador.coord.x;
                ladrones[NUM].balas[1].y = jugador.coord.y-1;
                if (ladron.coord.x != ladrones[NUM].balas[1].x && ladron.coord.y != ladrones[NUM].balas[1].y && family_L == true || family_L == false)
                {
                    gotoxy(ladrones[NUM].balas[1].x,ladrones[NUM].balas[1].y);
                    printf("%c",124);
                    ladrones[NUM].balas[1].exist = 1;
                }
            }
            

            if (jugador.coord.y + 1 < 27)
            {
                ladrones[NUM].balas[2].x = jugador.coord.x;
                ladrones[NUM].balas[2].y = jugador.coord.y+1;
                if (ladron.coord.x != ladrones[NUM].balas[2].x && ladron.coord.y != ladrones[NUM].balas[2].y && family_L == true || family_L == false)
                {
                    gotoxy(ladrones[NUM].balas[2].x,ladrones[NUM].balas[2].y);
                    printf("%c",124);
                    ladrones[NUM].balas[2].exist = 1;
                }
            }

            if(jugador.coord.x == policia.coord.x && distancia_entre_dos_puntos(jugador.coord.x,jugador.coord.y,policia.coord.x,policia.coord.y) != 0)
            {
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            if(policia.coord.y == jugador.coord.y)
            {
                if(ladrones[NUM].direccion == 0 && policia.coord.x < jugador.coord.x)
                {
                    respawn_policia();
                    aumentar_tiempo();
                    return;
                }
                if (ladrones[NUM].direccion == 1 && policia.coord.x > jugador.coord.x)
                {
                    respawn_policia();
                    aumentar_tiempo();
                    return;
                }
            }
        }
        //Uzi
        if (NUM+1 == 3)
        {
            //Posicion de la bala
            ladrones[NUM].balas[0].x = jugador.coord.x-1;
            ladrones[NUM].balas[0].y = jugador.coord.y-1;

            ladrones[NUM].balas[1].x = jugador.coord.x+1;
            ladrones[NUM].balas[1].y = jugador.coord.y-1;

            ladrones[NUM].balas[2].x = jugador.coord.x-1;
            ladrones[NUM].balas[2].y = jugador.coord.y+1;

            ladrones[NUM].balas[3].x = jugador.coord.x+1;
            ladrones[NUM].balas[3].y = jugador.coord.y+1;

            //Imprimir la bala

            if (ladrones[NUM].balas[0].x > 4 && ladrones[NUM].balas[0].x < 115 && ladrones[NUM].balas[0].y > 2 && ladrones[NUM].balas[0].y < 27)
            {
                gotoxy(ladrones[NUM].balas[0].x,ladrones[NUM].balas[0].y);
                cout<<"\\";
                ladrones[NUM].balas[0].exist = 1;
            }
            if (ladrones[NUM].balas[1].x > 4 && ladrones[NUM].balas[1].x < 115 && ladrones[NUM].balas[1].y > 2 && ladrones[NUM].balas[1].y < 27)
            {
                gotoxy(ladrones[NUM].balas[1].x,ladrones[NUM].balas[1].y);
                cout<<"/";
                ladrones[NUM].balas[1].exist = 1;
            }
            if (ladrones[NUM].balas[2].x > 4 && ladrones[NUM].balas[2].x < 115 && ladrones[NUM].balas[2].y > 2 && ladrones[NUM].balas[2].y < 27)
            {
                gotoxy(ladrones[NUM].balas[2].x,ladrones[NUM].balas[2].y);
                cout<<"/";
                ladrones[NUM].balas[2].exist = 1;
            }
            if (ladrones[NUM].balas[3].x > 4 && ladrones[NUM].balas[3].x < 115 && ladrones[NUM].balas[3].y > 2 && ladrones[NUM].balas[3].y < 27)
            {
                gotoxy(ladrones[NUM].balas[3].x,ladrones[NUM].balas[3].y);
                cout<<"\\";
                ladrones[NUM].balas[3].exist = 1;
            }
            
            //Eliminar al polcia

            //Ecuacion n1
            m = (ladrones[NUM].balas[0].y-jugador.coord.y)/(ladrones[NUM].balas[0].x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            m = (ladrones[NUM].balas[1].y-jugador.coord.y)/(ladrones[NUM].balas[1].x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

        }

        //Escopeta
        if (NUM+1 == 4)
        {
            if (ladrones[NUM].direccion == 0)
            {

                ladrones[NUM].balas[0].x = jugador.coord.x - 1;
                ladrones[NUM].balas[0].y = jugador.coord.y - 1;

                ladrones[NUM].balas[1].x = jugador.coord.x - 1;
                ladrones[NUM].balas[1].y = jugador.coord.y;

                ladrones[NUM].balas[2].x = jugador.coord.x - 2;
                ladrones[NUM].balas[2].y = jugador.coord.y;

                ladrones[NUM].balas[3].x = jugador.coord.x - 1;
                ladrones[NUM].balas[3].y = jugador.coord.y + 1;

                if (ladrones[NUM].balas[0].x > 4 && ladrones[NUM].balas[0].x < 115 && ladrones[NUM].balas[0].y > 2 && ladrones[NUM].balas[0].y < 27)
                {
                    gotoxy(ladrones[NUM].balas[0].x,ladrones[NUM].balas[0].y);
                    cout<<"\\";
                    ladrones[NUM].balas[0].exist = 1;
                }
                if (ladrones[NUM].balas[1].x > 4 && ladrones[NUM].balas[1].x < 115 && ladrones[NUM].balas[1].y > 2 && ladrones[NUM].balas[1].y < 27)
                {
                    gotoxy(ladrones[NUM].balas[1].x,ladrones[NUM].balas[1].y);
                    printf("%c",175);
                    ladrones[NUM].balas[1].exist = 1;
                }
                if (ladrones[NUM].balas[2].x > 4 && ladrones[NUM].balas[2].x < 115 && ladrones[NUM].balas[2].y > 2 && ladrones[NUM].balas[2].y < 27)
                {
                    gotoxy(ladrones[NUM].balas[2].x,ladrones[NUM].balas[2].y);
                    printf("%c",176);
                    ladrones[NUM].balas[2].exist = 1;
                }
                if (ladrones[NUM].balas[3].x > 4 && ladrones[NUM].balas[3].x < 115 && ladrones[NUM].balas[3].y > 2 && ladrones[NUM].balas[3].y < 27)
                {
                    gotoxy(ladrones[NUM].balas[3].x,ladrones[NUM].balas[3].y);
                    cout<<"/";
                    ladrones[NUM].balas[3].exist = 1;
                }
                
            }
            if (ladrones[NUM].direccion == 1)
            {

                ladrones[NUM].balas[0].x = jugador.coord.x + 1;
                ladrones[NUM].balas[0].y = jugador.coord.y - 1;

                ladrones[NUM].balas[1].x = jugador.coord.x + 1;
                ladrones[NUM].balas[1].y = jugador.coord.y;

                ladrones[NUM].balas[2].x = jugador.coord.x + 2;
                ladrones[NUM].balas[2].y = jugador.coord.y;

                ladrones[NUM].balas[3].x = jugador.coord.x + 1;
                ladrones[NUM].balas[3].y = jugador.coord.y +1;

                if (ladrones[NUM].balas[0].x > 4 && ladrones[NUM].balas[0].x < 115 && ladrones[NUM].balas[0].y > 2 && ladrones[NUM].balas[0].y < 27)
                {
                    gotoxy(ladrones[NUM].balas[0].x,ladrones[NUM].balas[0].y);
                    cout<<"/";
                    ladrones[NUM].balas[0].exist = 1;
                }
                if (ladrones[NUM].balas[1].x > 4 && ladrones[NUM].balas[1].x < 115 && ladrones[NUM].balas[1].y > 2 && ladrones[NUM].balas[1].y < 27)
                {
                    gotoxy(ladrones[NUM].balas[1].x,ladrones[NUM].balas[1].y);
                    printf("%c",174);
                    ladrones[NUM].balas[1].exist = 1;
                }
                if (ladrones[NUM].balas[2].x > 4 && ladrones[NUM].balas[2].x < 115 && ladrones[NUM].balas[2].y > 2 && ladrones[NUM].balas[2].y < 27)
                {
                    gotoxy(ladrones[NUM].balas[2].x,ladrones[NUM].balas[2].y);
                    printf("%c",176);
                    ladrones[NUM].balas[2].exist = 1;
                }
                if (ladrones[NUM].balas[3].x > 4 && ladrones[NUM].balas[3].x < 115 && ladrones[NUM].balas[3].y > 2 && ladrones[NUM].balas[3].y < 27)
                {
                    gotoxy(ladrones[NUM].balas[3].x,ladrones[NUM].balas[3].y);
                    cout<<"\\";
                    ladrones[NUM].balas[3].exist = 1;
                }
                
            }

            if(ladrones[NUM].direccion == 1 && policia.coord.x < jugador.coord.x)
            {
                return;
            }
            if (ladrones[NUM].direccion == 0 && policia.coord.x > jugador.coord.x)
            {
                return;
            }
            
            m = (ladrones[NUM].balas[0].y-jugador.coord.y)/(ladrones[NUM].balas[0].x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            m = (ladrones[NUM].balas[1].y-jugador.coord.y)/(ladrones[NUM].balas[1].x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            m = (ladrones[NUM].balas[3].y-jugador.coord.y)/(ladrones[NUM].balas[3].x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            m = (ladrones[NUM].balas[1].y-(jugador.coord.y+1))/(ladrones[NUM].balas[1].x-jugador.coord.x);
            b = ((jugador.coord.y+1)-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            m = (ladrones[NUM].balas[1].y-(jugador.coord.y-1))/(ladrones[NUM].balas[1].x-jugador.coord.x);
            b = ((jugador.coord.y-1)-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            
            
        
        }
        
    }
}

void borrar_balas(int NUM){
    for(int i = 0; i < 4; i ++)
    {
        if(ladrones[NUM].balas[i].exist == 1 
           && 
           ladrones[NUM].balas[i].x > 4 && ladrones[NUM].balas[i].x < 115
           &&
           ladrones[NUM].balas[i].y > 2 && ladrones[NUM].balas[i].y < 27)
        {
            gotoxy(ladrones[NUM].balas[i].x,ladrones[NUM].balas[i].y);
            cout<<" ";
            ladrones[NUM].balas[i].exist = 0;
        }
    }
}

void movimiento_ladron(){
    
    if(distancia_entre_dos_puntos(policia.coord.x, policia.coord.y, ladron.coord.x, ladron.coord.y) == 0)
    {
        gotoxy(ladron.coord.x, ladron.coord.y);
        cout<<" ";
        family_L = false;
        anadir_elemento(5);
        return;
    }

    int distancia_jugador_policia;
    int distancia_jugador_policia_1;
    
    coordenadas aux;

    distancia_jugador_policia = distancia_entre_dos_puntos(policia.coord.x, policia.coord.y, ladron.coord.x, ladron.coord.y);

    char *array;
    array = new char[8];
    
    for (int c = 0; true ; c = c)
    {
        for (char i = '1'; i < '9'; i++)
        {
            array[c] = i;
            c++;
        }
        break;
    }

    int size = 0;

    char *aux_array;
    char num_aux;

    do
    {

        aux.x = ladron.coord.x;
        aux.y = ladron.coord.y;

        num_aux = *(array+numero_majico(0,7-size));

        switch (num_aux)
        {
        case '1':
            aux.x -= 1;
            aux.y -= 1;
            break;
        case '2':
            //x
            aux.y -= 1;
            break;
        case '3':
            aux.x += 1;
            aux.y -= 1;
            break;
        case '4':
            aux.x += 1;
            //y
            break;
        case '5':
            aux.x += 1;
            aux.y += 1;
            break;
        case '6':
            //x
            aux.y += 1;
            break;
        case '7':
            aux.x -= 1;
            aux.y += 1;
            break;
        case '8':
            aux.x -= 1;
            //y
            break;
        }
        
        distancia_jugador_policia_1 = distancia_entre_dos_puntos(aux.x,aux.y,policia.coord.x,policia.coord.y);

        if (object.value == 0)
        {

            if (aux.x < 5 || aux.y < 3 || aux.x > 114 || aux.y > 26 || distancia_jugador_policia_1 <= distancia_jugador_policia )
            {
                size++;
                if (size == 8)
                {
                    return;
                }
                
                aux_array = new char [8-size];
                for (int i = 0, c = 0; c < 8-size; i++)
                {
                    if(array[i] != num_aux)
                    {
                        aux_array[c] = array[i];
                        c++;
                    }
                }
                
                delete[] array;
                array = new char[8-size];

                for (int i = 0; i < 8-size; i++)
                {
                    array[i] = aux_array[i];
                }
                
            }
            else
            {
                break;
            }
        }
        else
        {
            if (aux.x >= 5 && aux.y >= 3 && aux.x <= 114 && aux.y <= 26)
            {
                if (distancia_jugador_policia_1 >= 20)
                {
                    if (distancia_entre_dos_puntos(aux.x,aux.y,object.coord.x,object.coord.y) < distancia_entre_dos_puntos(ladron.coord.x,ladron.coord.y,object.coord.x,object.coord.y))
                    {
                        break;
                    }
                }
                else
                {
                    if (distancia_jugador_policia_1 > distancia_jugador_policia)
                    {
                        break;
                    }
                }
            }
            if(true)
            {
                size++;
                if (size == 8)
                {
                    return;
                }
                
                aux_array = new char [8-size];
                for (int i = 0, c = 0; c < 8-size; i++)
                {
                    if(array[i] != num_aux)
                    {
                        aux_array[c] = array[i];
                        c++;
                    }
                }
                
                delete[] array;
                array = new char[8-size];

                for (int i = 0; i < 8-size; i++)
                {
                    array[i] = aux_array[i];
                }
            }
        }
        

    } while (true);  

    
    gotoxy(ladron.coord.x, ladron.coord.y);
    cout<<" ";
    
    if(ladron.coord.x == jugador.coord.x && ladron.coord.y == jugador.coord.y)
    {
        if (aux.x != jugador.coord.x || aux.y != jugador.coord.y)
        {
            gotoxy(ladron.coord.x, ladron.coord.y);
            printf("%c",254);
        }
    }

    ladron.coord.x = aux.x;
    ladron.coord.y = aux.y;
    
    ///*
    gotoxy(ladron.coord.x, ladron.coord.y);
    cout<<"L";
    //*/

}

void ataque_ladron(){
    double m = 0, b = 0;
    if(arma[arma_num-1] != 0 && arma_num != 0){
        arma[arma_num-1] -= 1;
        //Duales
        if(arma_num == 1)
        {
            if(jugador.coord.x-1 > 4)
            {
                bala1.x = jugador.coord.x-1;
                bala1.y = jugador.coord.y;
                if (ladron.coord.x != bala1.x && ladron.coord.y != bala1.y && family_L == true || family_L == false)
                {
                    gotoxy(bala1.x,bala1.y);
                    printf("%c",196);
                    borrar[1] = 1;
                }

            }
            if (jugador.coord.x+1 < 115)
            {
                bala.x = jugador.coord.x+1;
                bala.y = jugador.coord.y;
                if (ladron.coord.x != bala.x && ladron.coord.y != bala.y && family_L == true || family_L == false)
                {
                    gotoxy(bala.x,bala.y);
                    printf("%c",196);
                    borrar[0] = 1;
                }

            }
            borrar[0] = 1;
            //Ecuacion de la recta
            m = (bala.y-jugador.coord.y)/(bala.x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }
        }
        //Ametralladora
        if (arma_num == 2)
        {

            if(direc == 0 && jugador.coord.x-1 > 4)
            {
                bala.x = jugador.coord.x-1;
                bala.y = jugador.coord.y;
                if (ladron.coord.x != bala.x && ladron.coord.y != bala.y && family_L == true || family_L == false)
                {
                    gotoxy(bala.x,bala.y);
                    printf("%c",196);
                    borrar[0] = 1;
                }

            }
            if (direc == 1 && jugador.coord.x+1 < 115)
            {
                bala.x = jugador.coord.x+1;
                bala.y = jugador.coord.y;
                if (ladron.coord.x != bala.x && ladron.coord.y != bala.y && family_L == true || family_L == false)
                {
                    gotoxy(bala.x,bala.y);
                    printf("%c",196);
                    borrar[0] = 1;
                }
            }

            if (jugador.coord.y - 1 > 2)
            {
                bala1.x = jugador.coord.x;
                bala1.y = jugador.coord.y-1;
                if (ladron.coord.x != bala1.x && ladron.coord.y != bala1.y && family_L == true || family_L == false)
                {
                    gotoxy(bala1.x,bala1.y);
                    printf("%c",124);
                    borrar[1] = 1;
                }
            }
            

            if (jugador.coord.y + 1 < 27)
            {
                bala2.x = jugador.coord.x;
                bala2.y = jugador.coord.y+1;
                if (ladron.coord.x != bala2.x && ladron.coord.y != bala2.y && family_L == true || family_L == false)
                {
                    gotoxy(bala2.x,bala2.y);
                    printf("%c",124);
                    borrar[2] = 1;
                }
            }

            if(jugador.coord.x == policia.coord.x && distancia_entre_dos_puntos(jugador.coord.x,jugador.coord.y,policia.coord.x,policia.coord.y) != 0)
            {
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            if(policia.coord.y == jugador.coord.y)
            {
                if(direc == 0 && policia.coord.x < jugador.coord.x)
                {
                    respawn_policia();
                    aumentar_tiempo();
                    return;
                }
                if (direc == 1 && policia.coord.x > jugador.coord.x)
                {
                    respawn_policia();
                    aumentar_tiempo();
                    return;
                }
            }
        }
        //Uzi
        if (arma_num == 3)
        {
            //Posicion de la bala
            bala.x = jugador.coord.x-1;
            bala.y = jugador.coord.y-1;

            bala1.x = jugador.coord.x+1;
            bala1.y = jugador.coord.y-1;

            bala2.x = jugador.coord.x-1;
            bala2.y = jugador.coord.y+1;

            bala3.x = jugador.coord.x+1;
            bala3.y = jugador.coord.y+1;

            //Imprimir la bala

            if (bala.x > 4 && bala.x < 115 && bala.y > 2 && bala.y < 27)
            {
                gotoxy(bala.x,bala.y);
                cout<<"\\";
                borrar[0] = 1;
            }
            if (bala1.x > 4 && bala1.x < 115 && bala1.y > 2 && bala1.y < 27)
            {
                gotoxy(bala1.x,bala1.y);
                cout<<"/";
                borrar[1] = 1;
            }
            if (bala2.x > 4 && bala2.x < 115 && bala2.y > 2 && bala2.y < 27)
            {
                gotoxy(bala2.x,bala2.y);
                cout<<"/";
                borrar[2] = 1;
            }
            if (bala3.x > 4 && bala3.x < 115 && bala3.y > 2 && bala3.y < 27)
            {
                gotoxy(bala3.x,bala3.y);
                cout<<"\\";
                borrar[3] = 1;
            }
            
            //Eliminar al polcia

            //Ecuacion n1
            m = (bala.y-jugador.coord.y)/(bala.x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            m = (bala1.y-jugador.coord.y)/(bala1.x-jugador.coord.x);
            b = (jugador.coord.y-m*jugador.coord.x);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

        }

        //Escopeta
        if (arma_num == 4)
        {
            if (direc == 0)
            {

                bala.x = jugador.coord.x - 1;
                bala.y = jugador.coord.y - 1;

                bala1.x = jugador.coord.x - 1;
                bala1.y = jugador.coord.y;

                bala2.x = jugador.coord.x - 2;
                bala2.y = jugador.coord.y;

                bala3.x = jugador.coord.x - 1;
                bala3.y = jugador.coord.y + 1;

                if (bala.x > 4 && bala.x < 115 && bala.y > 2 && bala.y < 27)
                {
                    gotoxy(bala.x,bala.y);
                    cout<<"\\";
                    borrar[0] = 1;
                }
                if (bala1.x > 4 && bala1.x < 115 && bala1.y > 2 && bala1.y < 27)
                {
                    gotoxy(bala1.x,bala1.y);
                    printf("%c",175);
                    borrar[1] = 1;
                }
                if (bala2.x > 4 && bala2.x < 115 && bala2.y > 2 && bala2.y < 27)
                {
                    gotoxy(bala2.x,bala2.y);
                    printf("%c",176);
                    borrar[2] = 1;
                }
                if (bala3.x > 4 && bala3.x < 115 && bala3.y > 2 && bala3.y < 27)
                {
                    gotoxy(bala3.x,bala3.y);
                    cout<<"/";
                    borrar[3] = 1;
                }
                
            }
            if (direc == 1)
            {

                bala.x = jugador.coord.x + 1;
                bala.y = jugador.coord.y - 1;

                bala1.x = jugador.coord.x + 1;
                bala1.y = jugador.coord.y;

                bala2.x = jugador.coord.x + 2;
                bala2.y = jugador.coord.y;

                bala3.x = jugador.coord.x + 1;
                bala3.y = jugador.coord.y +1;

                if (bala.x > 4 && bala.x < 115 && bala.y > 2 && bala.y < 27)
                {
                    gotoxy(bala.x,bala.y);
                    cout<<"/";
                    borrar[0] = 1;
                }
                if (bala1.x > 4 && bala1.x < 115 && bala1.y > 2 && bala1.y < 27)
                {
                    gotoxy(bala1.x,bala1.y);
                    printf("%c",174);
                    borrar[1] = 1;
                }
                if (bala2.x > 4 && bala2.x < 115 && bala2.y > 2 && bala2.y < 27)
                {
                    gotoxy(bala2.x,bala2.y);
                    printf("%c",176);
                    borrar[2] = 1;
                }
                if (bala3.x > 4 && bala3.x < 115 && bala3.y > 2 && bala3.y < 27)
                {
                    gotoxy(bala3.x,bala3.y);
                    cout<<"\\";
                    borrar[3] = 1;
                }
                
            }

            if(direc == 1 && policia.coord.x < jugador.coord.x)
            {
                return;
            }
            if (direc == 0 && policia.coord.x > jugador.coord.x)
            {
                return;
            }
            
            m = 0;
            b = (jugador.coord.y-1);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            m = 0;
            b = (jugador.coord.y);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }

            m = 0;
            b = (jugador.coord.y+1);

            if(policia.coord.y == m*policia.coord.x+b){
                respawn_policia();
                aumentar_tiempo();
                return;
            }            
        
        }
        
    }
}

void borrar_bala(){
    if (borrar[0] == 1)
    {
    borrar[0] = 0;
    gotoxy(bala.x,bala.y);
    cout<<" ";
    }

    if (borrar[1] == 1)
    {
        borrar[1] = 0;
        gotoxy(bala1.x,bala1.y);
        cout<<" ";
    }

    if (borrar[2] == 1)
    {
        borrar[2] = 0;
        gotoxy(bala2.x,bala2.y);
        cout<<" ";
    }
    if (borrar[3] == 1)
    {
        borrar[3] = 0;
        gotoxy(bala3.x,bala3.y);
        cout<<" ";
    }
    
}

void movimiento_policia(){

    if(policia.coord.x == jugador.coord.x && policia.coord.y == jugador.coord.y)
    {
        return;
    }

    int distancia_jugador_policia;
    int distancia_jugador_policia_1;
    
    coordenadas aux;

    distancia_jugador_policia = distancia_entre_dos_puntos(jugador.coord.x, jugador.coord.y, policia.coord.x, policia.coord.y);

    char *array;
    array = new char[8];
    
    for (int c = 0; true ; c = c)
    {
        for (char i = '1'; i < '9'; i++)
        {
            array[c] = i;
            c++;
        }
        break;
    }

    int size = 0;

    char *aux_array;
    char num_aux;

    do
    {

        aux.x = policia.coord.x;
        aux.y = policia.coord.y;

        num_aux = *(array+numero_majico(0,7-size));

        switch (num_aux)
        {
        case '1':
            aux.x -= 1;
            aux.y -= 1;
            break;
        case '2':
            //x
            aux.y -= 1;
            break;
        case '3':
            aux.x += 1;
            aux.y -= 1;
            break;
        case '4':
            aux.x += 1;
            //y
            break;
        case '5':
            aux.x += 1;
            aux.y += 1;
            break;
        case '6':
            //x
            aux.y += 1;
            break;
        case '7':
            aux.x -= 1;
            aux.y += 1;
            break;
        case '8':
            aux.x -= 1;
            //y
            break;
        }
        
        distancia_jugador_policia_1 = distancia_entre_dos_puntos(aux.x,aux.y,jugador.coord.x,jugador.coord.y);

        if (family_L == false)
        {
        if (aux.x < 5 || aux.y < 3 || aux.x > 114 || aux.y > 26 || distancia_jugador_policia_1 >= distancia_jugador_policia)
            {
                size++;
                aux_array = new char [8-size];
                for (int i = 0, c = 0; c < 8-size; i++)
                {
                    if(array[i] != num_aux)
                    {
                        aux_array[c] = array[i];
                        c++;
                    }
                }
                
                delete[] array;
                array = new char[8-size];

                for (int i = 0; i < 8-size; i++)
                {
                    array[i] = aux_array[i];
                }
                
            }
            else
            {
                break;
            }
        }
        else
        {
            if (distancia_jugador_policia < distancia_entre_dos_puntos(ladron.coord.x,ladron.coord.y,policia.coord.x,policia.coord.y))
            {
                if (aux.x < 5 || aux.y < 3 || aux.x > 114 || aux.y > 26 || distancia_jugador_policia_1 >= distancia_jugador_policia)
                {
                    size++;
                    aux_array = new char [8-size];
                    for (int i = 0, c = 0; c < 8-size; i++)
                    {
                        if(array[i] != num_aux)
                        {
                            aux_array[c] = array[i];
                            c++;
                        }
                    }
                    
                    delete[] array;
                    array = new char[8-size];

                    for (int i = 0; i < 8-size; i++)
                    {
                        array[i] = aux_array[i];
                    }
                    
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (aux.x < 5 || aux.y < 3 || aux.x > 114 || aux.y > 26 || distancia_entre_dos_puntos(ladron.coord.x,ladron.coord.y,aux.x,aux.y) >= distancia_entre_dos_puntos(ladron.coord.x,ladron.coord.y,policia.coord.x,policia.coord.y))
                {
                    size++;
                    aux_array = new char [8-size];
                    for (int i = 0, c = 0; c < 8-size; i++)
                    {
                        if(array[i] != num_aux)
                        {
                            aux_array[c] = array[i];
                            c++;
                        }
                    }
                    
                    delete[] array;
                    array = new char[8-size];

                    for (int i = 0; i < 8-size; i++)
                    {
                        array[i] = aux_array[i];
                    }
                    
                }
                else
                {
                    break;
                }
            }
            
        }
        

    } while (true);  

    
    gotoxy(policia.coord.x, policia.coord.y);
    cout<<" ";

    policia.coord.x = aux.x;
    policia.coord.y = aux.y;
    
    gotoxy(policia.coord.x, policia.coord.y);
    cout<<"P";

    
}

void ataque_policia(int NUM){
    int AUXT = Tiempo;
    double m = 0, b = 0;
    if(arma[arma_num-1] != 0 && arma_num != 0){
        arma[arma_num-1] -= 1;
        //Duales
        if(arma_num == 1)
        {
            if(policia.coord.x-1 > 4)
            {
                bala1.x = policia.coord.x-1;
                bala1.y = policia.coord.y;
                gotoxy(bala1.x,bala1.y);
                printf("%c",196);
                borrar[1] = 1;

            }
            if (policia.coord.x+1 < 115)
            {
                bala.x = policia.coord.x+1;
                bala.y = policia.coord.y;
                gotoxy(bala.x,bala.y);
                printf("%c",196);
                borrar[0] = 1;

            }
            borrar[0] = 1;
            //Ecuacion de la recta
            m = (bala.y-policia.coord.y)/(bala.x-policia.coord.x);
            b = (policia.coord.y-m*policia.coord.x);

            if(ladrones[NUM].coord.y == m*ladrones[NUM].coord.x+b){
                respawn_criminal(NUM);
                aumentar_tiempo();
                
                if (op == 2)
                {
                    arma[0] += 10;
                }
                
                return;
            }
        }
        //Ametralladora
        if (arma_num == 2)
        {

            if(direc == 0 && policia.coord.x-1 > 4)
            {
                bala.x = policia.coord.x-1;
                bala.y = policia.coord.y;

                gotoxy(bala.x,bala.y);
                printf("%c",196);
                borrar[0] = 1;
                

            }
            if (direc == 1 && policia.coord.x+1 < 115)
            {
                bala.x = policia.coord.x+1;
                bala.y = policia.coord.y;

                gotoxy(bala.x,bala.y);
                printf("%c",196);
                borrar[0] = 1;
                
            }

            if (policia.coord.y - 1 > 2)
            {
                bala1.x = policia.coord.x;
                bala1.y = policia.coord.y-1;

                gotoxy(bala1.x,bala1.y);
                printf("%c",124);
                borrar[1] = 1;
                
            }
            

            if (policia.coord.y + 1 < 27)
            {
                bala2.x = policia.coord.x;
                bala2.y = policia.coord.y+1;

                gotoxy(bala2.x,bala2.y);
                printf("%c",124);
                borrar[2] = 1;
                
            }

            if(policia.coord.x == ladrones[NUM].coord.x && distancia_entre_dos_puntos(policia.coord.x,policia.coord.y,ladrones[NUM].coord.x,ladrones[NUM].coord.y) != 0)
            {
                respawn_criminal(NUM);
                aumentar_tiempo();
                if (op == 2)
                {
                    arma[1] += 30;
                }
                return;
            }

            if(ladrones[NUM].coord.y == policia.coord.y)
            {
                if(direc == 0 && ladrones[NUM].coord.x < policia.coord.x)
                {
                    respawn_criminal(NUM);
                    aumentar_tiempo();
                    if (op == 2)
                    {
                        arma[1] += 30;
                    }
                    return;
                }
                if (direc == 1 && ladrones[NUM].coord.x > policia.coord.x)
                {
                    respawn_criminal(NUM);
                    aumentar_tiempo();
                    if (op == 2)
                    {
                        arma[1] += 30;
                    }
                    
                    return;
                }
            }
        }
        //Uzi
        if (arma_num == 3)
        {
            //Posicion de la bala
            bala.x = policia.coord.x-1;
            bala.y = policia.coord.y-1;

            bala1.x = policia.coord.x+1;
            bala1.y = policia.coord.y-1;

            bala2.x = policia.coord.x-1;
            bala2.y = policia.coord.y+1;

            bala3.x = policia.coord.x+1;
            bala3.y = policia.coord.y+1;

            //Imprimir la bala

            if (bala.x > 4 && bala.x < 115 && bala.y > 2 && bala.y < 27)
            {
                gotoxy(bala.x,bala.y);
                cout<<"\\";
                borrar[0] = 1;
            }
            if (bala1.x > 4 && bala1.x < 115 && bala1.y > 2 && bala1.y < 27)
            {
                gotoxy(bala1.x,bala1.y);
                cout<<"/";
                borrar[1] = 1;
            }
            if (bala2.x > 4 && bala2.x < 115 && bala2.y > 2 && bala2.y < 27)
            {
                gotoxy(bala2.x,bala2.y);
                cout<<"/";
                borrar[2] = 1;
            }
            if (bala3.x > 4 && bala3.x < 115 && bala3.y > 2 && bala3.y < 27)
            {
                gotoxy(bala3.x,bala3.y);
                cout<<"\\";
                borrar[3] = 1;
            }
            
            //Eliminar al polcia

            //Ecuacion n1
            m = (bala.y-policia.coord.y)/(bala.x-policia.coord.x);
            b = (policia.coord.y-m*policia.coord.x);

            if(ladrones[NUM].coord.y == m*ladrones[NUM].coord.x+b){
                respawn_criminal(NUM);
                aumentar_tiempo();
                if (op == 2)
                {
                    arma[2] += 28;
                }
                
                return;
            }

            m = (bala1.y-policia.coord.y)/(bala1.x-policia.coord.x);
            b = (policia.coord.y-m*policia.coord.x);

            if(ladrones[NUM].coord.y == m*ladrones[NUM].coord.x+b){
                respawn_criminal(NUM);
                aumentar_tiempo();
                if (op == 2)
                {
                    arma[2] += 28;
                }
                return;
            }

        }

        //Escopeta
        if (arma_num == 4)
        {
            if (direc == 0)
            {

                bala.x = policia.coord.x - 1;
                bala.y = policia.coord.y - 1;

                bala1.x = policia.coord.x - 1;
                bala1.y = policia.coord.y;

                bala2.x = policia.coord.x - 2;
                bala2.y = policia.coord.y;

                bala3.x = policia.coord.x - 1;
                bala3.y = policia.coord.y + 1;

                if (bala.x > 4 && bala.x < 115 && bala.y > 2 && bala.y < 27)
                {
                    gotoxy(bala.x,bala.y);
                    cout<<"\\";
                    borrar[0] = 1;
                }
                if (bala1.x > 4 && bala1.x < 115 && bala1.y > 2 && bala1.y < 27)
                {
                    gotoxy(bala1.x,bala1.y);
                    printf("%c",175);
                    borrar[1] = 1;
                }
                if (bala2.x > 4 && bala2.x < 115 && bala2.y > 2 && bala2.y < 27)
                {
                    gotoxy(bala2.x,bala2.y);
                    printf("%c",176);
                    borrar[2] = 1;
                }
                if (bala3.x > 4 && bala3.x < 115 && bala3.y > 2 && bala3.y < 27)
                {
                    gotoxy(bala3.x,bala3.y);
                    cout<<"/";
                    borrar[3] = 1;
                }
                
            }
            if (direc == 1)
            {

                bala.x = policia.coord.x + 1;
                bala.y = policia.coord.y - 1;

                bala1.x = policia.coord.x + 1;
                bala1.y = policia.coord.y;

                bala2.x = policia.coord.x + 2;
                bala2.y = policia.coord.y;

                bala3.x = policia.coord.x + 1;
                bala3.y = policia.coord.y +1;

                if (bala.x > 4 && bala.x < 115 && bala.y > 2 && bala.y < 27)
                {
                    gotoxy(bala.x,bala.y);
                    cout<<"/";
                    borrar[0] = 1;
                }
                if (bala1.x > 4 && bala1.x < 115 && bala1.y > 2 && bala1.y < 27)
                {
                    gotoxy(bala1.x,bala1.y);
                    printf("%c",174);
                    borrar[1] = 1;
                }
                if (bala2.x > 4 && bala2.x < 115 && bala2.y > 2 && bala2.y < 27)
                {
                    gotoxy(bala2.x,bala2.y);
                    printf("%c",176);
                    borrar[2] = 1;
                }
                if (bala3.x > 4 && bala3.x < 115 && bala3.y > 2 && bala3.y < 27)
                {
                    gotoxy(bala3.x,bala3.y);
                    cout<<"\\";
                    borrar[3] = 1;
                }
                
            }

            if(direc == 1 && ladrones[NUM].coord.x < policia.coord.x)
            {
                return;
            }
            if (direc == 0 && ladrones[NUM].coord.x > policia.coord.x)
            {
                return;
            }
            
            m = 0;
            b = (bala.y);

            if(ladrones[NUM].coord.y == m*ladrones[NUM].coord.x+b){
                respawn_criminal(NUM);
                aumentar_tiempo();
                arma[2] += 2;
                return;
            }

            m = 0;
            b = (bala1.y);

            if(ladrones[NUM].coord.y == m*ladrones[NUM].coord.x+b){
                respawn_criminal(NUM);
                aumentar_tiempo();
                arma[2] += 2;
                return;
            }

            m = 0;
            b = (bala3.y);

            if(ladrones[NUM].coord.y == m*ladrones[NUM].coord.x+b){
                respawn_criminal(NUM);
                aumentar_tiempo();
                arma[2] += 2;
                return;
            }

            
        }
        
    }

    if (op == 2)
    {
        Tiempo = AUXT;
    }
    
}

void mostrar_arma(){
    gotoxy(3,28);
    if(arma_num == 1)
    {
        cout<<"- 1.Duales: "<<arma[0]*2<<" | ";
    }
    else
    {
        cout<<"1.Duales: "<<arma[0]*2<<" | ";
    }

    if(arma_num == 2)
    {
        cout<<"- 2.Ametralladora: "<<arma[1]<<" | ";
    }
    else
    {
        cout<<"2.Ametralladora: "<<arma[1]<<" | ";
    }

    if(arma_num == 3)
    {
        cout<<"- 3.Uzi: "<<arma[2]<<" | ";
    }
    else
    {
        cout<<"3.Uzi: "<<arma[2]<<" | ";
    }

    if(arma_num == 4)
    {
        cout<<"- 4.Escopeta: "<<arma[3]<<"            ";
    }
    else
    {
        cout<<"4.Escopeta: "<<arma[3]<<"            ";
    }

}

void aumentar_tiempo(){
    Tiempo = (Tiempo/60)*60 + 60; 
}

void anadir_elemento(int XXX){
    
    int *AUX;
    numero_p ++;

    AUX = new int[numero_p];

    for (int i = 0; i < numero_p-1; i++)
    {
        AUX[i] = POWER[i];
    }

    AUX[numero_p-1] = XXX;

    delete POWER;
    POWER = new int[numero_p];

    for (int i = 0; i < numero_p; i++)
    {
        POWER[i] = AUX[i];
    }
    
}

void delete_element(int XXX){
    int *AUX;
    numero_p -= 1;
    AUX = new int[numero_p];
    for(int i = 0,c = 0; i < numero_p+1; i++)
    {
        if(POWER[i] != XXX)
        {
            AUX[c] = POWER[i];
            c++;
        }
    }
    delete POWER;
    POWER = new int[numero_p];
    for(int i = 0; i < numero_p; i++)
    {
        POWER[i] = AUX[i];
    }
    delete AUX;
}

void GET_power(){

    if (op == 1)
    {
        if (policia.coord.x == object.coord.x && policia.coord.y == object.coord.y)
        {
            object.value = 0;
            return;
        }

        if (distancia_entre_dos_puntos(object.coord.x, object.coord.y, jugador.coord.x, jugador.coord.y) != 0
            &&
            distancia_entre_dos_puntos(object.coord.x, object.coord.y, ladron.coord.x, ladron.coord.y) != 0)
        {
            return;
        }
    }

    if (op == 2)
    {
        for (int i = 0; i < 4; i++)
        {
            if (distancia_entre_dos_puntos(ladrones[i].coord.x,ladrones[i].coord.y,object.coord.x,object.coord.y) == 0 && ladrones[i].coord.x != -1)
            {
                vidas -= 1;
                for (int i = 0; i < 4; i++)
                {
                    if(ladrones[i].coord.x == -1)
                    {
                        respawn_criminal(i);
                        break;
                    }
                }
                
                object.value = 0;
                return;
            }
        }
        

        if (policia.coord.x != object.coord.x || policia.coord.y != object.coord.y)
        {
            return;
        }
    }

    int value = object.value;
    object.value = 0;

    aumentar_tiempo();

    if (op == 1)
    {
        switch (value)
        {
        case 1:
            arma[3] += 2;
            return;
            break;
        case 2:
            arma[2] += 28;
            return;
            break;
        case 3:
            arma[1] += 30;
            return;
            break;
        case 4:
            arma[0] += 10;
            return;
            break;
        case 5:
            family_L = true;
            delete_element(5);
            return;
            break;
        case 6:
            freeze_time = 1;
            delete_element(6);
            return;
            break;
        case 7:
            vidas++;
            return;
            break;
        case 8:
            aumentar_tiempo();
            return;
            break;
        }
    }
    else
    {
        switch (value)
        {
        case 1:
            arma[3] += 2;
            return;
            break;
        case 2:
            arma[2] += 28;
            return;
            break;
        case 3:
            arma[1] += 30;
            return;
            break;
        case 4:
            arma[0] += 10;
            return;
            break;
        case 5:
            for (int I = 0;true; I = 0)
            {
                for (int i = 0; i < 4; i++)
                {
                    if(ladrones[i].coord.x != -1)
                    {
                        I ++;
                    }
                }

                if (I == 1)
                {
                    return;
                }
                
                for(int i = 0; i < 4; i++)
                {
                    if(ladrones[i].coord.x != -1)
                    {
                        gotoxy(ladrones[i].coord.x,ladrones[i].coord.y);
                        cout<<" ";
                        ladrones[i].coord.x = -1;
                        break;
                    }
                    
                }
                break;
            }
            
            return;
            break;
        case 6:
            freeze_time = 1;
            delete_element(6);
            return;
            break;
        case 7:
            vidas++;
            return;
            break;
        case 8:
            aumentar_tiempo();
            return;
            break;
        }
    }
    
}

void power_up(){
    
    if(numero_majico(0,1) == 0 && object.value == 0)
    {

        object.value = POWER[numero_majico(1,numero_p)-1];
         
        do
        {
            object.coord.x = numero_majico(5,114);
            object.coord.y = numero_majico(3,26);
        }
        while (object.coord.x == jugador.coord.x && jugador.coord.y == object.coord.y 
               ||
               object.coord.x == ladron.coord.x && object.coord.y == ladron.coord.y
               ||
               object.coord.x == policia.coord.x && object.coord.y == policia.coord.y
               );
        
        gotoxy(object.coord.x,object.coord.y);
        printf("%c",127);
    }

    gotoxy(114,0);
    cout<<object.value;

    if(object.value == 0)
    {
        return;
    }

    GET_power();
    
    
}

void jugador_controles_ladron(){

    coordenadas aux;

    aux.x = jugador.coord.x;
    aux.y = jugador.coord.y;
    
    if(GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState('W') != 0)
    {
        if (jugador.coord.y - 1 > 2)
        {
            gotoxy(jugador.coord.x,jugador.coord.y);
            cout<<" ";
            jugador.coord.y -= 1;
            gotoxy(jugador.coord.x,jugador.coord.y);
            printf("%c",254);
        }
        
    }
    if (GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState('S') != -0)
    {
        if (jugador.coord.y + 1 < 27)
        {
            gotoxy(jugador.coord.x,jugador.coord.y);
            cout<<" ";
            jugador.coord.y ++;
            gotoxy(jugador.coord.x,jugador.coord.y);
            printf("%c",254);
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) != 0 || GetAsyncKeyState('D') != 0 )
    {
        if (jugador.coord.x + 1 < 115)
        {
            gotoxy(jugador.coord.x,jugador.coord.y);
            cout<<" ";
            jugador.coord.x++;
            gotoxy(jugador.coord.x,jugador.coord.y);
            printf("%c",254);
        }
        direc = 1;
        
    }
    if (GetAsyncKeyState(VK_LEFT) != 0 || GetAsyncKeyState('A') != 0 )
    {
        if (jugador.coord.x > 5)
        {
            gotoxy(jugador.coord.x,jugador.coord.y);
            cout<<" ";
            jugador.coord.x -= 1;
            gotoxy(jugador.coord.x,jugador.coord.y);
            printf("%c",254);
        }
        direc = 0;
    }



    if(GetAsyncKeyState('1') != 0)
    {
        arma_num = 1;

    }

    if(GetAsyncKeyState('2') != 0)
    {
        arma_num = 2;
    }

    if(GetAsyncKeyState('3') != 0)
    {
        arma_num = 3;
    }

    if(GetAsyncKeyState('4') != 0)
    {
        arma_num = 4;
    }

    if(GetAsyncKeyState(VK_SPACE) != 0)
    {
        ataque_ladron();
    }

    if (ladron.coord.x == aux.x && ladron.coord.y == aux.y && family_L == true)
    {
        if (aux.x != jugador.coord.x || aux.y != jugador.coord.x)
        {
            gotoxy(ladron.coord.x, ladron.coord.y);
            cout<<"L";
        }
        
    }

}

void jugador_controles_policia(){

    coordenadas aux;

    aux.x = policia.coord.x;
    aux.y = policia.coord.y;
    
    if(GetAsyncKeyState(VK_UP) != 0 || GetAsyncKeyState('W') != 0)
    {
        if (policia.coord.y - 1 > 2)
        {
            gotoxy(policia.coord.x,policia.coord.y);
            cout<<" ";
            policia.coord.y -= 1;
            gotoxy(policia.coord.x,policia.coord.y);
            printf("%c",254);
        }
        
    }
    if (GetAsyncKeyState(VK_DOWN) != 0 || GetAsyncKeyState('S') != -0)
    {
        if (policia.coord.y + 1 < 27)
        {
            gotoxy(policia.coord.x,policia.coord.y);
            cout<<" ";
            policia.coord.y ++;
            gotoxy(policia.coord.x,policia.coord.y);
            printf("%c",254);
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) != 0 || GetAsyncKeyState('D') != 0 )
    {
        if (policia.coord.x + 1 < 115)
        {
            gotoxy(policia.coord.x,policia.coord.y);
            cout<<" ";
            policia.coord.x++;
            gotoxy(policia.coord.x,policia.coord.y);
            printf("%c",254);
          }
        direc = 1;
        
    }
    if (GetAsyncKeyState(VK_LEFT) != 0 || GetAsyncKeyState('A') != 0 )
    {
        if (policia.coord.x > 5)
        {
            gotoxy(policia.coord.x,policia.coord.y);
            cout<<" ";
            policia.coord.x -= 1;
            gotoxy(policia.coord.x,policia.coord.y);
            printf("%c",254);
        }
        direc = 0;
    }

    

    if(GetAsyncKeyState('1') != 0)
    {
        arma_num = 1;

    }

    if(GetAsyncKeyState('2') != 0)
    {
        arma_num = 2;
    }

    if(GetAsyncKeyState('3') != 0)
    {
        arma_num = 3;
    }

    if(GetAsyncKeyState('4') != 0)
    {
        arma_num = 4;
    }

    if(GetAsyncKeyState(VK_SPACE) != 0)
    {
        for(int i = 0; i < 4; i++)
        {
            if (ladrones[i].coord.x != -1)
            {
                ataque_policia(i);
            }
            
        }
    }


}

void mostrar_vida(){
    
    gotoxy(0,0);
    score ++;
    cout<<"    Puntaje: "<<score;
    cout<<" Vidas: "<<vidas;
    cout<<" Tiempo: "<<Tiempo<<"   ";


}

void game_ladron(){

    system("cls");
    fondo1();
    spawn_criminal_mode();
    while (true)
        {

            mostrar_vida();

            jugador_controles_ladron();

            movimiento_policia();

            if (family_L == true)
            {
                movimiento_ladron();
            }
            else
            {
                ladron.coord.x = jugador.coord.x;
                ladron.coord.y = jugador.coord.y;
            }

            power_up();

            mostrar_arma();

            if (freeze_time == 0)
            {
                Tiempo -= 1;
            }
            else
            {
                if (freeze_time == 2)
                {
                    freeze_time = 1;
                    Tiempo -= 1;
                }
                else
                {
                    if(freeze_time == 1)
                    {
                        freeze_time ++;
                    }
                }
            }


            if(Tiempo == 0 || policia.coord.x == jugador.coord.x && policia.coord.y == jugador.coord.y)
            {
                vidas -= 1;
                Tiempo = 60;
                
                if(vidas == 0)
                {
                    object.value = 0;
                    vel = 0;
                    if (family_L = true)
                    {
                        family_L = false;
                        anadir_elemento(6);
                    }
                    
                    arma_num = 1;

                    if (freeze_time != 0)
                    {
                        freeze_time = 0;
                        anadir_elemento(6);
                    }
                    
                    for(int i = 0; i < 4; i ++)
                    {
                        arma[i] = 0;
                    }
                    you_lose();
                    return;
                }

                break;
            }

            Sleep(75);

            borrar_bala();
            
        }
    object.value = 0;
    vel = 0;
    game_ladron();
}

void game_policia(){
    //Rumania bangladesh y ecuador
    vidas = 10;
    system("cls");
    fondo1();
    spawn_police_mode();

    while (true)
    {
        
        mostrar_vida();
        mostrar_arma();
        jugador_controles_policia();

        for(int i = 0; i < 4; i ++)
        {
            if(ladrones[i].coord.x != -1)
            {
                movimiento_Ladrones(i);
            }

        }

        power_up();

        if(freeze_time == 0)
        {
            Tiempo -= 1;
        }
        else
        {
            if(freeze_time == 2)
            {
                freeze_time = 1;
                Tiempo -= 1;
            }
            if (freeze_time == 1)
            {
                freeze_time ++;
            }
            
        }

        if(Tiempo == 0)
        {
            Tiempo = 60;
            vidas -= 1;
            
            for (int I = 0; I < 4; I++)
            {
                if(ladrones[I].coord.x == -1)
                {
                    respawn_criminal(I);
                    break;
                }
            }
        }
        

        if (vidas == 0)
        {
            object.value = 0;
            freeze_time = 0;
            anadir_elemento(5);
            you_lose();
            return;
        }

        Sleep(75);
        borrar_bala();
        for(int i = 0; i < 4; i++)
        {
            borrar_balas(i);
        }
    }

}


// a = (1,1);
// b = (2,2);


//d1 = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))

//1,2,3,4,5,6,7,8,9

//aux = a

//aux---Lo modificamos

//d2 = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))


//d2 <= d1
//Se repite el ciclo
//d2 > d1
//a = aux














