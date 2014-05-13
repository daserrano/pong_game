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

struct TJugador{

    Coordenada jugador[MAX];

};

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

void Juego(){

    PintadoTablero();

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
