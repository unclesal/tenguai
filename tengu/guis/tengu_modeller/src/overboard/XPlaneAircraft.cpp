// ********************************************************************************************************************
// *                                                                                                                  *
// *                   The representation X-Plane simulator as the "agent" using XTengu plugin.                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *             Представление симулятора X-Plane в качестве агента с использованием плагина XTengu.                  *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 11 jun 2017 at 20:24 *
// ********************************************************************************************************************

#include "XPlaneAircraft.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                 The constructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                   Конструктор.                                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XPlaneAircraft::XPlaneAircraft( int acf_index ) 
    : tengu::Task()
{
    
    __aircraft_index = acf_index;
    
    QString sName= tr("acf_") + QString::number( acf_index );
    QString hName = tr("Aircraft ") + QString::number( acf_index );
    
    if ( acf_index == 0 ) {
        hName = tr("User Aircraft");
    };
    
    AbstractEntity::setSystemName( sName );
    AbstractEntity::setHumanName( hName );    
    AbstractEntity::setExecutionMode( AbstractEntity::EM_XPLANE );
    
    
    CREATE_XTENGU_SETTINGS;
    settings.beginGroup("CommonControl");
    __controlGroup = settings.value("ControlNameGroup", "xtengu.control").toString();
    __conditionGroup = settings.value("ConditionNameGroup", "xtengu.condition").toString();
    settings.endGroup();
    
    __init_sprout( "Longitude", Sprout::EXTERNAL_OUTPUT, tr("Longitude") );
    __init_sprout( "Latitude", Sprout::EXTERNAL_OUTPUT, tr("Latitude") );
    
    __init_sprout( "LeftAileron", Sprout::EXTERNAL_INPUT, tr("Left Aileron"), -45, 45 );
    __init_sprout( "RightAileron", Sprout::EXTERNAL_INPUT, tr("Right Aileron"), -45, 45 );
    
    // __init_sprout( "LeftAileron", Sprout::EXTERNAL_OUTPUT, tr("Left aileron") );
    /*
    __init_sprout( "LeftFlaperon", Sprout::EXTERNAL_OUTPUT, tr("Left flaperon") );
    __init_sprout( "LeftElevator", Sprout::EXTERNAL_OUTPUT, tr("Left elevator" ) );
    __init_sprout( "LeftRudder", Sprout::EXTERNAL_OUTPUT, tr("Left rudder" ) );    
    __init_sprout( "LeftBrake", Sprout::EXTERNAL_OUTPUT, tr("Left brake" ) );
    
    __init_sprout( "RightAileron", Sprout::EXTERNAL_OUTPUT, tr("Right aileron" ) );
    __init_sprout( "RightFlaperon", Sprout::EXTERNAL_OUTPUT, tr("Right flaperon" ) );
    __init_sprout( "RightElevator", Sprout::EXTERNAL_OUTPUT, tr("Right elevator" ) );
    __init_sprout( "RightRudder", Sprout::EXTERNAL_OUTPUT, tr("Right rudder" ) );
    __init_sprout( "RightBrake", Sprout::EXTERNAL_OUTPUT, tr("Right brake" ) );
    */
    
    // this->connect();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                               Translation one section of settings to set of sprouts.                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                            Перевод одной секции установок в некое множество "ростков".                           *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XPlaneAircraft::__init_sprout ( QString settingsGroup, tengu::Sprout::sprout_type_t type, QString name, float min, float max ) {
    
    
    CREATE_XTENGU_SETTINGS;
    
    settings.beginGroup( settingsGroup );
    QString input = settings.value("input_channel", "").toString();
    QString output = settings.value("output_channel", "").toString(); 
    settings.endGroup();
    
    QString inputPath = __conditionGroup + ".acf_" + QString::number( __aircraft_index ) + "." + input;
    QString outputPath = __controlGroup + ".acf_" + QString::number( __aircraft_index ) + "." + output;
    
    SproutProxy * sp = new SproutProxy( this );
    sp->setExecutionMode( AbstractAgent::EM_XPLANE );
        
    // The whitespace can be replaced to "_" in this procedurer
    // Пробел будет заменен на "_" в данной процедуре.
            
    sp->setHumanName( name );
    sp->setSproutType( type );
        
    // Crossing. Because output for sprout is an input for X-Plane.
    // Переворот, потому что выход для "ростка" - это вход для X-Plane.
        
    if ( type == Sprout::EXTERNAL_INPUT )  {
        sp->setSignalName( outputPath ); 
        sp->setSystemName( output );
        if ( min >= MINIMUM_CONSTRAINT ) sp->setMinimalValue( min );
        if ( max <= MAXIMUM_CONSTRAINT ) sp->setMaximalValue( max );
    } else {
        sp->setSignalName( inputPath );
        sp->setSystemName( input );
    }
    
    addSprout( sp );
            
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                            Overrided setting name method to avoid change predefined name.                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                  Перекрытый метод установки имени, чтобы избежать изменения предопределенного имени.             *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XPlaneAircraft::setName ( QString name ) {
    qDebug() << "XPlaneAircraft::setName() does not have any effect";
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                            Overrided setting execution mode method to avoid it's change.                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                   Перекрытый метод установки режима выполнения, чтобы избежать его изменение.                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XPlaneAircraft::setExecutionMode ( tengu::AbstractEntity::execution_mode_t mode ) {
    qDebug() << "XPlaneAircraft::setExecutioMode() does not have any effect";
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      Overrided connect function ( the stub ).                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                     Перекрытая функция соединения (заглушка).                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XPlaneAircraft::connect() {
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                   Overrided disconnect function ( the stub ).                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                    Перекрытая функция рассоединения (заглушка).                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XPlaneAircraft::disconnect() {
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The destructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Деструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XPlaneAircraft::~XPlaneAircraft() {
}