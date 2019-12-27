#include "PrecompiledHeader.h"
#include "Character.h"

#undef new

#include <Bullet/btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <Bullet/BulletDynamics/Character/btKinematicCharacterController.h>

namespace Core
{
Character::Character( Context* context ) :
    Entity( context ),
    connection( nullptr )
{
    height = 1.51f;
    diameter = 0.56f;
}

Character::~Character()
{
}

void Character::FixedUpdate( float time )
{
    if( connection )
    {
        const Controls& controls = connection->GetControls();

        if( GetSubsystem<Network>()->IsServerRunning() )
        {
            Quaternion rotation;
            Vector3 moveDirection = Vector3::ZERO;

            auto transform = GetComponent<SmoothedTransform>();

            //Smoothed Transform not found
            if( !transform )
                return;

            //Character is walking?
            if( controls.buttons_ & CHARACTERCONTROL_Forward )
            {
                moveDirection += Vector3::FORWARD;
                moveDirection = node_->GetWorldRotation() * moveDirection;
                rotation = Quaternion( 0.0f, controls.yaw_, 0.0f );
                transform->SetTargetRotation( rotation );
            }

            //Move Direction is valid?
            if( moveDirection.LengthSquared() > 0.0f )
            {
                //It's in a ground?
                if( bulletController->onGround() )
                    bulletController->setWalkDirection( ToBtVector3( moveDirection * time * 5.f ) );
                else
                    bulletController->setWalkDirection( ToBtVector3( moveDirection * time * 5.f ) );
            }
            else
                bulletController->setWalkDirection( btVector3( 0, 0, 0 ) );

            //Get World Transform
            btTransform worldTransform;
            worldTransform = bulletController->getGhostObject()->getWorldTransform();

            //Set World Position
            Vector3 newPosition = ToVector3( worldTransform.getOrigin() ) + Vector3::DOWN * height * 0.5f;
            node_->SetWorldPosition( newPosition );
        }
        /*else
        {
            node_->SetRotation( connection->GetRotation() );
            node_->SetPosition( connection->GetPosition() );
        }*/
    }
}
};