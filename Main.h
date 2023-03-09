#ifndef MAIN_H
#define MAIN_H
#include <QtWidgets/QVBoxLayout>
#include <cstdio>
#include <iostream>
#include <QString>
#include <QObject>
#include <QTimer>
#include <QPushButton>
#include <cmath>
#include <QLabel>
#include <thread>
#include <chrono>
#include <QFileDialog>
#include <Audio.h>
#include <QList>
#include <QtWidgets/QScrollArea>
#include <QScrollBar>
#include <QKeyEvent>
using namespace std;
using namespace chrono;
/*
class Mainwindows : public QWidget
{
    Q_OBJECT
public:
    QWidget Mainwindow;
    void keyPressEvent(QKeyEvent *key_press)
    {
        if(key_press->key() == Qt::Key_Space)
        {
            emit playpause();
            std::cout << "space pressed" << std::endl;
            return;
        }
        QWidget::keyPressEvent(key_press);
    }
    void KeyReleaseEvent(QKeyEvent *key_release)
    {
        return;
    }
signals:
    void playpause();
};
*/
class TimerProgress : public QWidget
{
    Q_OBJECT
public:
    QWidget *mainwindow;
private:
    int scrollAreaHeight = 0;
    QScrollArea *scrollArea;
    int max_time = 0;
    bool if_terminate = true, first_start = true;
    int now_time = 0;
    QTimer *timer = new QTimer(this);
    QScrollBar *bar;
    high_resolution_clock::time_point start_time, end_time; //use chrono to ensure that timer will work properly on different platforms
    int key_press = 0;
signals:
    void updated(int stacks, int heights);
    void finished();
    void timer_timeout(int time_pieces);
    void start_player();
    void pause_player();
public slots:
    void PlayPause()
    {
        if(if_terminate && now_time < max_time)
        {
            if_terminate = false;
            first_start = true; // Avoiding timer adding a time contianing the pause time.
            timer->start(50);
            QObject::connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeout())); //timer to time
            scrollArea = mainwindow->findChild<QScrollArea *>(QString::fromUtf8("scrollArea")); //get height when start playing for scrolling
        }
        else
        {
            if_terminate = true; //stop timer and lyrics
            timer->stop();
        }
    }
    void Next()
    {
        cout << "next" << endl;
    }
    void Pre()
    {
        cout << "pre" << endl;
    }
private slots:
    void TimeAdd(int time_piece)
    {
        if (now_time >= max_time)
        {
            if_terminate = true;
            emit finished();
        }
        else
        {
            now_time += time_piece;
            cout << "now: " << now_time << endl; // delete-------------
            scrollAreaHeight = scrollArea->height();
            emit updated(now_time, scrollAreaHeight);
        }
    }
    void handleTimeout()
    {
        if (first_start) //set first to reset
        {
            end_time = high_resolution_clock::now();
            first_start = false;
            emit timer_timeout(50); // first time also need to add time
        }
        start_time = high_resolution_clock::now();
        emit timer_timeout(int(duration_cast<duration<double>>(start_time - end_time).count() * 1000)); //calcuate time
        end_time = start_time;
    }
    void duration_ready(int duration)
    {
        max_time = duration; //set the max time by media data fetched
    }
};

class Lyrics : public QObject
{
    Q_OBJECT
public:
    //char lyrics[255][255] = {};
    QList<QString> lyrics;
    int time_info[255] = {};
    int line_num = 0;
    int starts = 0;
    bool lrc_exist = true;
    QWidget *mainwindow;
signals:
    void max_time(int max);
};

class Progress : public QObject
{
    Q_OBJECT
public:
    int lines = 0;
    Lyrics *Lrc;
    QList<QLabel *> QLabels;
    QWidget *mainwindow;
    void preConfig()
    {
        scrollarea = mainwindow->findChild<QScrollArea *>(QString::fromUtf8("scrollArea"));
        scrollbar = scrollarea->verticalScrollBar();
    }
private:
    QScrollArea *scrollarea;
    QScrollBar *scrollbar;
    bool done = false;
    int pos_factor = 0;
public slots:
    void Rolling(int now, int AreaHeight)
    {
        if (!done && Lrc->lrc_exist)
        {
            if (Lrc->time_info[lines] - now <= 100)
            {
                if(lines >= 4) // clear the lyrics above
                {
                    //int elementHeightBig = QLabels[lines]->height();
                    QLabels[lines - 4]->setFont(QFont("Heiti SC", 12));
                    QLabels[lines - 4]->setStyleSheet("color: grey");
                    QLabels[lines - 3]->setFont(QFont("Heiti SC", 12));
                    QLabels[lines - 3]->setStyleSheet("color: grey");
                    QLabels[lines - 2]->setFont(QFont("Heiti SC", 12));
                    QLabels[lines - 2]->setStyleSheet("color: grey");
                    QLabels[lines - 1]->setFont(QFont("Heiti SC", 12));
                    QLabels[lines - 1]->setStyleSheet("color: grey");
                    QLabels[lines]->setFont(QFont("Heiti SC", 12));
                    QLabels[lines]->setStyleSheet("color: grey");
                    int elementHeight = QLabels[lines - 4]->height();
                    //scrollbar->setValue(lines * elementHeight); --how to solve this!?
                }
                else // do not go out of range
                {
                    for (int i = 0; i <= lines; i++)
                    {
                        QLabels[i]->setFont(QFont("Heiti SC", 12));
                        QLabels[i]->setStyleSheet("color: grey");
                    }
                }
            }
            while (Lrc->time_info[lines] - now <= 100)
            {
                QLabels[lines]->setFont(QFont("Heiti SC",18));
                QLabels[lines]->setStyleSheet("color: black");
                if(Lrc->line_num - 1 > lines) // line_num - 1为总长，此为防越界
                {
                    lines++;
                }
                else
                {
                    done = true;
                    break;
                }
            }
        }
    }
};

void lrc_file_process(int *line, string path, QList<QString> *lyric, int time_info[255], int *start_pos, bool *lrc_exists);
void Connects(QWidget *Window, TimerProgress *TM, Lyrics *LRC, Progress *PRO, MediaPlayer *MP);
void RemoveAllChild(QLayout *layout);
void Display(int time_info[255], QList<QString> lyrics, QVBoxLayout *LyricLayout, int line_num, int start_pos, QList<QLabel *> *lrc, bool lrc_exists);
void lrc_append(QWidget *Window, QVBoxLayout *lrc_layout);
#endif