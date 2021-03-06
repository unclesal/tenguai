// ********************************************************************************************************************
// *                                                                                                                  *
// *                                An "entity" class, common parent for agents and sprouts.                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                        Класс "сущности", общий предок для агентов и ростков (связей агентов)                     *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 11 jun 2017 at 12:34 *
// ********************************************************************************************************************

#pragma once

#include <QObject>
#include <QMap>
#include <QString>
#include <QUuid>
#include <QJsonObject>
#include <QDateTime>

// #include "AbstractStorageableEntity.h"

#include "MongoIndex.h"
#include "Constants.h"

namespace tengu {
    
    class AbstractEntity {
        
        // For debug purposes, must be deleted later
        // Для отладки, потом надо удалить.
        
        friend class AgentFactory;
        friend class AgentItemFactory;
                
        public:
            
            // The execution mode for the model, processor, task e.t.c
            // Режим выполнения данной модели, процесса, задачи и др.
        
            enum execution_mode_t {
                EM_ALWAYS       = 0,
                EM_REAL         = 1,
                EM_XPLANE       = 2
                
                // Not realized yet.
                // EM_PREPAR3D     = 3
                
            };
            
            // Entity types. To avoid checking every time through dynamic_cast only
            // Типы сущностей. Чтобы не делать каждый раз dynamic_cast.
            
            enum entity_types_t {
                
                ET_Unknown, 
                
                // Entities itself
                // Собственно "сущности".
                
                ET_ANDor,
                ET_ORer,
                ET_Sprout,
                ET_Task,
                ET_Process,
                ET_ProcessStart,
                ET_ProcessStop,
                ET_SimpleRegulator,
                ET_Vehicle,
                ET_Workspace,
                
                // Graphics items
                // Графические элементы.
                
                ET_ANDorItem,
                ET_ORerItem,
                ET_SproutItem,
                ET_TaskItem,
                ET_ProcessItem,
                ET_ProcessStartItem,
                ET_ProcessStopItem,
                ET_SimpleRegulatorItem,
                ET_VehicleItem,
                ET_WorkspaceItem,
                
                // Tree-like representation
                // Древовидное представление.
                
                ET_TaskTreeItem,
                ET_ProcessTreeItem,
                ET_ProcessStartTreeItem,
                ET_ProcessStopTreeItem,
                ET_ANDorTreeItem,
                ET_ORerTreeItem,
                ET_VehicleTreeItem,
                ET_WorkspaceTreeItem
            };                        
            
            
            AbstractEntity ();
            virtual ~AbstractEntity();
            
            // true, really unique identifier for this object
            // Действительно уникальный идентификатор для данного объекта.
            
            virtual QString getUUID();
            virtual void setUUID( QString uuid );
            
            // The name of this agent.
            // Имя агента.
            
            virtual QString getSystemName();
            virtual void setSystemName( QString name );
            
            virtual QString getHumanName();
            virtual void setHumanName( QString name );
            
            // The comment of this entity.
            // Комментарий данной "сущности".
            
            virtual QString getComment();
            virtual void setComment( QString comment );
            
            // The execution mode of this entity (real, x-plane simulation, always e.t.c.)
            // Режим выполнения данной сущности (реальный, симуляция в X-Plane, всегда и др).
            
            virtual execution_mode_t getExecutionMode();
            virtual void setExecutionMode( execution_mode_t mode );
            
            // Has been this entity changed?
            // Была ли данная сущность изменена?
            
            virtual bool hasChanged();
            
            // Return last modified datetime (in the UTC) of this object.
            // Вернуть последнее время модификации (в UTC) данного объекта.
            
            virtual QDateTime lastModified();
            virtual void unmodify();
            
            // Convert this object to JSON form.
            // Преобразование данного объекта в формат JSON.
            
            virtual QJsonObject toJSON();
            
            // Back conversion, from JSON to object. All field will be replaced.
            // Обратное преобразование, из JSONа в объект. Все поля будут изменены.
            
            virtual bool fromJSON( QJsonObject json );
            
            // Indexes for mongo collection of this class.
            // Иднексы для монговой коллекции этого класса.
            
            virtual QMap<QString, tengu::MongoIndex> indexes();
            
            virtual bool hasClass( QJsonObject json, QString class_name );
            virtual entity_types_t entityType();
            
            int getX();
            void setX( int x );
            
            int getY();
            void setY( int y );
            
            void silent( bool s );
            bool silent();

            
        protected:
            
            bool _changed;            
            
            QString _class_name;
            entity_types_t _entity_type;
            
            void _somethingChanged();
            
            bool _silent;
                                    
        private:
            
            // Entity name
            // Имя сущности
            
            QString __system_name;
            
            QString __human_name;
            
            // Any human readable comment for this entity.
            // Любой человеко-ориентированный комментарий для сущности.
            
            QString __comment;
            
            // Unique (in entire system range) identifier of this agent.
            // Уникальный (в пределах вообще всей системы) идентификатор данного агента.
            
            QString __uuid;
            
            // Execution mode
            // Режим выполнения.
            
            execution_mode_t __execution_mode;
            
            // The UTC datetime of last modification
            // Всемирная дата-время последнего изменения.
            
            QDateTime __lastModified;
            
            int __x;
            int __y;
                        
            
    };
};

