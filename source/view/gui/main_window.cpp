#include "main_window.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QStatusBar>


static QTime const DEFAULT_REWIND_TIME(0, 0, 5);


namespace view::gui {


CMainWindow::CMainWindow(controller::IPlayer::TPtr const &player)
:
    m_player(player)
{
    QWidget     *central_widget     = new QWidget(this); // Создание центрального виджета
    QVBoxLayout *layout             = new QVBoxLayout(central_widget); // Создание вертикального layout

    // Создание кнопок
    QPushButton *open_button        = new QPushButton(tr("Open")    , central_widget);
    QPushButton *play_button        = new QPushButton(tr("Play")    , central_widget);
    QPushButton *stop_button        = new QPushButton(tr("Stop")    , central_widget);
    QPushButton *forward_button     = new QPushButton(tr("Forward") , central_widget);
    QPushButton *backward_button    = new QPushButton(tr("Backward"), central_widget);
    QPushButton *close_button       = new QPushButton(tr("Close")   , central_widget);

    // Добавление кнопок в layout
    layout->addWidget(open_button);
    layout->addWidget(play_button);
    layout->addWidget(stop_button);
    layout->addWidget(forward_button);
    layout->addWidget(backward_button);
    layout->addWidget(close_button);

    // Установка centralWidget как центрального виджета QMainWindow
    setCentralWidget(central_widget);

    statusBar()->showMessage(tr(""));

    // Сигналы и слоты для кнопок (пример для кнопки "Open File")
    connect(open_button,        &QPushButton::clicked, this, &CMainWindow::onOpenClick);
    connect(play_button,        &QPushButton::clicked, this, &CMainWindow::onPlayClick);
    connect(stop_button,        &QPushButton::clicked, this, &CMainWindow::onStopClick);
    connect(forward_button,     &QPushButton::clicked, this, &CMainWindow::onForwardClick);
    connect(backward_button,    &QPushButton::clicked, this, &CMainWindow::onBackwardClick);
    connect(close_button,       &QPushButton::clicked, this, &CMainWindow::close);

    m_player->setStatusBar(statusBar());
}


void CMainWindow::onOpenClick() {
    try {
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setNameFilter(tr("MP3 files (*.mp3)"));
        dialog.setViewMode(QFileDialog::Detail);
        if (dialog.exec() && !dialog.selectedFiles().empty()) {
            auto path = dialog.selectedFiles().constLast();
            m_file_name = QFileInfo(path).fileName();
            m_player->open(path);
            // statusBar()->showMessage(("Opened: " + m_file_name));
        }
    } catch (std::exception const &e) {
        statusBar()->showMessage(tr(e.what()));
    }
}


void CMainWindow::onPlayClick() {
    try {
        m_player->play();
        // statusBar()->showMessage(("Playing: " + m_file_name));
    } catch (std::exception const &e) {
        statusBar()->showMessage(tr(e.what()));
    }
}


void CMainWindow::onStopClick() {
    try {
        m_player->stop();
        // statusBar()->showMessage(("Stopped: " + m_file_name));
    } catch (std::exception const &e) {
        statusBar()->showMessage(tr(e.what()));
    }
}


void CMainWindow::onForwardClick() {
    try {
        m_player->forward(DEFAULT_REWIND_TIME);
    } catch (std::exception const &e) {
        statusBar()->showMessage(tr(e.what()));
    }
}


void CMainWindow::onBackwardClick() {
    try {
        m_player->backward(DEFAULT_REWIND_TIME);
    } catch (std::exception const &e) {
        statusBar()->showMessage(tr(e.what()));
    }
}


} // view::gui
