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

void RellenarJugador1(Coordenada jugador1[MAX]){

    for(int i=0; i < MAX ; i++){
	jugador1[i].x = 5;
	jugador1[i].y = 15 + i;
    }

}

void RellenarJugador2(Coordenada jugador2[MAX]){

    for(int i=0; i < MAX ; i++){
	jugador2[i].x = 93;
	jugador2[i].y = 15 + i;
    }

}

void MuestraJugador(Coordenada jugador1[MAX]){
    /*clear();
    PintadoTablero();
*/
    attron(COLOR_PAIR(2));
    for(int i=0; i < MAX; i++)
	
	mvprintw(jugador1[i].y, jugador1[i].x, "||");

    attroff(COLOR_PAIR(2));
    refresh();

}

void MuestraJugador2(Coordenada jugador2[MAX]){
   /* clear();
    PintadoTablero();
*/
    attron(COLOR_PAIR(2));
    for(int i=0; i < MAX; i++)
	
	mvprintw(jugador2[i].y, jugador2[i].x, "||");

    attroff(COLOR_PAIR(2));
    refresh();

}

void MoverJugadorArriba(Coordenada jugador[MAX], Coordenada incremento){

    for(int i= MAX-1; i>0; i--)
	jugador[i].y = jugador[i-1].y;

    jugador[0].y += incremento.y;

}

void MoverJugadorAbajo(Coordenada jugador[MAX], Coordenada incremento){

    for(int i=0; i<MAX; i++)
	jugador[i-1].y = jugador[i].y;

    jugador[MAX-1].y += incremento.y;

}  

void MoverJugador2Arriba(Coordenada jugador[MAX], Coordenada incremento){

    for(int i= MAX-1; i>0; i--)
	jugador[i].y = jugador[i-1].y;

    jugador[0].y += incremento.y;

}

void MoverJugador2Abajo(Coordenada jugador[MAX], Coordenada incremento){

    for(int i=0; i<MAX; i++)
	jugador[i-1].y = jugador[i].y;

    jugador[MAX-1].y += incremento.y;

} 

int main(int argc, char *argv[]){

    int user_input = 0;
    Coordenada jugador1[MAX];
    Coordenada jugador2[MAX];
    Coordenada movimiento1 = {0 , 1};
    Coordenada movimiento2 = {0 , -1};

    initscr(); // iniciar tablero de ncurses.
    start_color();

    init_pair(1, COLOR_BLUE, COLOR_BLUE); // Colorear.
    init_pair(2, COLOR_WHITE, COLOR_WHITE);

    // ------------------------------------NO FUNCIONA EL HALFDELAY-------------------------------------
    halfdelay(2);
    keypad(stdscr, TRUE); // Poder utilizar las flechas.
    noecho(); //No se muestre el caracter pulsado.
    curs_set(0); // Desaparecer el puntero.

    RellenarJugador1(jugador1);
    RellenarJugador2(jugador2);

    PintadoPresentacion();  

    while((user_input = getch()) != ESP){
    }
    clear();   // Limpia la pantalla.

    do{

    halfdelay(2);
	switch(tolower(user_input = getch())){    // Es lo mismo mayuscula que minuscula.
	    case 'w':
		movimiento1.x = 0;
		movimiento1.y = -1;
		MoverJugadorArriba(jugador1, movimiento1);
		break;

	    case 's':
		movimiento1.x = 0;
		movimiento1.y = 1;
		MoverJugadorAbajo(jugador1, movimiento1);
		break;

	    case KEY_UP:
		movimiento2.x = 0;
		movimiento2.y = -1;
		MoverJugador2Arriba(jugador2, movimiento2);
		break;

	    case KEY_DOWN:  // ----------------------------- FUNCIONA MAL, SE BAJA TAMBIEN EL USUARIO 1. ----------------------
		movimiento2.x = 0;
		movimiento2.y = 1;
		MoverJugador2Abajo(jugador2, movimiento2);
		break;

	}

	clear();
	PintadoTablero();
	MuestraJugador(jugador1);
	MuestraJugador2(jugador2);

    }while(user_input = getch() != ESC);
    endwin(); // Finaliza el tablero de ncurses.

    return EXIT_SUCCESS;
}
