#ifndef AUDIO_H
#define AUDIO_H
#include <Qstring>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaPlaylist>
#include <QUrl>
#include <QObject>
#include <QtGlobal>
#include <QMediaObject>
#include <iostream>
#include <QtMultimedia/QMediaMetaData>
using namespace std;
class MediaPlayer : public QObject
{
    Q_OBJECT
public:
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    QMediaPlaylist *playlist = new QMediaPlaylist;
    qint64 media_duration = 0;
    int last_pos = 0;
private:
    bool mp_if_terminate = true;
    bool finish_ok = false;
    bool ready = false;
signals:
    void duration_ready(int duration);
public slots:
    void setMediaFile(QString MediaFile)
    {
        player->setMedia(QUrl::fromLocalFile(MediaFile));
        QObject::connect(player, SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(get_duration(bool)));
        player->setVolume(30);
    }
    void PlayPause()
    {
        if (mp_if_terminate && !finish_ok && ready) //ready to start when ready flag is set
        {
            player->setPosition(last_pos); // start form last position
            player->play();
            mp_if_terminate = false;
        }
        else
        {
            player->stop();
            mp_if_terminate = true;
        }
    }
    void finish()
    {
        finish_ok = true;
    }
    void record_pos(int pos)
    {
        last_pos = pos;
    }
    void nextMedia()
    {
        ;
    }
private slots:
    void get_duration(bool available) // ready the duration of the media file
    {
        if (available)
        {
            media_duration = player->duration();
            cout << "Media duration: " << media_duration << endl;
            emit duration_ready(media_duration); //send time to Main.h/TimerProgress class
            ready = true;
        }
    }
};

#endif