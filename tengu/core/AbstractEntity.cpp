// ********************************************************************************************************************
// *                                                                                                                  *
// *                                An "entity" class, common parent for agents and sprouts.                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                        Класс "сущности", общий предок для агентов и ростков (связей агентов)                     *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 11 jun 2017 at 12:36 *
// ********************************************************************************************************************

#include "AbstractEntity.h"

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                     Конструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractEntity::AbstractEntity () 
{
    __system_name = QString("");
    __human_name = QString("");
    __comment = QString("");
    
    // The UUID is very important parameter. It can not be changed except fromJSON constructor.
    // UUID - это очень важный параметр. Он может быть переставлен только из конструктора fromJSON.
    
    __uuid = QUuid::createUuid().toString();
    
    // Initialization for change time, (probably) will be replaced later.
    // Инициализация времени изменения, (наверное) потом будет изменена.
    
    __lastModified = QDateTime::currentDateTimeUtc();
    
    __execution_mode = EM_ALWAYS;    
    
    // We have changes because the object was created.
    // У нас уже есть изменения, потому что объект был создан.
    
    _changed = true;
    _class_name = QString("");       
    _entity_type = AbstractEntity::ET_Unknown;
    
    __x = 0;
    __y = 0;

}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Get name of this agent.                                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Получить имя этого агента.                                            *
// *                                                                                                                  *
// ********************************************************************************************************************

