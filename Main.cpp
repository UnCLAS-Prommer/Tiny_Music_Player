#include <iostream>
#include <cstdio>
#include <cstring>
#include <thread>
#include <QtMainGUI.h>
#include <Main.h>
#include <QtWidgets/QApplication>
//#include <QGraphicsEffect>
using namespace std;
/*void newmusic()
{

}
void set_frame(QWidget *Mainwindow)
{
    Mainwindow->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect window_effect;
    window_effect.setOffset(QPoint(0, 0));
    window_effect.setColor(QColor("#000000"));
    window_effect.setBlurRadius(5);
    //QFrame *frame = Mainwindow->findChild<QFrame *>();
    Mainwindow->setContentsMargins(10,10,10,10);
    //frame->setGraphicsEffect(&window_effect);
    //Mainwindow->setWindowFlags(Qt::FramelessWindowHint);
}*/
int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    Ui_Window UI;  //Just for using "setupUI" function, no beautiful replacement founded.
    QVBoxLayout lrc_layout;
    QWidget Mainwindow;
    MediaPlayer *mp = new MediaPlayer;
    TimerProgress *tm = new TimerProgress;
    Progress *pro = new Progress;
    QList<QLabel *> lrc_line;
    Lyrics *lrc = new Lyrics;
    //set_frame(&Mainwindow);
    //Mainwindow.setWindowFlags(Qt::FramelessWindowHint);
    //FILE *music;
    string path;
    int start_pos = 0;
    //cout << "Path: ";
    //getline(cin, path);
    QString filename = QFileDialog::getOpenFileName(&Mainwindow, "Open File", "V:", "Music (*.mp3 *.aac *.flac *.ape *.wav)");
    mp->setMediaFile(filename);
    path = filename.toStdString();
    //music = _wfopen(path.c_str(), "rb");
    lrc_file_process(&lrc->line_num, path, &lrc->lyrics, lrc->time_info, &start_pos, &lrc->lrc_exist); //read files
    pro->lines = start_pos + 1;
    lrc->starts = start_pos;
    UI.setupUi(&Mainwindow); // Setup the window
    Connects(&Mainwindow, tm, lrc, pro, mp);
    Display(lrc->time_info, lrc->lyrics, &lrc_layout, lrc->line_num, start_pos, &lrc_line, lrc->lrc_exist); // make lyrics layout and set QLabel
    lrc_append(&Mainwindow, &lrc_layout);// append lrc
    pro->QLabels = lrc_line;
    pro->Lrc = lrc;
    tm->mainwindow = &Mainwindow;
    pro->mainwindow = &Mainwindow;
    pro->preConfig();
    Mainwindow.show();
    //tm->getinterval(tm);
    //fclose(music);
    return App.exec();
}