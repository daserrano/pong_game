#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdio_ext.h>

#define MAXLINES 40
#define ESC 27
#define ESP 32
#define MAX 5

typedef struct TCoordenada{

    int x;
    int y;

} Coordenada; 

typedef struct TPelota{

    Coordenada posicion;
    Coordenada velocidad;

} Pelota;   

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

void PintadoTablero(Pelota pelota){


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
    attron(COLOR_PAIR(3));
    mvprintw(pelota.posicion.y, pelota.posicion.x, "O");
    attroff(COLOR_PAIR(3));
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

    for(int i=0; i < MAX; i++)
	mvprintw(jugador1[i].y, jugador1[i].x, "||");
    
    refresh();

}

void MuestraJugador2(Coordenada jugador2[MAX]){

    for(int i=0; i < MAX; i++)
	mvprintw(jugador2[i].y, jugador2[i].x, "||");
    
    refresh();

}

void MoverJugadorArriba(Coordenada jugador[MAX], Coordenada incremento){

    for(int i= MAX-1; i>0; i--)
	jugador[i].y = jugador[i-1].y;

    jugador[0].y += incremento.y;

}

void MoverJugadorAbajo(Coordenada jugador[MAX], Coordenada incremento){

    for(int i=0; i<MAX-1; i++)
	jugador[i].y = jugador[i+1].y;

    jugador[MAX-1].y += incremento.y;

}  

void MovimientoPelota( Coordenada jugador1[MAX], Coordenada jugador2[MAX], Pelota *pelota){

    for(int i=0; i <= MAX; i++){
	if(i>=0 && i<2){
	    if(pelota->posicion.y == jugador2[i].y && pelota->velocidad.x > 0 && (pelota->posicion.x)+1 == jugador2[i].x){
		pelota->velocidad.x = -1;
		pelota->velocidad.y = -1;
		break;
	    }
	    else if(pelota->posicion.y == jugador1[i].y && pelota->velocidad.x < 0 && (pelota->posicion.x)-1 == jugador1[i].x){
		pelota->velocidad.x =  1;
		pelota->velocidad.y = -1;
		break;
	    }

	}
	else if(i==2){
	    if(pelota->posicion.y == jugador2[i].y && pelota->velocidad.x > 0 && (pelota->posicion.x)+1 == jugador2[i].x){
		pelota->velocidad.x = -1;
		pelota->velocidad.y =  0;
		break;
	    }
	    else if(pelota->posicion.y == jugador1[i].y && pelota->velocidad.x < 0 && (pelota->posicion.x)-1 == jugador1[i].x){
		pelota->velocidad.x = 1;
		pelota->velocidad.y = 0;
		break;
	    }
	}
	else if(i>2 && i<=MAX){
	    if(pelota->posicion.y == jugador2[i].y && pelota->velocidad.x > 0 && (pelota->posicion.x)+1 == jugador2[i].x){
		pelota->velocidad.x = -1;
		pelota->velocidad.y =  1;
		break;
	    }
	    else if(pelota->posicion.y == jugador1[i].y && pelota->velocidad.x < 0 && (pelota->posicion.x)-1 == jugador1[i].x){
		pelota->velocidad.x = 1;
		pelota->velocidad.y = 1;
	    }
	}
    }
}

void ReinicioPelota(Pelota *pelota){
    pelota->posicion.x  = 49;
    pelota->posicion.y  = 17;
    pelota->velocidad.y =  0;

} 

bool LimitesPelota(Pelota *pelota){
    if((pelota->posicion.y == 2 && pelota->velocidad.x < 0)){
	pelota->velocidad.y =  1;
	pelota->velocidad.x = -1;
    }
    if((pelota->posicion.y == 32 && pelota->velocidad.x < 0)){
	pelota->velocidad.y = -1;
	pelota->velocidad.x = -1;
    }
    if((pelota->posicion.y == 2 && pelota->velocidad.x > 0)){
	pelota->velocidad.y = 1;
	pelota->velocidad.x = 1;
    }
    if((pelota->posicion.y == 32 && pelota->velocidad.x > 0)){
	pelota->velocidad.y = -1;
	pelota->velocidad.x =  1;
    }

}

int main(int argc, char *argv[]){

    char opcion = 0;
    int user_input = 0;


    Coordenada jugador1[MAX];
    Coordenada jugador2[MAX];
    Pelota pelota = {30, 17};
    Coordenada movimiento1 = {0 , 1};
    Coordenada movimiento2 = {0 , 1};

    static int puntuacionJugador1 = 0, puntuacionJugador2 = 0;

    initscr(); // iniciar tablero de ncurses.
    start_color();

    init_pair(1, COLOR_RED, COLOR_RED); // Colorear.
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);

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
    pelota.velocidad.x = 1;
    pelota.velocidad.y = 0;
    do{
	timeout(100);
	user_input = getch();
	switch(user_input){    // Es lo mismo mayuscula que minuscula.
	    case 'w':
		movimiento1.x = 0;
		movimiento1.y = -1;
		if(jugador1[0].y > 2)
		    MoverJugadorArriba(jugador1, movimiento1);
		break;

	    case 's':
		movimiento1.x = 0;
		movimiento1.y = 1;
		if(jugador1[MAX-1].y < 32)
		    MoverJugadorAbajo(jugador1, movimiento1);
		break;

	    case KEY_UP:
		movimiento2.x = 0;
		movimiento2.y = -1;
		if(jugador2[0].y > 2)
		    MoverJugadorArriba(jugador2, movimiento2);
		break;

	    case KEY_DOWN:
		movimiento2.x = 0;
		movimiento2.y = 1;
		if(jugador2[MAX-1].y < 32)
		    MoverJugadorAbajo(jugador2, movimiento2);
		break;

	}



	if(pelota.posicion.x < 4){
	    ReinicioPelota(&pelota);
	    pelota.velocidad.x = -1;
	    puntuacionJugador2++;

	} 
	else if(pelota.posicion.x > 93){ 
	    ReinicioPelota(&pelota);
	    pelota.velocidad.x = 1;
	    puntuacionJugador1++;
	}
	if(LimitesPelota( &pelota)){
	    MovimientoPelota(jugador1, jugador2, &pelota);
	}
	pelota.posicion.x += pelota.velocidad.x; 
	pelota.posicion.y += pelota.velocidad.y;
	erase();
	PintadoTablero(pelota);
	attron(COLOR_PAIR(4));
	MuestraJugador(jugador1);
	attroff(COLOR_PAIR(4));
	attron(COLOR_PAIR(5));
	MuestraJugador(jugador2);
	attroff(COLOR_PAIR(5));

	attron(COLOR_PAIR(6));
	mvprintw(36, 45, "%i", puntuacionJugador1);
	attroff(COLOR_PAIR(6));
	mvprintw(36, 48, "-");
	attron(COLOR_PAIR(7));
	mvprintw(36, 51, "%i", puntuacionJugador2);
	attroff(COLOR_PAIR(7));

    }while(user_input != ESC && (puntuacionJugador1 < 7 && puntuacionJugador2 < 7));
    timeout(1000000000);
    //clear();
    mvprintw(36, 59, "¿Jugar otra partida? s/n ");
    refresh();
    __fpurge(stdin);
    opcion = getchar();
    __fpurge(stdin);

    if(opcion == 's'){
	puntuacionJugador1 = 0;
    	puntuacionJugador2 = 0;
	pelota.posicion.x = 45;
	pelota.posicion.y = 17;
    }
    }while (opcion != 'n');
    endwin(); // Finaliza el tablero de ncurses.

    return EXIT_SUCCESS;
}
