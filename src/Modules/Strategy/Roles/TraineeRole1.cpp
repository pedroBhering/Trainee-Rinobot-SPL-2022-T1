#include "TraineeRole1.h"
#include "Core/Utils/Math.h"
#include "Core/Utils/RelativeCoord.h"
#include "Core/Utils/RobotDefs.h"
#include "Core/Utils/CartesianCoord.h"

TraineeRole1::TraineeRole1(SpellBook *spellBook) : Role(spellBook)
{
    timeH = 0;
    timeFound = 0;
    timeSp = 0;
    timeSay = 0;
    timeL = 0;
    timeR = 0;
    degree = 0;

    ballSpotted = false;
    timeBall = 0;
    ballHere = false;
    gap = 0;
    angle = 0;
    timePitch = 0;
    foundBall = false;
    time = 0;

    timeLow = 0;
    timeHigh = 0;
    timeLeft = 0;
    timeRight = 0;

    headHigh = false;
    headLow = false;
    headLeft = false;
    headRight = false;

    abaixouC = false;
    rodou = false;
    ballDistActual = 0;
    dist = false;
    para  = true;
    andou = 0;
    h = 0.573;
    ballDistanceDif = 0;
    ballD = 0;



    onStart = false;
}
TraineeRole1::~TraineeRole1()
{
}

void TraineeRole1::lookingForTheBall(){
    spellBook->motion.Vx = 0;

    if(timeLeft < 3 && !headLeft){
        timeLeft++;
        spellBook->motion.HeadYaw = DEG2RAD(-90.f);
    }

    else
        headLeft = true;

    if(timeLow < 3 && !headLow && headLeft){
        timeLow++;
        spellBook->motion.HeadPitch = DEG2RAD(30.0f);
    }

    else
        headLow = true;

    if(timeRight < 6 && !headRight && headLow)
    {
        timeRight++;
        spellBook->motion.HeadYaw = DEG2RAD(90.f);
    }

     else
        headRight = true;

    if(timeHigh < 3 && !headHigh && headRight)
    {
        timeHigh++;
        spellBook->motion.HeadPitch = DEG2RAD(-30.0f);
    }

    else{
        headHigh = true;
        timeLeft = 0;
    }
    
    if(headLow && headRight && headLeft && headRight)
    {
        if(timeLeft < 3){
            timeLeft++;
            spellBook->motion.HeadYaw = DEG2RAD(-90.f);
        }
    }
}


void TraineeRole1::Tick(float ellapsedTime, const SensorValues &sensor)
{
    spellBook->strategy.MoveHead = false;
    spellBook->motion.HeadYaw = 0;
    spellBook->motion.HeadSpeedYaw = 0.2f;
    spellBook->motion.HeadSpeedPitch = 0.2f;

    if ((spellBook->strategy.GameState == STATE_READY || spellBook->strategy.GameState == STATE_PLAYING) && !onStart)
    {
        if (spellBook->perception.vision.localization.Enabled)
        {
            spellBook->strategy.WalkForward = true;
            spellBook->strategy.TargetX = -1.0f;
            spellBook->strategy.TargetY = 0.0f;
            spellBook->strategy.TargetTheta = 0;

            CartesianCoord current(spellBook->perception.vision.localization.X, spellBook->perception.vision.localization.Y);
            CartesianCoord desired(spellBook->strategy.TargetX, spellBook->strategy.TargetY);
            if (current.distance(desired) < 0.2f)
            {
                spellBook->strategy.WalkForward = false;
                onStart = true;
            }
        }
        else
        {
            onStart = true;
        }
    }
    if (spellBook->strategy.GameState == STATE_PLAYING && onStart)
    {
        if(spellBook->perception.vision.ball.BallDetected && para){ //viu a bola
            timeLow = 0;
            timeHigh = 0;
            timeLeft = 0;
            timeRight = 0;
            headLow = false;
            headHigh = false;
            headLeft = false;
            headRight = false;
            andou = 0;
            ballD = 0;
            
            if(!foundBall){
                SAY("I found the ball"); //fala que viu a bola
                foundBall = true;
            }

            float ballAngle = spellBook->perception.vision.ball.BallYaw; //captura a angulacao da bola

            if (ballAngle >= 1 || ballAngle <= -1) //verifica se o angulo em relacao a bola esta para esquerda ou direita e
            {
                if(ballAngle > 0)
                    spellBook->motion.Vth = Deg2Rad(2.0f);
                else
                    spellBook->motion.Vth = Deg2Rad(-2.0f);
            }

            else
                rodou = true;

            if(rodou){
                ballSpotted = true;
                spellBook->motion.Vth = Deg2Rad(0.0f); //depois de girar, coloca a velocidade do angular do robo para 0
            
            if(!dist){
                ballDistActual = spellBook->perception.vision.ball.BallDistance; //captura a distancia em relacao a bola e calcula quantas iteracoes sera
                dist = true;
            }

            else{
                ballDistPrevious = ballDistActual;
                ballDistActual = spellBook->perception.vision.ball.BallDistance; //captura a distancia em relacao a bola e calcula quantas iteracoes serao 
                ballDistanceDif = ballDistActual - ballDistPrevious;
                ballD = sqrt(pow(ballDistActual, 2) - pow(h, 2));

                if(ballDistanceDif > 0)
                    lookingForTheBall();

                if(ballD <= 0.3)
                {
                    dist = false;
                    ballSpotted = false;
                    para = false;
                    spellBook->motion.Vx = 0;
                    if(!ballHere){
                        SAY("The ball is here");
                        ballHere = true;
                    }  
                }
            }
        }
        }
        else if(ballSpotted){ //se a bola foi vista e ainda nao foram feitas todas as iteracoes calculadas
            if(andou < 200){
                spellBook->motion.Vx = 0.2; //define a velocidade do robo para 0.2 m/s
                andou++;
            }

            else if(andou >= 199)
               lookingForTheBall(); 
        }

        else{
            lookingForTheBall();
            foundBall = false;
            ballSpotted = false;
            ballHere = false;
            para = true;
            rodou = false;
        }

        
        // cout << "na role trainee1, " << endl;
        // spellBook->motion.Vth = Deg2Rad(0); // SETA A VELOCIDADE ANGULAR PARA 0 GRAUS
        // spellBook->motion.Vx = 0.2; // SETA A VELOCIDADE LINEAR PARA 0 m/s (NAO COLOQUE MAIS QUE 0.2m/s!!!)
        // spellBook->motion.HeadPitch = Deg2Rad(0.0f); // ANGULACAO DA CABECA DO ROBO, POSITIVO O ROBO OLHA PRA BAIXO, NEGATIVO PRA CIMA
        //  informacoes disponiveis:
        //  spellBook->perception.vision.ball.BallDetected // SE ESTA VENDO A BOLA
        //  spellBook->perception.vision.ball.BallDistance // DISTANCIA ATE A BOLA em metros
        //  spellBook->perception.vision.ball.BallYaw > Deg2Rad(10.0f) // ANGULACAO DA BOLA EM X
        //  spellBook->motion.HeadPitch = Deg2Rad(24.0f); // OLHA PRA BAIXO
    }
}
