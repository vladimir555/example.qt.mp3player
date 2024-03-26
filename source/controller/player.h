#pragma once


#include <qsharedpointer.h>

#include <QStatusBar>


namespace controller {


class IPlayer {
public:
    typedef QSharedPointer<IPlayer> TPtr;
    virtual ~IPlayer() = default;

    virtual void open           (QString const &file_name)  = 0;
    virtual void play           ()                          = 0;
    virtual void stop           ()                          = 0;
    virtual void forward        (QTime const &time)         = 0;
    virtual void backward       (QTime const &time)         = 0;
    virtual void setStatusBar   (QStatusBar *status_bar)    = 0;
};


} // controller
