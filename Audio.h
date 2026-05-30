#ifndef AUDIO_H
#define AUDIO_H
#include <Qstring>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QUrl>
#include <QObject>
#include <QtGlobal>
#include <iostream>
#include <QtMultimedia/QMediaMetaData>
using namespace std;
class MediaPlayer : public QObject
{
    Q_OBJECT
public:
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
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
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(MediaFile));
        QObject::connect(player, SIGNAL(metaDataChanged()), this, SLOT(get_duration()));
        audioOutput->setVolume(0.3f);
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
    void get_duration() // fetch media duration when metadata is ready
    {
        media_duration = player->duration();
        if (media_duration > 0)
        {
            cout << "Media duration: " << media_duration << endl;
            emit duration_ready(media_duration);
            ready = true;
        }
    }
};

#endif