// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        The dialog with sprout's properties.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Диалог со свойствами "отростка".                                       *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 23 jun 2017 at 13:55 *
// ********************************************************************************************************************

#include "DialogPropertiesSprout.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The constructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Конструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::DialogPropertiesSprout::DialogPropertiesSprout( WorkSpace * workSpace ) 
    : DialogProperties( workSpace )
{
    __sproutItem = nullptr;
    __oldSproutItem = new SproutItem();
    __oldSproutItem->checkEntity();
    
    setWindowTitle( tr("Sprout's properties") );
    setWindowIcon( QIcon(QPixmap( ":button_navigation_16.png" )) );
    setMinimumSize( 600, 360 );
    
    __create_editor_widgets();
    
    QVBoxLayout * lay = new QVBoxLayout();
    lay->setMargin( 0 );
    lay->setSpacing( 0 );
    _centerWidget->setLayout( lay );

    // --------------------------------------------------------------------------------------------
    //                               Top widget, slider or indicator
    //                            Верхний виджит, слайдер или индикатор.
    // --------------------------------------------------------------------------------------------
    
    QWidget * topWidget = new QWidget();
    topWidget->setFixedHeight( 70 );
    lay->addWidget( topWidget );
    QHBoxLayout * topLayout = new QHBoxLayout();
    topLayout->setMargin( 5 );
    topLayout->setSpacing( 5 );
    topWidget->setLayout( topLayout );
    
    // Widget for output sprout (slider and minimum/maximum settings)
    // Виджит для выходного отростка (слайдер и установка минимума-максимума).
    
    QWidget * topic = new QWidget();
    topLayout->addWidget( topic );
    
    QHBoxLayout * topicLayout = new QHBoxLayout();
    topicLayout->setMargin( 2 );
    topicLayout->setSpacing( 2 );
    topic->setLayout( topicLayout );
        
    topicLayout->addWidget( __minimum_editor_widget, Qt::AlignLeft | Qt::AlignVCenter );
    
    // Widget with slider
    // Виджит со слайдером.
    
    __slider_widget = new QWidget();
    __slider_widget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    topicLayout->addWidget( __slider_widget, Qt::AlignCenter );
    
    QVBoxLayout * sliderLayout = new QVBoxLayout();
    sliderLayout->setMargin(0);
    sliderLayout->setSpacing(0);
    sliderLayout->setAlignment( Qt::AlignCenter );
    __slider_widget->setLayout( sliderLayout );
    
    // Widget with centered output current value label
    // Виджит с отцентрированной надписью о текущем выходном значении.
    
    QWidget * oclWidget = new QWidget();
    QHBoxLayout * oclLayout = new QHBoxLayout();
    oclLayout->setMargin( 0 );
    oclLayout->setSpacing( 0 );
    oclLayout->setAlignment( Qt::AlignCenter );
    oclWidget->setLayout( oclLayout );
    
    __output_current_value_label = new QLabel( tr("Current value: 0.00") );
    QFont output_current_value_label__font( "Arial", 12 );
    output_current_value_label__font.setBold( true );
    __output_current_value_label->setFont( output_current_value_label__font );
    oclLayout->addWidget( __output_current_value_label );
    
    sliderLayout->addWidget( oclWidget );
        
    __output_slider = new QSlider();
    QObject::connect( __output_slider, SIGNAL( valueChanged(int) ), this, SLOT( __on__slider_value_changed( int ) ) );
    __output_slider->setOrientation( Qt::Horizontal );
    __output_slider->setTickPosition( QSlider::TicksBothSides );
    sliderLayout->addWidget( __output_slider, Qt::AlignCenter );
    
    // widget with LCD-indicator.
    // виджит с LCD индикатором.
    
    __lcd_widget = new QWidget();
    __lcd_widget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );        
    topicLayout->addWidget( __lcd_widget, Qt::AlignCenter );
    
    QVBoxLayout * lcdLayout = new QVBoxLayout();
    lcdLayout->setMargin( 0 );
    lcdLayout->setSpacing( 0 );
    lcdLayout->setAlignment( Qt::AlignCenter );
    __lcd_widget->setLayout( lcdLayout );
    
    __lcd = new QLCDNumber();
    __lcd->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    __lcd->setDigitCount( 10 );
    __lcd->setDecMode();
    __lcd->setSmallDecimalPoint( false );
    __lcd->display( LCD_NONE );
    
    lcdLayout->addWidget( __lcd );
    
    // Add maximum value editor widget
    // Добавление виджита с редактором максимального значения.
    
    topicLayout->addWidget( __maximum_editor_widget, Qt::AlignRight | Qt::AlignVCenter );        
        
    
    // --------------------------------------------------------------------------------------------
    //                                        Properties widget
    //                                       Виджит со свойствами.
    // --------------------------------------------------------------------------------------------
    
    QWidget * propWidget = new QWidget();
    propWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    lay->addWidget( propWidget );
    
    QVBoxLayout * propLay = new QVBoxLayout();
    propLay->setMargin( 0 );
    propLay->setSpacing( 0 );
    propWidget->setLayout( propLay );
        
    // Widget to define type of sprout
    // Виджит для определения типа sprout'а
    
    QWidget * wType = new QWidget();
    propLay->addWidget( wType );
    
    QHBoxLayout * layoutType = new QHBoxLayout();
    layoutType->setMargin( 5 );
    layoutType->setSpacing( 5 );
    layoutType->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );    
    wType->setLayout( layoutType );
    
    // Sprout's execution mode
    // Режим выполнения sprout'а
    
    QLabel * lblExecutionMode = new QLabel( tr("Execution mode:") );
    lblExecutionMode->setMargin( 0 );
    layoutType->addWidget( lblExecutionMode );
    
    __combo_box__execution_mode = new QComboBox();
    QObject::connect( __combo_box__execution_mode, SIGNAL( activated( int ) ), this, SLOT( __on__combo_box__execution_mode__activated( int ) ) );
    __combo_box__execution_mode->addItem( QIcon( QPixmap(":attach_32.png") ), tr("Always"), AbstractAgent::EM_ALWAYS );
    __combo_box__execution_mode->addItem( QIcon( QPixmap(":cog_32.png")), tr("Real"), AbstractAgent::EM_REAL );
    __combo_box__execution_mode->addItem( QIcon( QPixmap(":xplane10_32.png")), tr("X-Plane"), AbstractAgent::EM_XPLANE );
    layoutType->addWidget( __combo_box__execution_mode );
    
    // Settings the sprout's type 
    // Установка типа Sprout'а
    
    QLabel * lblType = new QLabel( tr("Signal type:") );
    lblType->setMargin( 0 );
    layoutType->addWidget( lblType );
            
    __combo_box__type = new QComboBox();
    QObject::connect( __combo_box__type, SIGNAL( activated(int) ), this, SLOT( __on__combo_box_type_activated( int ) ) );
    __combo_box__type->addItem( tr("In-process Input"), Sprout::SPT__IN_PROCESS_INPUT );
    __combo_box__type->addItem( tr("External Input"), Sprout::SPT__EXTERNAL_INPUT );
    __combo_box__type->addItem( tr("In-process Output"), Sprout::SPT__IN_PROCESS_OUTPUT );
    __combo_box__type->addItem( tr("External Output"), Sprout::SPT__EXTERNAL_OUTPUT );
    layoutType->addWidget( __combo_box__type );
    
    // Manual setting signal name
    // Ручная установка имени сигнала.
        
    QWidget * widgetSignal = new QWidget();
    propLay->addWidget( widgetSignal );
    QHBoxLayout * layoutSignal = new QHBoxLayout();
    layoutSignal->setMargin( 5 );
    layoutSignal->setSpacing( 5 );
    layoutSignal->setAlignment( Qt::AlignLeft | Qt::AlignVCenter );
    widgetSignal->setLayout( layoutSignal );
    
    __check_box__manual = new QCheckBox( tr("Set signal name manually:") );
    QObject::connect( __check_box__manual, SIGNAL(stateChanged(int)), this, SLOT( __on__manual_signal_selection_state_changed( int ) ) );
    layoutSignal->addWidget( __check_box__manual );
    
    __manual_signal_name = new QLineEdit();
    __manual_signal_name->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    layoutSignal->addWidget( __manual_signal_name );
        
    // Widget for selection sprout's signal name
    // Виджит для выбора сигнала sprout'а.
    
    QWidget * selectorWidget = new QWidget();    
    selectorWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    propLay->addWidget( selectorWidget );
    QGridLayout * selectorLayout = new QGridLayout();
    selectorLayout->setMargin( 5 );
    selectorLayout->setSpacing( 5 );
    selectorWidget->setLayout( selectorLayout );
    
    // Labels for processes / tasks / sprout selection
    // Метки для выбора процессов / задач / отростков.
    
    QLabel * labelForVehicles = new QLabel( tr("Processors:") );
    selectorLayout->addWidget( labelForVehicles, 0, 0 );    
    QLabel * labelForProcess = new QLabel( tr("Process:") );
    selectorLayout->addWidget( labelForProcess, 0, 1 );
    QLabel * labelForTask = new QLabel( tr("Task:") );
    selectorLayout->addWidget( labelForTask, 0, 2 );
    QLabel * labelForSprout = new QLabel( tr("Sprout:") );
    selectorLayout->addWidget( labelForSprout, 0, 3 );
    
    // Filters for processes / tasks / sprouts
    // Фильтры для процессов / задач / отростков.
    
    __filter_processors = new QLineEdit();
    QObject::connect( __filter_processors, SIGNAL( textChanged( const QString & ) ), this, SLOT( __on__filter_processors_text_changed( const QString & ) ) );
    selectorLayout->addWidget( __filter_processors, 1, 0 );
    
    __filter_processes = new QLineEdit();
    QObject::connect( __filter_processes, SIGNAL(textChanged( const QString & )), this, SLOT( __on__filter_processes_text_changed( const QString & ) ) );    
    selectorLayout->addWidget( __filter_processes, 1 , 1 );
    
    __filter_tasks = new QLineEdit();
    QObject::connect( __filter_tasks, SIGNAL( textChanged( const QString & ) ), this, SLOT( __on__filter_tasks_text_changed( const QString & ) ) );
    selectorLayout->addWidget( __filter_tasks, 1, 2 );
    
    __filter_sprouts = new QLineEdit();
    QObject::connect( __filter_sprouts, SIGNAL( textChanged( const QString & )), this, SLOT( __on__filter_sprouts_text_changed( const QString & ) ) );
    selectorLayout->addWidget( __filter_sprouts, 1, 3 );
    
    // Tables for processes / tasks / sprouts
    // Таблицы для процессов / задач / отростков.
    
    __table_processors = new QTableWidget();
    QObject::connect( __table_processors->selectionModel(), SIGNAL( selectionChanged ( const QItemSelection &, const QItemSelection & ) ),
        this, SLOT( __on__table_processors_item_selected( const QItemSelection &, const QItemSelection & ) ) );
    __init_table( __table_processors );
    selectorLayout->addWidget( __table_processors, 2, 0 );
    
    __table_processes = new QTableWidget();
    QObject::connect( __table_processes->selectionModel(), SIGNAL( selectionChanged( const QItemSelection & , const QItemSelection & ) ), 
        this, SLOT( __on__table_processes_item_selected( const QItemSelection &, const QItemSelection & ) ) 
    );    
    __init_table( __table_processes );
    selectorLayout->addWidget( __table_processes, 2, 1 );
    
    __table_tasks = new QTableWidget();
    QObject::connect( __table_tasks->selectionModel(), SIGNAL( selectionChanged( const QItemSelection &, const QItemSelection & ) ),
        this, SLOT( __on__table_tasks_item_selected( const QItemSelection &, const QItemSelection & ) )
    );
    __init_table( __table_tasks );
    selectorLayout->addWidget( __table_tasks, 2, 2 );
    
    __table_sprouts = new QTableWidget();
    QObject::connect( __table_sprouts->selectionModel(), SIGNAL( selectionChanged( const QItemSelection &, const QItemSelection & ) ),
        this, SLOT( __on__table_sprouts_item_selected( const QItemSelection &, const QItemSelection & ) ) 
    );
    __init_table( __table_sprouts );
    selectorLayout->addWidget( __table_sprouts, 2, 3 );
        
    __do_not_handle_events = true;
    __setManualSelection( false );
    __setAsTypeInput( true );
    __do_not_handle_events = false;
    
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Initialize one table widget                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Инициализация одного табличного виджита.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__init_table ( QTableWidget* table ) {
    
    table->setMinimumWidth( 80 );
    table->setMinimumHeight( 60 );
    table->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    table->setColumnCount(1);
    
    QFont font("Arial", 10 );
    table->setFont( font );
    
    QHeaderView * verticalHeader = table->verticalHeader();
    verticalHeader->setSectionResizeMode( QHeaderView::Fixed );
    verticalHeader->setDefaultSectionSize( 20 );
    verticalHeader->hide();
    
    QHeaderView * horizontalHeader = table->horizontalHeader();
    horizontalHeader->setSectionResizeMode( QHeaderView::Stretch );
    horizontalHeader->hide();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *             Create minimum and maximum editors widget, they used for input and output simultaneously.            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *  Создание виджитов с редакторами минимума и максимума. Они используются одновременно и для входа, и для выхода.  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__create_editor_widgets() {
    
    // Left widget with editor: label and the editor itself.
    // Левый виджит с редактором: метка (надпись) и сам редактор.
    
    __minimum_editor_widget = new QWidget();
    __minimum_editor_widget->setMaximumWidth( 80 );
    QVBoxLayout * leftEditorLayout = new QVBoxLayout();
    leftEditorLayout->setMargin( 0 );
    leftEditorLayout->setSpacing( 0 );
    __minimum_editor_widget->setLayout( leftEditorLayout );
    
    QLabel * labelMinimum = new QLabel( tr("Minimum:") );
    leftEditorLayout->addWidget( labelMinimum );
    
    __editor_minimum = new QLineEdit();
    QObject::connect( __editor_minimum, SIGNAL( textChanged( const QString & )), this, SLOT( __on__minimum_editor_text_changed( const QString & ) ) );
    __editor_minimum->setMaximumWidth( 60 );
    leftEditorLayout->addWidget( __editor_minimum );
        
    // Right widget with editor: label and maximum value editor.
    // Правый виджит с редактором: надпись и редактор максимального значения.
    
    __maximum_editor_widget = new QWidget();    
    __maximum_editor_widget->setMaximumWidth( 80 );
    __maximum_editor_widget->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    
    QVBoxLayout * rightEditorLayout = new QVBoxLayout();
    rightEditorLayout->setMargin( 0 );
    rightEditorLayout->setSpacing( 0 );    
    __maximum_editor_widget->setLayout( rightEditorLayout );
    
    // The "maximum" label shifted right.
    // Надпись "Максимум", сдвинутая вправо.
    QWidget * rlWidget = new QWidget();
    QHBoxLayout * rlLayout = new QHBoxLayout();
    rlLayout->setMargin(0);
    rlLayout->setSpacing(0);
    rlLayout->setAlignment( Qt::AlignRight );
    rlWidget->setLayout( rlLayout );
    
    QLabel * labelMaximum = new QLabel( tr("Maximum:") );
    rlLayout->addWidget( labelMaximum );
    rightEditorLayout->addWidget( rlWidget, Qt::AlignRight );
    
    __editor_maximum = new QLineEdit();
    QObject::connect( __editor_maximum, SIGNAL( textChanged( const QString & ) ), this, SLOT( __on__maximum_editor_text_changed( const QString & ) ) );
    __editor_maximum->setMaximumWidth( 60 );
    QWidget * reWidget = new QWidget();
    QHBoxLayout * reLayout = new QHBoxLayout();
    reWidget->setLayout( reLayout );
    reLayout->setMargin(0);
    reLayout->setSpacing(0);
    reLayout->setAlignment( Qt::AlignRight );
    reLayout->addWidget( __editor_maximum );
    rightEditorLayout->addWidget( reWidget );                
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                Dialog appearance                                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                Появление диалога.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::showEvent ( QShowEvent* event ) {
    QDialog::showEvent ( event );
    __stopListen();    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Stop listen sprout's receiving.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Остановка прослушивания sprout'а.                                       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__stopListen() {
    
    __lcd->display( LCD_NONE );
    
    if ( ( __sproutItem != nullptr ) && ( __sproutItem->sprout() != nullptr ) && ( __sproutItem->sprout()->isInput() ) ) {
        __sproutItem->sprout()->unsubscribe();
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                             Store sprout properties to have restoring possibility later.                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                     Сохранить параметры sprout'а, чтобы иметь потом возможность восстановить их.                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__storeOldSproutParams() {
    
    __oldSproutItem->sprout()->setExecutionMode( __sproutItem->sprout()->getExecutionMode() );
    __oldSproutItem->sprout()->setSproutType( __sproutItem->sprout()->getSproutType() );
    __oldSproutItem->sprout()->setSignalName( __sproutItem->sprout()->getSignalName() );
    
    __oldSproutItem->sprout()->setMinimalValue( __sproutItem->sprout()->getMinimalValue() );
    __oldSproutItem->sprout()->setMaximalValue( __sproutItem->sprout()->getMaximalValue() );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Cancelled. Restore old sprout params.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                  Отменили. Восстанавливаем старые параметры sprout'а.                            *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__restoreOldSproutParams() {

    __stopListen();
    
    __sproutItem->sprout()->setExecutionMode( __oldSproutItem->sprout()->getExecutionMode() );
    __sproutItem->sprout()->setSproutType( __oldSproutItem->sprout()->getSproutType() );
    __sproutItem->sprout()->setSignalName( __oldSproutItem->sprout()->getSignalName() );
    
    __sproutItem->sprout()->setMinimalValue( __oldSproutItem->sprout()->getMinimalValue() );
    __sproutItem->sprout()->setMaximalValue( __oldSproutItem->sprout()->getMaximalValue() );
    
    if ( __sproutItem->sprout()->isInput() )  __sproutItem->sprout()->subscribe();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   Cancel operation.                                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                  Операции при отмене.                                            *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::_on__cancel() {
    
    QObject::disconnect( __sproutItem->sprout(), SIGNAL( signalGotValue( QVariant ) ), this, SLOT( __on__got_value( QVariant ) ) );
    __restoreOldSproutParams();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                       Set slider's min / max / current position according to sprout's values.                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *         Установить минимальную / максимальную / текущую позицию слайдера согласно значениям в sprout'е.          *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__setSlider() {
    if ( ( __sproutItem ) && ( __sproutItem->sprout() ) ) {
        float min = __sproutItem->sprout()->getMinimalValue();
        float max = __sproutItem->sprout()->getMaximalValue();
        bool unlimited = ( ( min == MINIMUM_CONSTRAINT ) || ( max == MAXIMUM_CONSTRAINT ) );
        __output_slider->setMinimum( min );
        __output_slider->setMaximum( max );
        float val = __sproutItem->sprout()->getValue().toFloat();
        if ( ( val <= min ) && ( val > max ) ) val = ( max - min ) / 2.0;  
        
        __do_not_handle_events = true;
        __output_slider->setValue( val );
        __do_not_handle_events = false;
        
        if ( unlimited ) __output_slider->setTickPosition( QSlider::NoTicks );
        else __output_slider->setTickPosition( QSlider::TicksBothSides );
        
        __output_current_value_label->setText( QString::number( val ) );
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                            Show current min and max constraints in the editor's fields.                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                      Отобразить текуюие минимальное и максимальное значение в полях редакторов.                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__showMinMaxValues() {
    
    float min = __sproutItem->getMinimalValue();
    float max = __sproutItem->getMaximalValue();
    
    if ( min > MINIMUM_CONSTRAINT ) __editor_minimum->setText( QString::number( min ) );
    else __editor_minimum->setText("");
    
    if ( max < MAXIMUM_CONSTRAINT ) __editor_maximum->setText( QString::number( max ) );
    else __editor_maximum->setText("");
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                            Fill dialog's fields from sprout.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Заполнение полей диалога из "отростка".                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::fillFrom( tengu::AbstractEntityItem * item ) {
        
    __stopListen();
    
    SproutItem * sproutItem = dynamic_cast< SproutItem * > ( item );
    if ( sproutItem ) {
        
        __sproutItem = sproutItem;        
        __storeOldSproutParams();
        __sproutItem->checkEntity();
                
        QObject::connect( __sproutItem->sprout(), SIGNAL( signalGotValue( QVariant ) ), this, SLOT( __on__got_value( QVariant ) ) );
                
        // Change widget's looking
        // Изменение внешнего вида виджита.
        
        // Set sprout type.
        // Установить тип спраута.
        int index = __combo_box__type->findData( (int) __sproutItem->getSproutType() );
        if ( index > 0 ) __combo_box__type->setCurrentIndex( index );
                
        __do_not_handle_events = true;
                
        __check_box__manual->setChecked( __sproutItem->manualSignalNameSelection );
        __setManualSelection( sproutItem->manualSignalNameSelection );
        __setSlider();
        __showMinMaxValues();
        
        __do_not_handle_events = false;
        
    };
    
    __fill_processors_list();
    
    // __fill_processes_list();    
    // __fill_tasks_list();
    // __fill_sprouts_list();
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                     Fill processes table according it's filter                                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                            Заполнить таблицу процессов согласно установленному фильтру                           *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__fill_processes_list() {
    
    _clearTable( __table_tasks );
    _clearTable( __table_sprouts );
    _clearTable( __table_processes );
    
    __stopListen();
    
    Processor * processor = __selectedAgent< Processor * > ( __table_processors );
    if ( processor ) {
        __fill_one_table< Process * >( processor , __table_processes, __filter_processes );
    
        // If we have rows in the table - select either first row or early selected.
        // Если есть строки в таблице - выберем либо первую, либо ранее выбранную.
    
        if ( __table_processes->rowCount() > 0 ) {
            
            QTableWidgetItem * first = __table_processes->itemAt( 0, 0 );
        
            if ( first ) {            
                __do_not_handle_events = true;
                first->setSelected( true );
                __fill_tasks_list();
                __do_not_handle_events = false;
            };
            
        };
        
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Fill processors table according it's filter                                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   Заполнить таблицу процессоров согласно фильтру.                                *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__fill_processors_list() {
    
    _clearTable( __table_processors );
    _clearTable( __table_processes );
    _clearTable( __table_tasks );
    _clearTable( __table_sprouts );
    
    __stopListen();
    
    __fill_one_table< Processor * > ( _workSpace, __table_processors, __filter_processors );
    
    // If we have rows in processor's table - select either first or early selected.
    // Если есть строки в таблице процессоров - выбираем либо первую, либо ранее выбранную.
    
    if ( __table_processors->rowCount() > 0 ) {
        QTableWidgetItem * first = __table_processors->itemAt( 0, 0 );
        if ( first ) {
            __do_not_handle_events = true;
            first->setSelected( true );
            __fill_processes_list();
            __do_not_handle_events = false;
        };
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                         Fill sprout's list according selected task and sprout's filter.                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                     Заполнить список sprout'ов согласно выбранной задаче и фильтру sprout'ов.                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__fill_sprouts_list() {
        
    _clearTable( __table_sprouts );
    __stopListen();
    
    // Define selected task
    // Определение выбранной задачи.
    
    Task * selectedTask = __selectedAgent< Task * > ( __table_tasks );
    
    if ( selectedTask ) {
                
        QList < Sprout * > suitableSprouts = selectedTask->sutiableSproutsFor( __sproutItem->sprout() );
        
        if ( suitableSprouts.count() > 0 ) {
            
            for ( int i=0; i<suitableSprouts.count(); i++ ) {
                Sprout * sprout = suitableSprouts.at(i);
                __table_sprouts->setRowCount( i+1 );
                QTableWidgetItem * item = new QTableWidgetItem();
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                item->setData( Qt::UserRole, QVariant::fromValue< Sprout * >( sprout ) );
                item->setText( sprout->getHumanName() );
                __table_sprouts->setItem( i, 0, item );
            };
        };
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                            Fill tasks list according selected process and task's filter                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                      Заполнить список задач согласно выбранному процессу и фильтру для задач.                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__fill_tasks_list() {
    
    // Define process selected in the process table
    // Определяем процесс, выбранный в таблице процессов.
        
    Process * selectedProcess = __selectedAgent < Process * > ( __table_processes );
    
    _clearTable( __table_tasks );
    _clearTable( __table_sprouts );
    
    if ( selectedProcess ) {
        
        __fill_one_table< Task * >( selectedProcess, __table_tasks, __filter_tasks );   
        
        // Now select - either the first element or early selected.
        // Выбираем - первый элемент, либо ранее выбранный
        
        QTableWidgetItem * first = __table_tasks->itemAt( 0, 0 );
        if ( first ) {
            __do_not_handle_events = true;
            first->setSelected( true );
            __fill_sprouts_list();        
            __do_not_handle_events = false;
        };
        
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                   Get process which was selected in process'es table.                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                               Получить процесс, который был выбран в таблице процессов.                          *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
tengu::Process * tengu::DialogPropertiesSprout::__selectedProcess() {
    
    Process * selectedProcess = nullptr;
    
    if ( __table_processes->selectedItems().count() > 0 ) {
        QTableWidgetItem * selectedItem = __table_processes->selectedItems().at(0);
        if ( selectedItem ) {
            selectedProcess = qvariant_cast< Process * >( selectedItem->data( Qt::UserRole ) );
        };
    };
    
    return selectedProcess;
    
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                            Get processor which was selected in the processor's table.                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                          Получить процессор, который был выбран в таблице процессоров.                           *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
tengu::Processor * tengu::DialogPropertiesSprout::__selectedProcessor() {
    
    Processor * selectedProcessor = nullptr;
    if ( __table_processors->selectedItems().count() > 0 ) {
        QTableWidgetItem * selectedItem = __table_processors->selectedItems().at(0);
        if ( selectedItem ) {
            selectedProcessor = qvariant_cast< Processor * > ( selectedItem->data( Qt::UserRole) );
        };
    }
    return selectedProcessor;
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Get the task which was selected in task's table.                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                  Получить задачу, которая была выбрана в таблице задач.                          *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
tengu::Task* tengu::DialogPropertiesSprout::__selectedTask() {
    
    Task * selectedTask = nullptr;
    
    if ( __table_tasks->selectedItems().count() > 0 ) {
        QTableWidgetItem * selectedItem = __table_tasks->selectedItems().at(0);
        if ( selectedItem ) {
            selectedTask = qvariant_cast< Task * >( selectedItem->data( Qt::UserRole ) );
        };
    };
    
    return selectedTask;
    
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                              Get the sprout which was selected in the sprout's table.                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                             Получить "росточек", который был выбран в таблице "ростков".                         *
// *                                                                                                                  *
// ********************************************************************************************************************
/*
tengu::Sprout* tengu::DialogPropertiesSprout::__selectedSprout() {
    
    Sprout * selectedSprout = nullptr;
    
    if ( __table_sprouts->selectedItems().count() > 0 ) {
        QTableWidgetItem * selectedItem = __table_sprouts->selectedItems().at(0);
        if ( selectedItem ) {
            selectedSprout = qvariant_cast< Sprout * > ( selectedItem->data( Qt::UserRole ) );
        };
    };
    
    return selectedSprout;
}
*/
// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Set manual selection of sprout's signal name.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                               Установка ручного способа выбора имени сигнала sprout'а.                           *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__setManualSelection ( bool manual ) {
    
    __manual_signal_name->setEnabled( manual );
    
    __filter_processors->setEnabled( ! manual );
    __filter_processes->setEnabled( ! manual );
    __filter_tasks->setEnabled( ! manual );
    __filter_sprouts    ->setEnabled( ! manual );
    
    __table_processors->setEnabled( ! manual );
    __table_processes->setEnabled( ! manual );
    __table_tasks->setEnabled( ! manual );
    __table_sprouts->setEnabled( ! manual );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                   Select input or output looking for widget's topic.                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   Установить входной или выходной вид топика виджита.                            *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__setAsTypeInput ( bool isInput ) {
    __slider_widget->setVisible( ! isInput );
    __lcd_widget->setVisible( isInput );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                   Slot: change the state of manual check box selection                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                             Слот: изменение нажатости крыжика "ручной выбор имени сигнала"                       *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__manual_signal_selection_state_changed ( int state ) {
    
    Q_UNUSED( state );
    
    if ( __do_not_handle_events ) return;
    __stopListen();
    __setManualSelection( __check_box__manual->isChecked() );
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      Changing text in process filter editor.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                   Изменение текста в редакторе фильтра процессов.                                *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__filter_processes_text_changed ( const QString & text ) {
    
    Q_UNUSED( text );
    
    if ( __do_not_handle_events ) return;
    __stopListen();
    __fill_processes_list();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Changing the text in processors filter editor.                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Изменение текста в фильтре процессоров.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__filter_processors_text_changed ( const QString & text ) {
    
    Q_UNUSED( text );
    
    if ( __do_not_handle_events ) return;
    __stopListen();
    __fill_processors_list();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Item was selected in processes table.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        В таблице процессов был выбран элемент.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__table_processes_item_selected ( const QItemSelection & selected, const QItemSelection & deselected ) {
    
    Q_UNUSED( selected );
    Q_UNUSED( deselected );
    
    if ( __do_not_handle_events ) return;        
    __stopListen();    
    __fill_tasks_list();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                  The item was selected in the processor's table.                                 *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                    В таблице процессоров был выделен элемент.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__table_processors_item_selected ( const QItemSelection& selected, const QItemSelection& deselected ) {
    Q_UNUSED( selected );
    Q_UNUSED( deselected );
    
    if ( __do_not_handle_events ) return;    
    __stopListen();
    __fill_processes_list();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Item was selected in the task's table.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         В таблице задач был выделен элемент.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__table_tasks_item_selected ( const QItemSelection& selected, const QItemSelection& deselected ) {
    
    Q_UNUSED( selected );
    Q_UNUSED( deselected );
        
    if ( __do_not_handle_events ) return;
    __stopListen();
    __fill_sprouts_list();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      Item was selected in the sprout's table                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                     В таблице "росточков" был выделен элемент.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__table_sprouts_item_selected ( const QItemSelection& selected, const QItemSelection& deselected ) {
    
    Q_UNUSED( selected );
    Q_UNUSED( deselected );
    
    if ( __do_not_handle_events ) return;
    
    __stopListen();
    
    Processor * selectedProcessor = __selectedAgent < Processor * > ( __table_processors );
    Process * selectedProcess = __selectedAgent <Process * > ( __table_processes );
    Task * selectedTask = __selectedAgent < Task * > ( __table_tasks );
    Sprout * selectedSprout = __selectedAgent < Sprout * > ( __table_sprouts );
        
    if ( ( selectedProcessor != 0 ) && ( selectedProcess != 0 ) && ( selectedTask != 0 ) &&  ( selectedSprout != 0 ) ) {
        
        SproutProxy * proxy = dynamic_cast< SproutProxy * >( selectedSprout );
        QString signalName;
        
        if ( proxy ) {
            
            // For the proxy just use his signal.
            // Для прокси просто используем его сигнал.
            
            signalName = selectedSprout->getSignalName();
            
            __sproutItem->setMinimalValue( selectedSprout->getMinimalValue() );
            __sproutItem->setMaximalValue( selectedSprout->getMaximalValue() );
            
            __showMinMaxValues();
                        
        } else {
            
            // For a non-proxy, a "real" sprout, we use process name - a dot - task name - a dot - sprout name.
            // Для не-проксевых, "реальных" росточков, используем имя процесса - точка - имя задачи - точка - имя ростка.
            
            signalName = selectedProcess->getSystemName() + "." + selectedTask->getSystemName() + "." + selectedSprout->getSystemName();            
        };  
        
        if ( ! signalName.isEmpty() ) {
            
            __sproutItem->setSignalName( signalName );
            if ( __sproutItem->sprout()->isInput() ) {
                __sproutItem->sprout()->subscribe();
            };
        };
            
    };
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Changing text in tasks filter editor.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                    Изменение текста в редакторе фильтра задач.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__filter_tasks_text_changed ( const QString & text ) {
    
    Q_UNUSED( text );
    
    if ( __do_not_handle_events ) return;
    __fill_tasks_list();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                      Changing the text in sprout's filter editor.                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Изменение текста в редакторе фильтра ростков.                               *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__filter_sprouts_text_changed ( const QString & text ) {
    
    Q_UNUSED( text );
    
    if ( __do_not_handle_events ) return;
    __fill_sprouts_list();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Change text in minimum value editor .                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                 Изменение текста в редакторе минимального значения.                              *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__minimum_editor_text_changed ( const QString & text ) {
    
    if ( __do_not_handle_events ) return;
    
    if ( text.isEmpty() ) {
        __sproutItem->sprout()->setMinimalValue( MINIMUM_CONSTRAINT );
    } else {
        bool ok = false;
        float val = text.toFloat( & ok );
        if ( ok ) {
            __sproutItem->sprout()->setMinimalValue( val );
            __setSlider();
        };
    };
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Change text in maximum value editor.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                Изменение текста в редакторе максимального значения.                              *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__maximum_editor_text_changed ( const QString & text ) {
    if ( __do_not_handle_events ) return;
    
    if ( text.isEmpty() ) {
        __sproutItem->sprout()->setMaximalValue( MAXIMUM_CONSTRAINT );
    } else {
        bool ok = false;
        float val = text.toFloat( & ok );
        if ( ok ) {
            __sproutItem->sprout()->setMaximalValue( val );
            __setSlider();
        };
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                     Sprout's type combo-box change it's value.                                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                 Комбо-бокс типа sprout'а изменил свое значение.                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__combo_box_type_activated ( int index ) {

    if ( __do_not_handle_events ) return;
    
    __stopListen();
    __sproutItem->setSproutType( ( Sprout::sprout_type_t ) index );
        
    switch ( index ) {
        
        case Sprout::SPT__IN_PROCESS_INPUT: {
            __setAsTypeInput( true );
        }; break;
        
        case Sprout::SPT__EXTERNAL_INPUT: {
            __setAsTypeInput( true );
        }; break;
        
        case Sprout::SPT__IN_PROCESS_OUTPUT: {
            __setAsTypeInput( false );
        }; break;
        
        case Sprout::SPT__EXTERNAL_OUTPUT: {
            __setAsTypeInput( false );
        }; break;
    };    
    
    __fill_sprouts_list();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Change value of execution mode combo-box.                                     *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                               Изменение значения combo-box'а режима выполнения.                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__combo_box__execution_mode__activated ( int index ) {
    
    if ( __do_not_handle_events ) return;
    
    __sproutItem->setExecutionMode( (AbstractAgent::execution_mode_t) index );
    __fill_sprouts_list();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Slot: got value from sprout.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Слот: со sprout'а было получено значение.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__got_value ( QVariant value ) {
    bool ok = false;
    float fVal = value.toFloat( & ok );
    if ( ok ) {
        __lcd->display( fVal );
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Output slider's value has been changed.                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                         Значение выходного слайдера было изменено.                               *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::DialogPropertiesSprout::__on__slider_value_changed ( int value ) {
    
    if ( ( __sproutItem ) && ( __sproutItem->sprout() ) && ( __sproutItem->sprout()->isOutput() ) ) {
        __output_current_value_label->setText( QString::number( value ) );
        __sproutItem->sprout()->setValue( value );
    };
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The destructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Деструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::DialogPropertiesSprout::~DialogPropertiesSprout() {
    delete( __oldSproutItem->sprout() );
    delete( __oldSproutItem );
}

