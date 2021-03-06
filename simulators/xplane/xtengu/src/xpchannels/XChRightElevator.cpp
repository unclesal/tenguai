// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Class for control right elevator's array.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                              Класс для управления отклонением правого руля высоты (массивом).                    *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 10 may 2017 at 12:15 *
// ********************************************************************************************************************

#include "XChRightElevator.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                     The constructor.                                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Конструктор.                                               *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XChRightElevator::XChRightElevator() 
    : XChFloatArrayTwice ( "RightElevator" ,"" , -60 , 60 ) 
{
    _dataref_1 = XPlaneChannel::find_dataref( "sim/flightmodel/controls/elv1_def" );
    _dataref_2 = XPlaneChannel::find_dataref( "sim/flightmodel/controls/elv2_def" );
    
    // For the begin initialization. We want the channel to be usable().
    // Для начальной инициализации. Мы хотим, чтобы канал был usable();
    _dataref = _dataref_1;
        
    // Indexes for left elevator. The minus sign due to the configuration, we want the negative values to deflect the aileron down.
    // Индексы для левого руля высоты. Знак минуса - из-за конфигурации, мы хотим, чтобы отрицательные значения отклоняли элерон вниз.
    
    _template_1[ 17 ] = -1;        
    _template_2[ 13 ] = -1;
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The desctructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Деструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XChRightElevator::~XChRightElevator() {

}

