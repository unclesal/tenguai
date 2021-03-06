// ********************************************************************************************************************
// *                                                                                                                  *
// *     Graphics representation of Sprout class (signal/slot mechanism, inter-agent redis-based communications).     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *          Графическое представление класса Sprout ("росток' - механизм сигналов-слотов, межагентное общение,      *
// *                                                  основанное на redis'е.                                          *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 10 jun 2017 at 12:20 *
// ********************************************************************************************************************

#pragma once

#include "ItemWithLinks.h"
#include "Sprout.h"
#include "AgentPropertyElement.h"
#include "Constants.h"

namespace tengu {
    
    class SproutItem : public ItemWithLinks {
        
        Q_OBJECT
        
        Q_PROPERTY( Sprout::sprout_type_t sprout_type READ getSproutType WRITE setSproutType );
        Q_PROPERTY( Sprout::sprout_orientation_t orientation READ getOrientation WRITE setOrientation );
        Q_PROPERTY( QString signal_name READ getSignalName WRITE setSignalName );
        Q_PROPERTY( float minimal_value READ getMinimalValue WRITE setMinimalValue );
        Q_PROPERTY( float maximal_value READ getMaximalValue WRITE setMaximalValue );
        
        public:
                        
            SproutItem ( Sprout * sprout = nullptr, QGraphicsItem * parent = nullptr );
            virtual ~SproutItem();
            
            void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR);
            
            QList< QList<AgentPropertyElement> > properties();
            
            void checkEntity();
            
            void setSproutType( Sprout::sprout_type_t type );
            Sprout::sprout_type_t getSproutType();
            
            Sprout * sprout();
            
            bool isOrphan();
            
            /**
             * @short Get the orientation of this element at the diagram.
             * 
             * The "Sprout" can be rotated on the chart to make it more convenient and readable.
             * 
             * "Росточек" может вращаться на диаграмме, чтобы было удобнее и читабельнее.
             */
            
            Sprout::sprout_orientation_t getOrientation();
            void setOrientation( Sprout::sprout_orientation_t orientation );
            
            QString getSignalName();
            void setSignalName( QString name );
            
            void recalculate();
            
            float getMinimalValue();
            void setMinimalValue( float min );
            float getMaximalValue();
            void setMaximalValue( float max );
            
            /**
             * @short Manual signal name selection.
             */
            
            bool manualSignalNameSelection;                        
            
        private:
            
            QTransform __transform();
            
            int __width;
            int __height;
    };
    
};

