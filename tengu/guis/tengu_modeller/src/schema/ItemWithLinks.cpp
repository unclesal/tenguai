// ********************************************************************************************************************
// *                                                                                                                  *
// *                                     An item which can be linked with another items.                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                Элемент, который может иметь связь с другими элементами.                          *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 22 jun 2017 at 10:33 *
// ********************************************************************************************************************

#include "ItemWithLinks.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The constructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ItemWithLinks::ItemWithLinks ( tengu::AbstractEntity * entity, QGraphicsItem* parent ) 
    : AbstractEntityItem ( entity, parent )
{
    __linksOutgoingFromThis = QMap< QString, LinkItem * >();
    __linksIncommingToThis = QMap< QString, LinkItem * >();    
    
    _iAmSprout = false;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Add a link which is outgoing from this item.                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   Добавить связь, исходящую из данного элемента.                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ItemWithLinks::addOutgoingLink ( tengu::LinkItem* link ) {
    __linksOutgoingFromThis[ link->getUUID() ] = link;
    QObject::connect( link, SIGNAL(signalLinkRemoved(QString)), this, SLOT(removeLink(QString)) );
    link->__setFrom( this, _iAmSprout );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Add a link which is incomming to this item                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Добавить связь, входящую в этот элемент.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ItemWithLinks::addIncommingLink ( tengu::LinkItem * link ) {
    __linksIncommingToThis[ link->getUUID() ] = link;
    QObject::connect( link, SIGNAL(signalLinkRemoved(QString)), this, SLOT(removeLink(QString)) );
    link->__setTo( this, _iAmSprout );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  Remove the link                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                  Удаление связи.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ItemWithLinks::removeLink ( tengu::LinkItem * link ) {
    removeLink( link->getUUID() );    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Remove the link by it's uuid (slot)                                       *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                     Удаление связи по ее идентификатору (слот).                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ItemWithLinks::removeLink ( QString uuid ) {
    
    if ( __linksIncommingToThis.contains( uuid ) ) {
        QObject::disconnect( __linksIncommingToThis[uuid], SIGNAL(signalLinkRemoved(QString)), this, SLOT( removeLink( QString) ) );
        __linksIncommingToThis.remove( uuid );
    }
    
    if ( __linksOutgoingFromThis.contains( uuid ) ) {
        QObject::disconnect( __linksOutgoingFromThis[uuid], SIGNAL(signalLinkRemoved(QString)), this, SLOT(removeLink(QString)) );
        __linksOutgoingFromThis.remove( uuid );
    }
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Get all links of this item.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Вернуть все связи данного элемента.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

QList< tengu::LinkItem* > tengu::ItemWithLinks::hisLinks() {
    
    QList< LinkItem * > result;
    
    foreach( LinkItem * item, __linksIncommingToThis ) {
        result.append( item );
    };
    
    foreach( LinkItem * item, __linksOutgoingFromThis ) {
        result.append( item );
    };
    
    return result;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The destructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Деструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ItemWithLinks::~ItemWithLinks() {

}

