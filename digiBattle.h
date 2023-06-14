#ifndef DIGIBATTLE
#define DIGIBATTLE

#include <iostream>
#include <fstream> //probando file library
#include <cstdio> // tambien pa probar
#include "tablero.h"
#include "casillero.h"
#include "cartas.h"
#include "jugador.h"
#include <cstdlib>




/*struct Jugador{
    int vidas;
    int numDeJugador;
    Lista<Ubicacion>* tropas;
    Lista<Carta*>* cartas;
};*/

class DigiBattle {
private:
    FILE* tableroArchivo;                   //BMP del tablero
    Tablero* tablero;                       //Tablero lol
    Lista<Jugador*>* jugadores;             //Puntero a lista con punteros a structs jugador que tienen punteros a lista de ints (son los numeros del soldado del jugador) y puntero a lista con 
    Lista<Casillero*>* casillerosInactivos; //Puntero a lista de punteros a los casilleros inactivos actuales (para bajarles el contador directamente desde digibattle)
    
    //Metodos
    /*
    Pre: Recibe que tipo de artilleria se va a utilizar
    Pos: Devuelve un struct con coordenadas validadas segun artilleria
    */
    Ubicacion pedirUbicacion(Artilleria tipo);

    /*
    Pre: Debe elegirse un jugador existente
    Pos: Devuelve un puntero al jugador buscado o NULL si no se encontró
    */
    Jugador* buscarJugador(int nroJugador);

    /*
    Pre: Recibe coordenadas y un tipo de artilleria
    Pos: Devuelve true si el casillero existe y es válido para la artillería requerida
    */ 
    bool validarCasillero(Ubicacion posicion, Artilleria tipo);
    
    /*
    Pre: Recibe dos ubicaciones dentro del tablero para mover SOLDADO o BARCO
    Pos: Devuelve TRUE si la distancia de movimiento y la direccion es permitida
    */
    bool validarMovimiento(Ubicacion ubiSoldado, Ubicacion ubiNueva );

    /*
    Pre: 
    Pos: Reduce los turnos inactivos de las casillas inactivas
    */
    void reducirCasilleroInactivo();

    /*
    Pre: Debe de haber quedado solo un jugador con vida 
    Pos: Anuncia quien fue el ganador y da por terminada la partida
    */
    void anunciarGanador();
    
    /*
    Pre: La carta debe existir en la lista
    Pos: Usa una carta de la lista de cartas del jugador
    */
    void usarCarta(Jugador * jugador);
public:

    /*
    Pre:-
    Pos: Bob el constructor
    */
    DigiBattle();

    /*
    Pre:
    Pos: Bob el destructor
    */
    ~DigiBattle();

    /*
    Pre:
    Pos: Pide cantidad de jugadores, cantidad de tropas y tamanio de mapa en formato XYZ
    */
    void iniciarJuego();

    /*
    Pre:
    Pos: maneja el numero de turnos, a qué jugador corresponde y la cuenta de casilleros inactivos
    */
    void turno();

    /*
    Pre:
    Pos: Pide la posicion XYZ en la que se va a poner la mina
    */
    void ponerMina(int jugador);

    /*Pre:
    Pos: Si se decide mover una tropa, se puede hacer en vertical, horizontal o diagonal
    */
    void moverTropa();

    /*Pre: Recibe una Artilleria, y la lista de tropas que tiene el jugador
    Pos: Muestra en pantalla el tipo de tropa, el numero de tropa y la ubicacion de cada tropa de ese tipo
    */
    void mostrarTropasDisponibles(Artilleria seleccionTropa, Lista<InfoTropa*>* tropasDelJugador);

    /*
    Pre:
    Pos: Agrega una carta a la lista de cartas del jugador
    */
    void obtenerCarta(Jugador * jugador);
    
    /*
    Pre: Recibe un numero de jugador junto con un numero de soldado
    Pos: Le resta una vida al jugador ,ademas de sacarle el soldado
    */
    void bajarVidaJugador(int nroJugador,int nroSoldado);

    /*
    Pre: Recibe cantidad de tropas por jugador y cantidad de jugadores
    Pos: Coloca todos los tropas iniciales , por jugador
    */
    void colocarSoldados(int cantidadSoldados, int cantidadJugadores);

    /*
    Pre: Recibe numero de jugador ,numero de soldado , y la ubicacion
    Pos: Coloca el soldado si la artillera en la ubicacion es VACIO y si es SOLDADO se muere el soldado que estaba en la
    ubicacion y el que se iba a colocar
    */
    void ponerSoldado(Ubicacion ubicacionSoldado,int nroJugador,int nroSoldado);

    /*
    Pre: ~~
    Pos: Devuelve un numero aleatorio entre 3 y 6
    */
    int poderMina();

    /*Pre: Debe recibir un puntero a jugador y el tipo de Artilleria a elegir
    Pos: Devuelve el numero de tropa a mover
    */
    int pedirTropaAElegir(Jugador * jugador, Artilleria seleccionTropa);

    /*
    Pre:
    Pos:
    */
    int getPosicionJugadorEnLista(int nroJugador);

    /*Pre: Recibe una Artilleria, la cantidad de aviones y la cantidad de barcos disponibles
    Pos: Devuelve TRUE si la Artilleria recibida existe y tiene al menos 1 disponible para usar
    */
    bool comprobarSeleccionTropa(Artilleria seleccionTropa, int cantidadAviones, int cantidadBarcos);

    /*
    Pre: Recibe el casillero, la artillería y el numero de jugador
    Pos: Compara la artillería con el contenido y devuelve true si la artillería se coloca o false si se destruye
    */
    bool resolverColision(Casillero* casillero , Artilleria artilleria, int nroJugador);

    /*
    Pre: Recibe el casillero, la artillería y el numero de jugador y numero de soldado
    Pos: Revisa el contenido del casillero y coloca el soldado o lo elimina según corresponda
    */
    bool resolverColision(Casillero* casillero, Artilleria artilleria, int nroJugador, int nroSoldado);

    /*
    Pre: -
    Pos: Revisa si se cumplen las condiciones de victoria
    */
    bool comprobarVictoria(int nroJugador);

    /*
    Pre: ~~
    Pos: Mata todo en su radio y desactiva las casillas la cantidad de turnos correspondientes
    */
    void cartaAtaqueQuimico(Ubicacion posicion);

    /*
    Pre: ~~
    Pos: Agrega un Avion al tablero y a la lista tropas del jugador
    */
    void cartaAvionRadar(Jugador * jugador);

    /*
    Pre: ~~
    Pos: Agrega un Barco al tablero y a la lista tropas del jugador
    */
    void cartaBarco(Jugador * jugador);

    /*
    Pre: ~~
    Pos: Agrega 2 cartas al jugador
    */
    void cartaPotOfGreed(Jugador * jugador);

    /*
    Pre:~~
    Pos: Agrega 2 Soldados al tablero y a la lista tropas del jugador 
    */
    void cartaAgregarSoldados(Jugador * jugador);

    /*
    Pre:~~
    Pos:
    */
    void cartaRayoLaser(Jugador * jugador);

    /*
    Pre:
    Pos: Devuelve la lista de jugadores
    */
    Lista<Jugador*>* getListaJugadores();

    /*
    Pre:
    Pos: 
    */
    void archivo();

};
#endif