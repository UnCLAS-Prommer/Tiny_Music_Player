#include <Main.h>
#include <QLabel>
#include <QList>
using namespace std;
void lrc_file_process(int *line, string path, QList<QString> *lyric, int time_info[255], int *start_pos, bool *lrc_exits)
{
    *start_pos = 0;
    char orig_lrc[255][255]; // I think it's difficult to find a lrc as long as 255 lines;
    FILE *lrc;
    int pos = path.find_last_of("."); //find filename without extensions.
    bool symbol = false;
    if (path.find("\"") == 0 || path.find("\'") == 0)
        symbol = true;
    string lrc_path;
    symbol ? lrc_path = path.substr(1, pos - 1) + ".lrc":lrc_path = path.substr(0, pos) + ".lrc"; // clean the ' or "
    lrc = fopen(lrc_path.c_str(), "r");
    if (lrc == NULL)
    {
        // cout << "File can't be opened. Or no file exists." << endl;
        *lrc_exits = false;
    }
    else
    {
        string temp, tempstr;
        int i = 0, offset = 0;
        bool done = false;
        pos = 0;
        while (fgets(orig_lrc[i], 255, lrc) != NULL) // read the file and get the number of the line
        {
            if (int(orig_lrc[i][0]) == 10)
                break;
            temp = orig_lrc[i];
            if (temp.find("[offset:") != -1) //get offset
            {
                bool minus_flag = false;
                int temp_pos1 = temp.find(":"), temp_pos2 = temp.find("]"), k = temp_pos2 - temp_pos1 - 2;
                for (int j = temp_pos1 + 1; j < temp_pos2; j++)
                {
                    if (temp[j] == '-')
                    {
                        minus_flag = true;
                        k--;
                        continue;
                    }
                    offset += int((int(temp[j]) - 48) * pow(10.0, float(k)));
                    k--;
                }
                if (minus_flag)
                {
                    offset *= -1;
                }
            }
            pos = temp.find("]");
            tempstr = temp.substr(pos + 1, temp.length() - pos - 2);
            if (tempstr != "")
                done = true;
            if (tempstr == "" && done == false)
                *start_pos = i; //search the start point of the lyrics.
            lyric->push_back(QString::fromStdString(tempstr));
            tempstr = temp.substr(0, pos + 1);
            // Get time in milliseconds
            if (tempstr.length() == 10 && done == true)
                time_info[i] = offset + 1000 * (60 * (10 * (int(tempstr[1]) - 48) + (int(tempstr[2]) - 48)) + 10 * (int(tempstr[4]) - 48) + (int(tempstr[5]) - 48)) + 100 * (int(tempstr[7]) - 48) + 10 * (int(tempstr[8] - 48));
            if (tempstr.length() == 11 && done == true)
                time_info[i] = offset + 1000 * (60 * (10 * (int(tempstr[1]) - 48) + (int(tempstr[2]) - 48)) + 10 * (int(tempstr[4]) - 48) + (int(tempstr[5]) - 48)) + 100 * (int(tempstr[7]) - 48) + 10 * (int(tempstr[8] - 48)) + int(tempstr[9]) - 48;
            i++; // get the line num
        }
        *line = i;
    }
    fclose(lrc);
}
void Connects(QWidget *Window, TimerProgress *TM, Lyrics *LRC, Progress *PRO, MediaPlayer *MP)
{
    QPushButton *NextButton = Window->findChild<QPushButton *>(QString::fromStdString("Next"));
    QPushButton *PauseButton = Window->findChild<QPushButton *>(QString::fromStdString("PlayPause"));
    QPushButton *PreButton = Window->findChild<QPushButton *>(QString::fromStdString("Previous"));
    QObject::connect(NextButton, SIGNAL(clicked()), TM, SLOT(Next()));
    QObject::connect(PauseButton, SIGNAL(clicked()), TM, SLOT(PlayPause()));
    QObject::connect(PauseButton, SIGNAL(clicked()), MP, SLOT(PlayPause()));
    QObject::connect(PreButton, SIGNAL(clicked()), TM, SLOT(Pre()));
    QObject::connect(TM, SIGNAL(updated(int, int)), PRO, SLOT(Rolling(int, int)));
    QObject::connect(TM, SIGNAL(updated(int, int)), MP, SLOT(record_pos(int)));
    QObject::connect(TM, SIGNAL(timer_timeout(int)), TM, SLOT(TimeAdd(int)));
    QObject::connect(TM, SIGNAL(finished()), MP, SLOT(finish()));
    QObject::connect(MP, SIGNAL(duration_ready(int)), TM, SLOT(duration_ready(int)));
}
void RemoveAllChild(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) 
    {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }
}
void Display(int time_info[255], QList<QString> lyrics, QVBoxLayout *LyricLayout, int line_num, int start_pos, QList<QLabel *> *lrc, bool lrc_exists)
{
    RemoveAllChild(LyricLayout); // Need to remove this or it will append to much objects.
    for (int i = 0; i < start_pos; i++)
        lrc->push_back(new QLabel);/*
    for (int i = 0; i < 9; i++)
        LyricLayout->addWidget(new QLabel);//add previous labels for a better looking*/
    for (int i = start_pos; i < line_num; i++)
    {
        lrc->push_back(new QLabel());
        lrc->at(i)->setText(lyrics.at(i));
        lrc->at(i)->setFont(QFont("Heiti SC", 12));
        lrc->at(i)->setStyleSheet("color: grey");
        lrc->at(i)->setAlignment(Qt::AlignHCenter);
        lrc->at(i)->setWordWrap(true);
        LyricLayout->addWidget(lrc->at(i));
        /*if (!(time_info[i + 1] == time_info[i]))
            LyricLayout->addWidget(new QLabel);*/
    }
    if(!lrc_exists)
    {
        lrc->push_back(new QLabel());
        lrc->at(0)->setText(QString::fromUtf8("No Lyrics for this music."));
        lrc->at(0)->setFont(QFont("Heiti SC", 12));
        lrc->at(0)->setStyleSheet("color: grey");
        lrc->at(0)->setAlignment(Qt::AlignHCenter);
        lrc->at(0)->setWordWrap(true);
        LyricLayout->addWidget(lrc->at(0));
    }
}
void lrc_append(QWidget *Window, QVBoxLayout *lrc_layout) // layout set
{
    lrc_layout->setObjectName(QString::fromUtf8("Lyrics"));
    QWidget *Lrc = Window->findChild<QWidget *>(QString::fromUtf8("Lrc_Widget"));
    Lrc->setLayout(lrc_layout);
}