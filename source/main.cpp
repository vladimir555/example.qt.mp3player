#include <QApplication>

#include "controller/implementation/player.h"
#include "view/gui/main_window.h"


int main(int argc, char *argv[]) {
    QApplication    app(argc, argv);
    auto            player      = controller::implementation::CPlayer::create();
    auto            main_window = view::gui::CMainWindow::create(player);

    main_window->show();

    return app.exec(); // ----->
}
