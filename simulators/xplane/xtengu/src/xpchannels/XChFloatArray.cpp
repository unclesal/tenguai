// ********************************************************************************************************************
// *                                                                                                                  *
// *                                 An array. Reading and setting for array-based X-Plane values.                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                        Массив. Чтение и управление каналов X-Plane, основанных на массиве данных.                *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 08 may 2017 at 16:51 *
// ********************************************************************************************************************

#include "XChFloatArray.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The constructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XChFloatArray::XChFloatArray ( QString aName, QString path, int aMinValue, int aMaxValue ) 
    : XPlaneChannel ( aName, path, aMinValue, aMaxValue ) 
    , _templateArray( QList<int>() )
{
        for ( int i=0; i<XPLANE_SURFACES_COUNT; i++ ) {
        _templateArray.append( 0 );
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                               Set integer value - just call setting of float value.                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *               Установка целочисленного значения - просто устанавливаем значение с плавающей запятой.             *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XChFloatArray::set ( int value ) {
    this->set( (float) value );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                Setting of floating value                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Установка значения с плавающей запятой.                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::XChFloatArray::set ( float value ) {
    
    if ( ( _dataref ) && ( _templateArray.count() > 0 ) ) {
        
        float aValue = applyRestrictions( value );
        float * fArray = new float[ _templateArray.count() ];
        memset( fArray, 0, _templateArray.count() * sizeof( float ) );
        
        // Reading array values from X-Plane
        // Читаем значение массива из X-Plane
        
        XPLMGetDatavf( _dataref, fArray, 0, _templateArray.count() );
        for ( int i=0; i<_templateArray.count(); i++ ) {
            if ( _templateArray.at(i) ) {
                fArray[i] = _templateArray.at(i) * aValue ;
            };
        };
        XPLMSetDatavf( _dataref, fArray, 0, _templateArray.count() );
        
        delete( fArray );
    };
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The desctructor                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XChFloatArray::~XChFloatArray() {
}

