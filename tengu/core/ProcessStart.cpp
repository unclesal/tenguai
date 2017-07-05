// ********************************************************************************************************************
// *                                                                                                                  *
// *                       The start point for process. There should be only one within the process.                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                          Точка старта процесса. Должна быть только одна в пределах процесса.                     *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 09 jun 2017 at 10:39 *
// ********************************************************************************************************************

#include "ProcessStart.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The constructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ProcessStart::ProcessStart () 
    : AbstractAgentKernel ()
{
    // Start element is always in mode EM_ALWAYS
    // Старт всегда в режиме EM_ALWAYS
    
    setExecutionMode( EM_ALWAYS );
    _className = "ProcessStart";
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                            Conversion from object to JSON                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Преобразование из объекта в JSON.                                      *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
QJsonObject tengu::ProcessStart::toJSON() {
    
    QJsonObject o = tengu::AbstractEntity::toJSON();
    o["class_name"] = "ProcessStart";
    
    // There is no collection name because the start/stop object are not written to the database
    // Здесь нет имени коллекции, потому что старт/стоп объекты в базу - не записываются.
    
    return o;
    
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                            Conversion from JSON to object.                                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Преобразование из JSONа в объект.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
bool tengu::ProcessStart::fromJSON ( QJsonObject json ) {
    
    if ( hasClass( json, "ProcessStart" ) ) {
        tengu::AbstractEntity::fromJSON ( json );
        return true;
    };
    
    return false;
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The destructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Деструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ProcessStart::~ProcessStart() {

}
