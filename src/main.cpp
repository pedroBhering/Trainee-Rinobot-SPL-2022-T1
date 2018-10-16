#include <iostream>
#include <unistd.h>
#include "Core/InitManager.h"
#include "Core/ModulesManager.h"
#include "Modules/Motion/MotionModule.h"
#include "Modules/Strategy/StrategyModule.h"
#include "Modules/Remote/RemoteModule.h"
#include "Modules/Perception/PerceptionModule.h"
#include "Modules/Behaviour/BehaviourModule.h"

using namespace std;

int main(int argc,char *argv[])
{
    InitManager::Init(argc, argv);

    ModulesManager manager;
    SpellBook spellBook;
    spellBook.Load("/home/nao/data/config.json");
        
    if(spellBook.modules.LoadPerception)
        manager.Attach(new PerceptionModule(&spellBook));
    if(spellBook.modules.LoadMotion)
        manager.Attach(new MotionModule(&spellBook));
    if(spellBook.modules.LoadStrategy)
        manager.Attach(new StrategyModule(&spellBook));
    if(spellBook.modules.LoadRemote)
        manager.Attach(new RemoteModule(&spellBook));
    if(spellBook.modules.LoadBehaviour)
        manager.Attach(new BehaviourModule(&spellBook));
    
    manager.Run();

    InitManager::Destroy();

    return 0;
}