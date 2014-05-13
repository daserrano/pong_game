#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define MAXLINES 40
#define ESC 27
#define ESP 32
#define MAX 5

typedef struct TCoordenada{

    double x;
    double y;

} Coordenada; 

void PintadoPresentacion(){

    system("clear");

    char tablero[MAXLINES];
    FILE *fp;

    if ((fp = fopen ("presentacion.txt", "r")) ==  NULL) {
	fprintf(stderr, "Error: %s NOT FOUND \n", "presentacion.txt");
	exit(EXIT_FAILURE);
    }


    char pixel;
    while( (pixel = fgetc(fp)) != EOF){
	printw("%c", pixel);
    }


    refresh();
    fclose(fp);

} 

void PintadoTablero(){

    system("clear");

    char tablero[MAXLINES];
    FILE *fp;

    if ((fp = fopen ("pantalla.txt", "r")) ==  NULL) {
	fprintf(stderr, "Error: %s NOT FOUND \n", "pantalla.txt");
	exit(EXIT_FAILURE);
    }

    attron(COLOR_PAIR(1));

    char pixel;
    while( (pixel = fgetc(fp)) != EOF){
	printw("%c", pixel);
    }

    attroff(COLOR_PAIR(1));

    refresh();
    fclose(fp);
}

void RellenarJugador(Coordenada jugador1[MAX]){

    for(int i=0; i < MAX ; i++){
	jugador1[i].x = 5;
        jugador1[i].y = 5 + i;
    }

}

void MuestraJugador(Coordenada jugador1[MAX]){
    clear();
    PintadoTablero();

    for(int i=0; i < MAX; i++)
	mvprintw(jugador1[i].y, jugador1[i].x, "|");

    refresh();

}

void MoverJugador(Coordenada jugador1[MAX]){

    for(int i= MAX-1; i>0; i--)
	jugador1[i].y = jugador1[i-1].y;


}
void Juego(){

    Coordenada jugador1[MAX];

    //PintadoTablero();

    RellenarJugador(jugador1);
    MuestraJugador(jugador1);
    MoverJugador(jugador1);


}

int main(int argc, char *argv[]){

    int user_input = 0;

    initscr();
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    PintadoPresentacion();  
    getch();
    clear();

    do{
	Juego();

    }while(user_input = getch() != ESC);
    endwin();

    return EXIT_SUCCESS;
}
