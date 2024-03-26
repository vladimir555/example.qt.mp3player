#pragma once

#include <QMainWindow>


#include "controller/player.h"


namespace view::gui {


class CMainWindow: public QMainWindow {
    Q_OBJECT
public:
    typedef QSharedPointer<CMainWindow> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }

    CMainWindow(controller::IPlayer::TPtr const &player);
    virtual ~CMainWindow() = default;

private:
    void    onOpenClick();
    void    onPlayClick();
    void    onStopClick();
    void    onForwardClick();
    void    onBackwardClick();
    void    onCloseClick();

    QString                     m_file_name;
    controller::IPlayer::TPtr   m_player;
};


} // view::gui
