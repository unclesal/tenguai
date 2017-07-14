// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Graphical representation of entire workspace                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   Графическое представление рабочего пространства целиком.                       *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 05 jul 2017 at 12:16 *
// ********************************************************************************************************************

#include "WorkSpaceItem.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                      The constructor.                                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                         Конструктор.                                             *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::WorkSpaceItem::WorkSpaceItem ( tengu::AbstractEntity* entity, QGraphicsItem* parent ) 
    : AbstractEntityItem ( entity, parent ) 
{
    _class_name = "WorkSpaceItem";
    _entity_type = ET_WorkspaceItem;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                      The destructor.                                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                         Деструктор.                                              *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::WorkSpaceItem::~WorkSpaceItem() {

}

