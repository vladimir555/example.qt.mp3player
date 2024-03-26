#pragma once


#include <QtMultimedia>
#include <QStatusBar>
#include "controller/player.h"


namespace controller::implementation {


class CPlayer:
    public QObject,
    public IPlayer
{
    Q_OBJECT
public:
    typedef QSharedPointer<CPlayer> TPtr;
    static TPtr create() {
        return TPtr::create();
    }

    CPlayer();
    virtual ~CPlayer() = default;

    void open       (QString const &path)   override;
    void play()                             override;
    void stop()                             override;
    void forward    (QTime const &time)     override;
    void backward   (QTime const &time)     override;

    void setStatusBar(QStatusBar *status_bar) override;

private:
    static qint64 convert(QTime const &time);

    void onErrorOccurred        (QMediaPlayer::Error code, const QString &error);
    void onMediaStatusChanged   (QMediaPlayer::MediaStatus status);

    QAudioOutput m_audio_output;
    QMediaPlayer m_media_player;
    QStatusBar  *m_status_bar;
};


} // controller::implementation
