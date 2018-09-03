#include "special_state.h"

SpecialState::SpecialState() 
    :CharacterState() {
    	
    m_current_state = SPECIAL_STATE;
    m_refresh_rate = 100;
}