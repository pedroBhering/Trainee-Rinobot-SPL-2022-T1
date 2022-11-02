#include "TraineeRole1.h"
#include "Core/Utils/Math.h"
#include "Core/Utils/RelativeCoord.h"
#include "Core/Utils/RobotDefs.h"
#include "Core/Utils/CartesianCoord.h"

TraineeRole1::TraineeRole1(SpellBook *spellBook) : Role(spellBook)
{
    timeH = 0;
    timeLow = 0;
    timeFound = 0;
    timeSp = 0;
    timeSay = 0;
    spinL = false;
    spinR = false;
    spinB = false;
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

    onStart = false;
}
TraineeRole1::~TraineeRole1()
{
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
        if(spellBook->perception.vision.ball.BallDetected && !ballSpotted){
            spellBook->motion.Vx = 0;

            while(timePitch < 5)
            {
                timePitch++;
                spellBook->motion.HeadPitch = Deg2Rad(-angle);
            }

            if(!foundBall){
                SAY("I found the ball");
                foundBall = true;
            }
            ballSpotted = true;
            float ballAngle = spellBook->perception.vision.ball.BallYaw;
            while (ballAngle > 0.01 || ballAngle < -0.01)
            {
                if(ballAngle > 0)
                    spellBook->motion.Vth = Deg2Rad(0.1f);
                else
                    spellBook->motion.Vth = Deg2Rad(-0.1f);
            }
            spellBook->motion.Vth = Deg2Rad(0.0f);
            timeBall = (spellBook->perception.vision.ball.BallDistance / 0.2)*0.02;
        }
        else if(ballSpotted && time < timeBall){
            spellBook->motion.Vx = 0.2;
            time++;
            if(spellBook->perception.vision.ball.BallDistance <= 0.01)
            {
                spellBook->motion.Vx = 0;
                if(!ballHere){
                    SAY("The ball is here");
                    ballHere = true;
                }
            }
        }

        else{
            spellBook->motion.Vx = 0;
            foundBall = false;
            ballSpotted = false;
            ballHere = false;
            time = 0;
        }

        
        cout << "na role trainee1, " << endl;
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
