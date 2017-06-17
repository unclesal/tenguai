// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Process start graphics representation.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                    Графическое представление начала процесса.                                    *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 16 jun 2017 at 12:53 *
// ********************************************************************************************************************

#include "ProcessStartItem.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                 The constructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                   Конструктор.                                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ProcessStartItem::ProcessStartItem ( tengu::ProcessStart * entity, QGraphicsItem* parent ) 
    : AbstractEntityItem ( entity, parent )
{
    _boundingRect = QRect( 0, 0, 76, 76 );    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Painting of this object.                                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                 Отрисовка объекта.                                               *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::ProcessStartItem::paint ( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget ) {
    
    QPixmap pixmap( _boundingRect.width(), _boundingRect.height() );
    QPainter pixPainter( & pixmap );
    pixPainter.eraseRect( _boundingRect );
    
    int shadowSize = 8;
    
    // The shadow
    // Тенька
    
    QColor shadowColor = _processDiagram_shadowColor();
    QPen shadowPen( shadowColor );
    QBrush shadowBrush( shadowColor );
    pixPainter.setBrush( shadowBrush );
    pixPainter.setPen( shadowPen );
    pixPainter.drawEllipse( shadowSize, shadowSize, _boundingRect.width() - shadowSize - 1, _boundingRect.height()-shadowSize-1 );
    
    // Start process item element body.
    // Тело элемента "начало процесса".
    
    QPen borderPen = _processDiagram_borderPen();
    pixPainter.setPen( borderPen );
    
    int radius = qRound( ( _boundingRect.width() - shadowSize ) / 2.0 );    
    QPoint center( radius, radius );
    QPoint focal( radius-shadowSize, radius-shadowSize );
    
    QRadialGradient gradient( center, radius - 1, focal );
    gradient.setColorAt(0, _processDiagram_brightFillColor() );
    gradient.setColorAt(1, _processDiagram_darkFillColor() );
    QBrush brush = QBrush( gradient );    
    pixPainter.setBrush( brush );
    pixPainter.drawEllipse( 1, 1, _boundingRect.width() - shadowSize, _boundingRect.height() - shadowSize );
    
    painter->drawPixmap( 0, 0, pixmap );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The destructor.                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                    Деструктор.                                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::ProcessStartItem::~ProcessStartItem() {

}
