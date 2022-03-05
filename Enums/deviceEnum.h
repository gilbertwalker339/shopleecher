#ifndef DEVICEENUM_H
#define DEVICEENUM_H

#include <QObject>

class DeviceEnum {
    Q_GADGET

private:
    explicit DeviceEnum();

public:
    enum Value {
        iPhone = 1 << 0,
        iPad = 1 << 1,
        MacBook = 1 << 2
    };

    Q_ENUM(Value);
};

#endif // DEVICEENUM_H
