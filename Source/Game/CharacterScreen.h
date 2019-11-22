#pragma once

#include "Screen.h"

namespace Core
{
class CharacterScreen : public Screen
{
    URHO3D_OBJECT( CharacterScreen, Screen );
public:
    //! Constructor.
    CharacterScreen( Context* context );

    //! Deconstructor.
    ~CharacterScreen();
protected:
    //! Initialize Scene.
    virtual void Init();
private:
    //! Create Scene.
    void CreateScene();

    //! Setup Viewport.
    void SetupViewport();

    //! Build Window.
    void BuildWindow();
};
}