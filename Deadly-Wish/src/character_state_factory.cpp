#include "character_state_factory.h"

CharacterStateFactory::CharacterStateFactory() 
{

}

CharacterStateFactory::~CharacterStateFactory()
{

}

CharacterState*
CharacterStateFactory::change_character_state(int next_state)
{
    switch(next_state) {
        case IDLE_STATE:
            return new IdleState();
            break;

        case MOVING_STATE:
            return new MovingState();
            break;

        case DEATH_STATE:
            return new DeathState();
            break;

        case HEAVY_ATTACK_STATE:
            return new HeavyAttackState();
            break;

        case LIGHT_ATTACK_STATE:
            return new LightAttackState();
            break;
            
        case DEFENSE_STATE:
            return new DefenseState();
            break;

        case SPECIAL_STATE:
            return new SpecialState();
            break;
            
        default:
            printf("error on character_state_factory!\n");
            return nullptr;
    }
}