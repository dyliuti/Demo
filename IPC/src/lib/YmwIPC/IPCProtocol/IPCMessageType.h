#ifndef IPCMESSAGETYPE_H
#define IPCMESSAGETYPE_H

#include <QObject>
#include "ymwIPC_global.h"

enum IPCDataType {
    PostTest_SC = 0,
    SendTest_SC = 1,
    PostTest_CS = 2,
    Unknow = 255
};



#endif // IPCMESSAGETYPE_H
