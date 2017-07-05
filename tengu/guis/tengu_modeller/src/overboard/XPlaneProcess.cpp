// ********************************************************************************************************************
// *                                                                                                                  *
// *                         Full-time invisible process for connection with an X-Plane simulator.                    *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                    Невидимый (постоянно невидимый) процесс для соединения с симулятором X-Plane                  *
// *                                                                                                                  *
// * Eugene G. Sysoletin <e.g.sysoletin@gmail.com>                                       Created 26 jun 2017 at 09:12 *
// ********************************************************************************************************************

#include "XPlaneProcess.h"

const QString tengu::XPlaneProcess::XPLANE_PROCESS_UUID = QString("9b914362-07a6-471b-ad64-f8028cfdc97e");
const QList<QString> tengu::XPlaneProcess::AIRCRAFTS_UUIDS = QList<QString>({
    "7dc03d65-c4e6-40fc-9b57-c85aac787cb0"      // 0 - user aircraft
    , "5d04260f-898b-472c-9421-fd996b70fbd1"    // 1
});

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                  The constructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                    Конструктор.                                                  *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XPlaneProcess::XPlaneProcess() 
    : Process()
{
    setSystemName( tr("xtengu") );
    setHumanName( tr("X-Plane simulation process"));
        
    for ( int idx = 0; idx < XPlaneProcess::AIRCRAFTS_UUIDS.size(); idx++ ) {
        XPlaneAircraft * acf = new XPlaneAircraft( idx );       
        addChild( acf );        
    };
    
    // There is not necessery to connect because this process contains only proxy.
    // Здесь не нужно соединение, этот процесс содержит только proxy.
    // this->connect();
    
}

// ********************************************************************************************************************
// *                                                                                                                  *
// *                                                   The destructor.                                                *
// * ---------------------------------------------------------------------------------------------------------------- *
// *                                                      Деструктор.                                                 *
// *                                                                                                                  *
// ********************************************************************************************************************

tengu::XPlaneProcess::~XPlaneProcess() {

}

