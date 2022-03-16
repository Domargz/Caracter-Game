
typedef struct 
{
    int y;
    int x;
} posicion;

struct jugador
{
    posicion pos;
    char mono[7];
};
struct enemy
{
    posicion pos;
    char caracter;
};





int init();
void run();
void closer();


void dibujarJugador(struct jugador*);
void moverJugador(int *, struct jugador*);
void limiteJugador(struct jugador*);



void dibujarEnemigo(struct enemy*);
void moverEnemigo(struct enemy*);
void borrarEnemigo(struct enemy*);
void limiteEnemigo(struct enemy*);
void logicaEnemigo(struct enemy*);

void colision(struct enemy*, struct jugador*, int *, int *);
void borrarJugador(struct jugador*);

void update(void);
