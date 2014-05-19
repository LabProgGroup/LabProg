#include "utils.h"

/*
  Recebe duas structs do tipo Position contendo posições (x,y,z) e retorna a distância 
  eucliana.
*/ 
float distance(Position a, Position b) { 
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z));
}

/*
  Recebe uma posição So, velocidade v e retorna a nova 
  posição após o tempo de atualização da tela.
 */
Position spaceTimeEquation(Position initialPosition, Velocity v) {
    Position newPosition;
    newPosition.x = initialPosition.x + v.x * clockTick;
    newPosition.y = initialPosition.y + v.y * clockTick;
    newPosition.z = initialPosition.z + v.z * clockTick;
    
    return newPosition;
}

/*
  Define o tick do relógio em segundos.
  clockTick = 1/fps.
*/
float clockTick = (float) 1/20;

/*
  Define a altura da janela do jogo
*/
int ySize = 20;

/*
  Define a largura da janela do jogo
*/
int xSize = 20;

Dimension defaultCenarioDim = {20, 20, 2000};   


/*
  Recebe a posição da nave e de algum outro objeto (tiro, inimigo) e verifica se ele ainda
  está na tela, retornando TRUE em case afirmativo e FALSE, caso contrário. 
*/
int isItAtScreen(Position shipP, Position objectP) {
	return shipP.z <= objectP.z;
}
