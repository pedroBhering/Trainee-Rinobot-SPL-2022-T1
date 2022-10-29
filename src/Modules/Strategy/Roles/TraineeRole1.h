#ifndef RINO_PLAYER_H
#define RINO_PLAYER_H

#include "Role.h"

using namespace std;

class TraineeRole1: public Role {

private:
    bool onStart;
    int variavelQualquer;
    int timeH = 0; //variavel de controle para fazer o robo manter a cabeça reta
    int timeLow = 0; //variavel de controle para fazer o robo abaixar a cabeça
    int timeFound = 0; //variavel de controle para fazer o robo falar que a bola foi encontrada
    int timeSp = 0; //variavel de controle para fazer o robo falar que a bola foi avistada
    int timeSay = 0; //variavel de controle para fazer o robo falar que está procurando a bola
    bool spinL = false; //girou para a esquerda
    bool spinR = false; //girou para a direita

public:

    TraineeRole1(SpellBook *spellBook);
    ~TraineeRole1();
    void Tick(float ellapsedTime, const SensorValues&);

};
#endif
