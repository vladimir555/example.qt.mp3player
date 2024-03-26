#include "player.h"


namespace controller::implementation {


static float DEFAULT_VOLUME = 50;


CPlayer::CPlayer()
:
    m_status_bar(nullptr)
{
    m_media_player.setAudioOutput(&m_audio_output);
    m_audio_output.setVolume(DEFAULT_VOLUME);

    connect(&m_media_player, &QMediaPlayer::errorOccurred,      this, &CPlayer::onErrorOccurred);
    connect(&m_media_player, &QMediaPlayer::mediaStatusChanged, this, &CPlayer::onMediaStatusChanged);
}


void CPlayer::open(QString const &path) {
    m_media_player.setSource(QUrl::fromLocalFile(path));
    // if (!m_media_player.errorString().isEmpty())
    //     throw std::runtime_error(m_media_player.errorString().toStdString().c_str());
}


void CPlayer::play() {
    m_media_player.play();
    // if (!m_media_player.errorString().isEmpty())
    //     throw std::runtime_error(m_media_player.errorString().toStdString().c_str());
}


void CPlayer::stop() {
    m_media_player.stop();
    // if (!m_media_player.errorString().isEmpty())
    //     throw std::runtime_error(m_media_player.errorString().toStdString().c_str());
}


void CPlayer::forward(QTime const &time) {
    m_media_player.setPosition(m_media_player.position() + convert(time));
    // if (!m_media_player.errorString().isEmpty())
    //     throw std::runtime_error(m_media_player.errorString().toStdString().c_str());
}


void CPlayer::backward(QTime const &time) {
    m_media_player.setPosition(m_media_player.position() - convert(time));
    // if (!m_media_player.errorString().isEmpty())
    //     throw std::runtime_error(m_media_player.errorString().toStdString().c_str());
}


void CPlayer::setStatusBar(QStatusBar *status_bar) {
    m_status_bar = status_bar;
}


qint64 CPlayer::convert(QTime const &time) {
    return (time.hour() * 3600 + time.minute() * 60 + time.second()) * 1000 + time.msec();
}


void CPlayer::onErrorOccurred(QMediaPlayer::Error code, const QString &error) {
    if (m_status_bar)
        m_status_bar->showMessage(error);
    qDebug() << error;
}


void CPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (m_status_bar)
        m_status_bar->showMessage(QMetaEnum::fromType<QMediaPlayer::MediaStatus>().valueToKey(status));
    // qDebug() << status;
}


} // controller::implementation
