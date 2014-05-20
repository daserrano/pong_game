#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>

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

    char pixel;
    while( (pixel = fgetc(fp)) != EOF){
	if( pixel == '#'){
	    attron(COLOR_PAIR(1));
	    printw("%c", pixel);
	    attroff(COLOR_PAIR(1));
	}
	else if( pixel == '|'){
	    attron(COLOR_PAIR(2));
	    printw("%c", pixel);
	    attroff(COLOR_PAIR(2));
	}
	else
	    printw("%c", pixel);

    }

    //attroff(COLOR_PAIR(1));

    refresh();
    fclose(fp);
}

void RellenarJugador(Coordenada jugador1[MAX]){

    for(int i=0; i < MAX ; i++){
	jugador1[i].x = 5;
	jugador1[i].y = 15 + i;
    }

}

void MuestraJugador(Coordenada jugador1[MAX]){
    clear();
    PintadoTablero();

    attron(COLOR_PAIR(2));
    for(int i=0; i < MAX; i++)
	
	mvprintw(jugador1[i].y, jugador1[i].x, "||");

    attroff(COLOR_PAIR(2));
    refresh();

}

void MoverJugador(Coordenada jugador1[MAX], Coordenada incremento){

    for(int i= MAX-1; i>0; i--)
	jugador1[i].y = jugador1[i-1].y;

    jugador1[0].y += incremento.y;

}  

int main(int argc, char *argv[]){

    int user_input = 0;
    Coordenada jugador1[MAX];
    Coordenada movimiento = {0 , 1};

    initscr(); // iniciar tablero de ncurses.
    start_color();

    init_pair(1, COLOR_BLUE, COLOR_BLUE); // Colorear.
    init_pair(2, COLOR_WHITE, COLOR_WHITE);

    //halfdelay(2);
    keypad(stdscr, TRUE); // Poder utilizar las flechas.
    noecho(); //No se muestre el caracter pulsado.
    curs_set(0); // Desaparecer el puntero.

    RellenarJugador(jugador1);

    PintadoPresentacion();  

    while((user_input = getch()) != ESP){
    }
    clear();   // Limpia la pantalla.

    do{
	switch(tolower(user_input = getch())){    // Es lo mismo mayuscula que minuscula.
	    case 'w':
		movimiento.x = 0;
		movimiento.y = -1;
		break;

	    case 's':
		movimiento.x = 0;
		movimiento.y = 1;
		break;

	}

	    MoverJugador(jugador1, movimiento);
	    MuestraJugador(jugador1);

    }while(user_input = getch() != ESC);
    endwin(); // Finaliza el tablero de ncurses.
 
    return EXIT_SUCCESS;
}