QString tengu::AbstractEntity::getSystemName() {
    return __system_name;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Set name of this agent.                                             *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                           Установить имя данного агента.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::setSystemName ( QString name ) {
    __system_name = name;
    __system_name = __system_name.replace(' ', '_');
    _somethingChanged();    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Get human name of this agent.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Получить "человеческое" имя этого агента.                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

QString tengu::AbstractEntity::getHumanName() {
    return __human_name;    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Set the human name of this agent.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                     Установить человеческое имя этого агента.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::setHumanName( QString name ) {
    __human_name = name;
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                             Return UUID of this agent.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                            Вернуть UUID данного агента.                                          *
// *                                                                                                                  *
// ********************************************************************************************************************

QString tengu::AbstractEntity::getUUID() {
    return __uuid;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Set this agent uuid                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Установить uuid данного агента.                                         *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::setUUID ( QString uuid ) {
    __uuid = uuid;
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               Get entity's comment.                                              *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Получить комментарий данноой "сущности".                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

QString tengu::AbstractEntity::getComment() {
    return __comment;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                          Set comment for this "entity".                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Установить комментарий данной "сущности".                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::setComment ( QString comment ) {
    __comment = comment;
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                         Return execution mode of this entity.                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Вернуть режим выполнения данной сущности.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractEntity::execution_mode_t tengu::AbstractEntity::getExecutionMode() {
    return __execution_mode;
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                       Set execution mode for this entity.                                        *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                 Установить режим выполнения для данной сущности.                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::setExecutionMode( tengu::AbstractEntity::execution_mode_t mode ) {
    __execution_mode = mode;
    _somethingChanged();
};

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                               The X coordinate getter.                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                 Выдача координаты X                                              *
// *                                                                                                                  *
// ********************************************************************************************************************

int tengu::AbstractEntity::getX() {
    return __x;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                The X coordinate setter.                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                 Установка координаты X                                           *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::setX ( int x ) {
    __x = x;
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                The Y coordinate getter                                           *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                   Выдача координаты Y                                            *
// *                                                                                                                  *
// ********************************************************************************************************************

int tengu::AbstractEntity::getY() {
    return __y;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                 The Y coordinate setter.                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                  Установка координаты Y                                          *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::setY ( int y ) {
    __y = y;
    _somethingChanged();
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Has been this entity changed?                                          *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Была ли данная "сущность" изменена?                                        *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::AbstractEntity::hasChanged() {
    return _changed;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Somewhat has been changed in the class.                                   *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                        Что-то в данном классе было изменено.                                     *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::_somethingChanged() {
    _changed = true;
    __lastModified = QDateTime::currentDateTimeUtc();
    // emit signalHasBeenChanged( __lastModified );
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                    Return last modified time of this object, in the UTC.                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                Вернуть последнее время модификации данного объекта в UTC.                        *
// *                                                                                                                  *
// ********************************************************************************************************************

QDateTime tengu::AbstractEntity::lastModified() {
    return __lastModified;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Convert an entity to JSON format.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Преобразование "сущности" в формат JSON.                                   *
// *                                                                                                                  *
// ********************************************************************************************************************

QJsonObject tengu::AbstractEntity::toJSON() {
    
    QJsonObject o;
    
    o.insert(JSON_DATABASE_ELEMENT, TENGU_DATABASE );
    o.insert(JSON_UUID_ELEMENT, __uuid );
    o["system_name"] = __system_name;
    o["human_name"] = __human_name;
    o.insert("comment", __comment );
    o.insert("execution_mode", (int) __execution_mode );
    o.insert("last_modified", __lastModified.toString("t yyyy-MM-dd hh:mm:ss:zzz") );
    o.insert("x", __x );
    o.insert("y", __y );
    if ( ! _class_name.isEmpty() ) o[ JSON_CLASS_NAME_ELEMENT ] = _class_name;
    
    /*
    QJsonArray indexes;
    QJsonArray idx_up;
    idx_up.insert("uuid");
    indexes.insert( idx_up );    
    o.insert("indexes", indexes );
    */
    
    return o;
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Return type of this entity.                                            *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                          Вернуть тип данной сущности.                                            *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractEntity::entity_types_t tengu::AbstractEntity::entityType() {

    return _entity_type;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                              Make this object unmodified                                         *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Сделать данный объект не-модифицированным.                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

void tengu::AbstractEntity::unmodify() {

    _changed = false;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                           Get mongo indexes for this class.                                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                      Получить индексы монги для этого класса.                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

QMap<QString, tengu::MongoIndex> tengu::AbstractEntity::indexes() {
    
    QMap<QString, tengu::MongoIndex> result;
    
    MongoIndex idx_id;
    idx_id.name = "_id_";
    idx_id.key.append( MongoIndex::one_key_t ({ name : "_id", asc : 1 }));
    idx_id.unique = true;
    result[ idx_id.name ] = idx_id;
    
    // By system name
    // По системному имени.
    
    MongoIndex idx_sname;
    idx_sname.name = "idx_system_name";
    idx_sname.key.append( MongoIndex::one_key_t({ name : "system_name", asc: 1 } ) );
    result[ idx_sname.name ] = idx_sname;
    
    
    /*
    result["_id"] = 1;
    result["system_name"] = 1;
    result["human_name"] = 1;
    result["execution_mode"] = 1;
    */
    
    return result;
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                        Does json object have this class_name?                                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                       Имеет ли JSON-объект данное class_name?                                    *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::AbstractEntity::hasClass ( QJsonObject json, QString class_name ) {
    
    if ( json.contains("class_name") ) {
        QString cName = json.value("class_name").toString();
        if ( cName == class_name ) return true;
    };
    
    return false;
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                           Convert JSON notation to this object (the constructor from JSON).                      *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                               Преобразование из JSON в объект ("конструктор" от JSON).                           *
// *                                                                                                                  *
// ********************************************************************************************************************

bool tengu::AbstractEntity::fromJSON ( QJsonObject json ) {
    
    if ( ! _class_name.isEmpty() ) {
        if ( ! hasClass( json, _class_name ) ) return false;
    };
    
    if ( json.contains("uuid" ) ) __uuid = json.value("uuid").toString();
    if ( json.contains("system_name" ) ) __system_name = json.value("system_name").toString();
    if ( json.contains("human_name" ) ) __human_name = json.value("human_name").toString();
    if ( json.contains("execution_mode") ) __execution_mode = ( execution_mode_t ) json.value("execution_mode").toInt();
    if ( json.contains("last_modified") ) __lastModified = QDateTime::fromString( json.value("last_modified").toString(), "t yyyy-MM-dd hh:mm:ss:zzz" );
    
    return true;
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                    The destructor.                                               *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                       Деструктор.                                                *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::AbstractEntity::~AbstractEntity() {

}


