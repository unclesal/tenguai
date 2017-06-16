// ********************************************************************************************************************
// *                                                                                                                  *
// *                         One button at component library toolbar, it can emit drag event.                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *             Кнопка на тулбаре библиотеки компонентов, которая может генерировать сигнал перетаскивания.          *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 12 jun 2017 at 16:13 *
// ********************************************************************************************************************

#include "LibraryTab_Button.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                    Конструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::LibraryTab_Button::LibraryTab_Button ( QIcon icon, QString hint ) 
    : QPushButton()
{
    __mouse_left_button_pressed = false;
    __dragging = false;
    __drag = QJsonObject();
    
    setFlat( true );
    setIcon( icon );
    setToolTip( hint );
    setFixedSize( QSize( 22, 22 ) );    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  Set drag object.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                              Установить таскаемый объект.                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::LibraryTab_Button::setDrag ( QJsonObject json ) {
    __drag = json;
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Mouse press event handler.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Обработчик события нажатия мыши.                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::LibraryTab_Button::mousePressEvent ( QMouseEvent * event ) {
    
    QAbstractButton::mousePressEvent ( event );
    
    if ( event->buttons() | Qt::LeftButton ) {
        __mouse_left_button_pressed = true;
        __mouse_pressed_position = event->pos();
    }
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Mouse move event handler.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Обработчик события перемещения мыши.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::LibraryTab_Button::mouseMoveEvent ( QMouseEvent* event ) {
    
    QAbstractButton::mouseMoveEvent ( event );
    
    if ( ( __mouse_left_button_pressed ) && ( ! __dragging ) ) {
        
        QPoint pos = event->pos() - __mouse_pressed_position;
        if ( pos.manhattanLength() > QApplication::startDragDistance() ) {
            
            // Start of dragging
            // Начало перетаскивания
            
            __dragging = true;
            QDrag * drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            
            QJsonDocument doc( __drag );
            mimeData->setData("application/json", doc.toJson() );
            
            drag->setMimeData(mimeData);
            
            QPixmap pm = icon().pixmap( QSize(16,16) );
            drag->setPixmap( pm );

            // Qt::DropAction dropAction = 
            drag->exec();
                        
            __dragging = false;            
            
        };
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Mouse release event handler.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Обработчик события отпускания мыши.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::LibraryTab_Button::mouseReleaseEvent ( QMouseEvent* event ) {
    
    QAbstractButton::mouseReleaseEvent ( event );
    
    if ( event->buttons() | Qt::LeftButton ) {
        __mouse_left_button_pressed = false;
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                Mouse leaves this widget.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Мышка покинула территорию виджита.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::LibraryTab_Button::leaveEvent ( QEvent* event ) {
    QWidget::leaveEvent ( event );
    update();
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The destructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Деструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::LibraryTab_Button::~LibraryTab_Button() {

}