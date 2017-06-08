// ********************************************************************************************************************
// *                                                                                                                  *
// *                                     The right part of main window (properties area).                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Правая часть главного окна (зона свойств).                                *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 01 jun 2017 at 09:13 *
// ********************************************************************************************************************

#include "MainWindowRight.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::MainWindowRight::MainWindowRight(QWidget * parent)
    : QWidget( parent )
{
    QVBoxLayout * lay = new QVBoxLayout();
    lay->setMargin( 1 );
    lay->setSpacing( 1 );
    this->setLayout( lay );
    __splitter = new QSplitter( Qt::Vertical );
    __splitter->setHandleWidth( SPLITTERS_HANDLE_WIDTH );
    __splitter->setLineWidth( SPLITTERS_LINE_WIDTH );
    lay->addWidget( __splitter );
    __properties = new AgentPropertyView();
    __splitter->addWidget( __properties );
    
    // for temporary use only
    // просто для времянки
    
    __down = new QWidget();
    __splitter->addWidget( __down );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                   Get component's heights for save in the settings.                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                 Получить высОты компонентов для записи в установках.                             *
// *                                                                                                                  *
// ********************************************************************************************************************

QPair<int, int> tengu::MainWindowRight::getComponentsHeights() {
    QPair<int, int> result;
    result.first = __properties->size().height();
    result.second = __down->size().height();
    return result;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                               Set component's heights after restore main window settings.                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                      Установить высОты компонентов после восстановления установок главного окна.                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindowRight::setComponentsHeight( QList<int> h ) {
    __splitter->setSizes( h );
}


// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Set MVC-model for property editing window.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                              Установка MVC-модели для окна редактирования свойств.                               *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::MainWindowRight::setPropertiesDataModel( AgentPropertyModel * model ) {
    __properties->setModel( model );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The destructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Деструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::MainWindowRight::~MainWindowRight() {
}