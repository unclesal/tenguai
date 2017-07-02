// ********************************************************************************************************************
// *                                                                                                                  *
// *           The sprout from / to agent, the communication branch between agents using redis messages.              *
// *                                  In other hand this is a property of the agent.                                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                 Отросток из / в агента. Веточка для связи между агентами через сообщения редиса.                 *
// *                                  С другой стороны, он же и "свойство" агента.                                    *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 27 may 2017 at 08:38 *
// ********************************************************************************************************************

#include "Sprout.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                The constructor.                                                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                  Конструктор.                                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::Sprout::Sprout( AbstractAgentKernel * owner )
    : QObject(), AbstractEntity()
{
    __owner = owner;
    __subscribed = false;
    __subscribtion_requested = false;
    // __inputChannel = QString("");
    // __outputChannel = QString("");
    __signalName = QString("");
    __sprout_type = IN_PROCESS_INPUT;
    
    // Default constraints is 0 ... 100
    // Ограничение значения по умолчанию - 0 ... 100
    
    __minimal_value = 0.0;
    __maximal_value = 100.0;
    
    _className = "Sprout";
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Add input redis channel.                                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Добавить канал редиса по входу.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
void tengu::Sprout::setInputChannel( QString channel ) {
    if ( ! channel.isEmpty() ) {
        __inputChannel = channel;
    };
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Add output redis channel.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Добавить выходной канал редиса.                                        *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
void tengu::Sprout::setOutputChannel( QString channel ) {
    if ( ! channel.isEmpty() ) {
        __outputChannel = channel ;
        _changed = true;
    };
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                            Get sprout's signal direction.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Получить направление сигнала "ростка".                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::Sprout::sprout_type_t tengu::Sprout::getSproutType() {
    return __sprout_type;
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Set sprout's signal direction.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Установить направление сигнала "ростка".                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::setSproutType ( tengu::Sprout::sprout_type_t type ) {
    __sprout_type = type;
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  Get signal name                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                Получить имя сигнала.                                             *
// *                                                                                                                  *
// ********************************************************************************************************************

QString tengu::Sprout::getSignalName() {
    return __signalName;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                Set signal name                                                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                             Установить имя сигнала.                                              *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::setSignalName ( QString signal ) {
    __signalName = signal;
    _somethingChanged();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                 Get minimal allowed value for this sprout.                                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                        Получить минимально допустимое значение данного "росточка".                               *
// *                                                                                                                  *
// ********************************************************************************************************************

float tengu::Sprout::getMinimalValue() {
    return __minimal_value;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Set minimal allowed value for this sprout                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                           Установить минимально допустимое значение данного "росточка".                          *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::setMinimalValue ( float min ) {
    __minimal_value = min;
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Get maximal allowed value for this sprout.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                         Получить максимально допустимое значение для данного "росточка"                          *
// *                                                                                                                  *
// ********************************************************************************************************************

float tengu::Sprout::getMaximalValue() {
    return __maximal_value;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                   Set maximum allowed value for this sprout.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                             Установить максимально допустимое значение данного росточка.                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::setMaximalValue ( float max ) {
    __maximal_value = max;
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                        Get the value of object (procedure for providing property behaviour)                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                  Получить значение объекта (процедура для обеспечения поведения как "свойства")                  *
// *                                                                                                                  *
// ********************************************************************************************************************

QVariant tengu::Sprout::getValue() {    
    return __value;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                    Set the value of this object (for property, but also can be use directly)                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *    Установить значение для данного объекта. Вообще-то для свойства, но может быть использовано и напрямую.       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::setValue( QVariant val ) {
    
    __value = val;
    
    // This is not the component changes. _changed is not need.
    // Это - не изменение компонента как такового. _changed не нужно.
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    The possibility to subscribe for this sprout.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                  Возможность для данного объекта подписаться.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::subscribe() {

    if ( 
        ( ! __subscribed ) 
        // && ( ! __subscribtion_requested )
        && ( ! __signalName.isEmpty() )
        && ( __sprout_type == EXTERNAL_INPUT )
        && ( __owner != nullptr )
        && ( __owner->_sub_redis ) 
        && ( __owner->__sub_redis_connected )
    ) {
        __owner->_sub_redis->subscribe( __signalName );
        __subscribtion_requested = true;
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                              Get the sprout's owner (the agent, the task usually).                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                               Получить владельца sprout'а (агента, обычно - задачу ).                            *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractAgentKernel* tengu::Sprout::owner() {
    return __owner;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Somewhat has been subscribed.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          что-то было реально подписано.                                          *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::subscribed( QString channel ) {
    if (
        ( ! __subscribed )
        && ( __sprout_type == EXTERNAL_INPUT )
        && ( ! __signalName.isEmpty() )
        && ( __signalName == channel ) 
    ) {
        __subscribed = true;
    }
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Unsubscribe from RedisIO messages.                                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                Отписаться от событий редиса.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::unsubscribe() {
        
    if ( ( __owner ) 
        && ( __subscribed )
        && ( __owner->_sub_redis ) 
        && ( ! __signalName.isEmpty() ) 
    ) {
        
        __owner->_sub_redis->unsubscribe( __signalName );
        
        // One sprout can be subscribed to only one redis.io signal. Wait until really unsubscribed.
        // Один sprout может быть подписан только на один сигнал redis'а. Ждем, пока реально не отпишется.
        
        int cycles = 10000;
        
        while ( (cycles > 0 ) && ( __subscribed ) ) {
            LoRedis::processEvents();
            usleep( 1 );
            cycles --;
        };
        
        // If something goes wrong...
        // Если что-то пошло не так...
        
        if ( __subscribed ) {
            __subscribed = false;
            __subscribtion_requested = false;
        };        
        
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Somewhat has been unsubscribed.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                               Что-то отписалось.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::Sprout::unsubscribed( QString channel ) {

    qDebug() << "Sprout::unsubscribed: " << channel;
    if ( _to_me( channel ) ) {
        __subscribed = false;
        __subscribtion_requested = false;
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Was this message addressed to me?                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                    Было ли данное сообщение адресовано мне?                                      *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Sprout::_to_me( QString channel ) {

    return ( ( ! __signalName.isEmpty() ) && ( channel == __signalName ) );
        
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Handle the message from redis.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Обработать сообщение из редиса.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Sprout::handleMessage( QString channel, QString value ) {

    if ( _to_me( channel ) ) {
        qDebug() << "Sprout::handleMesssage, value=" << value;
        __value.setValue( value );
        emit signalGotValue( __value );
        return true;
    };
    return false;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Have this sprout any input type?                                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                    Является ли данный отросток входным сигналом?                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Sprout::isInput() {
    return ( ( __sprout_type == Sprout::EXTERNAL_INPUT ) || ( __sprout_type == Sprout::IN_PROCESS_INPUT ) );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Have this sprout any output type?                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                 Является ли данный отросток выходным сигналом?                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Sprout::isOutput() {
    return ( ( __sprout_type == Sprout::EXTERNAL_OUTPUT ) || ( __sprout_type == Sprout::IN_PROCESS_OUTPUT ) );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Have this sprout external type?                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          У данного sprout'а - внешний тип?                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Sprout::isExternal() {
    return ( ( __sprout_type == Sprout::EXTERNAL_INPUT ) || ( __sprout_type == Sprout::EXTERNAL_OUTPUT ) );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Have this sprout internal type?                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         У данного спраута - внутренний тип?                                      *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::Sprout::isInternal() {
    return( ( __sprout_type == Sprout::IN_PROCESS_INPUT ) || ( __sprout_type == Sprout::IN_PROCESS_OUTPUT ) );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Return name of this sprout.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                             Вернуть имя данного "ростка"                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

/*
QString tengu::Sprout::systemName() {
    return __system_name;
}
*/

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The destructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                    Деструктор.                                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::Sprout::~Sprout() {
}

