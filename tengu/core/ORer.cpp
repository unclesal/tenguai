// ********************************************************************************************************************
// *                                                                                                                  *
// *                        The agent which will waiting at least one of his sprout after activity.                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *              Агент, который будет ждать хотя бы одного из своих входов ("веток") после активизации.              *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 09 jun 2017 at 09:46 *
// ********************************************************************************************************************

#include "ORer.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                The constructor.                                                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                   Конструктор.                                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ORer::ORer () 
    : AbstractAgent () 
{
    _className = "ORer";
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The destructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Деструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ORer::~ORer() {

}

