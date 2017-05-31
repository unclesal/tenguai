// ********************************************************************************************************************
// *                                                                                                                  *
// *           The sprout from / to agent, the communication branch between agents using redis messages.              *
// *                                  In other hand this is a property of the agent.                                  *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                 Отросток из / в агента. Веточка для связи между агентами через сообщения редиса.                 *
// *                                  С другой стороны, он же и "свойство" агента.                                    *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 27 may 2017 at 08:02 *
// ********************************************************************************************************************

#pragma once

#include <QObject>
#include <QVariant>
#include "AbstractAgentKernel.h"

namespace tengu {
    
    class Sprout : public QObject {
        
        Q_OBJECT        
        Q_PROPERTY( QVariant value READ __getValue WRITE __setValue )
                    
        public:
            
            // The name should be unique in the parent (owner) namespace.
            // Имя лучше бы было уникальным в пределах родителя (владельца).
            
            Sprout( AbstractAgentKernel * owner, QString systemName );
            virtual ~Sprout();
            
            void setInputChannel( QString channel );
            void setOutputChannel( QString channel );
            
            void subscribe();
            void subscribed( QString channel );
            void unsubscribed( QString channel );
            virtual bool handleMessage( QString channel, QString message );
            
            QString systemName();
                        
        protected:
            
            bool _to_me( QString channel );
            
        private:
            
            QString __system_name;
            QVariant __value;
            
            bool __subscribed;
            bool __subscribtion_requested;
            
            AbstractAgentKernel * __owner;
            
            QString __inputChannel;
            QString __outputChannel;
            
            QVariant __getValue();
            void __setValue( QVariant value );            
            
        signals:
            
            void signalGotValue( QVariant value );
        
            
    };
    
};

