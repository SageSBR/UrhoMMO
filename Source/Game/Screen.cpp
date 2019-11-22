#include "PrecompiledHeader.h"
#include "Screen.h"

namespace Core
{
void Screen::Init()
{
    //Create the Scene
    scene = new Scene( context_ );
}

void Screen::Run()
{
    scene->SetUpdateEnabled( true );
}

void Screen::Pause()
{
    scene->SetUpdateEnabled( false );
}

void Screen::Dispose()
{
    //Pause the scene and remove everything from it
    if( scene )
    {
        scene->SetUpdateEnabled( false );
        scene->Clear();
        scene->Remove();
    }

    USERINTERFACE->GetRoot()->RemoveAllChildren();
}
}