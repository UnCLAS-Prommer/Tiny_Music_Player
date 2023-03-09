/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QTMAINGUI_H
#define QTMAINGUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QFrame *Frame;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *Main_Layout;
    QVBoxLayout *Structure;
    QVBoxLayout *INFO;
    QLabel *Title;
    QLabel *Album_Name;
    QLabel *Artist;
    QHBoxLayout *LyricAlbum;
    QLabel *Album_Picture;
    QScrollArea *scrollArea;
    QWidget *Lrc_Widget;
    QHBoxLayout *Controls;
    QSpacerItem *horizontalSpacer_L;
    QPushButton *Previous;
    QPushButton *PlayPause;
    QPushButton *Next;
    QSpacerItem *horizontalSpacer_R;


    void setupUi(QWidget *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QString::fromUtf8("Window"));
        Window->resize(1000, 600);
        Window->setMinimumSize(QSize(1000, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../tune.ico"), QSize(), QIcon::Normal, QIcon::On);
        Window->setWindowIcon(icon);
        Frame = new QFrame(Window);
        Frame->setObjectName(QString::fromUtf8("Frame"));
        Frame->setGeometry(QRect(0, 0, 1000, 600));
        Frame->setMinimumSize(QSize(1000, 600));
        Frame->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 250, 250);"));
        Frame->setFrameShape(QFrame::StyledPanel);
        Frame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_3 = new QWidget(Frame);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(0, 0, 1001, 601));
        Main_Layout = new QVBoxLayout(verticalLayoutWidget_3);
        Main_Layout->setObjectName(QString::fromUtf8("Main_Layout"));
        Main_Layout->setSizeConstraint(QLayout::SetMaximumSize);
        Main_Layout->setContentsMargins(5, 5, 5, 5);
        Structure = new QVBoxLayout();
        Structure->setObjectName(QString::fromUtf8("Structure"));
        Structure->setContentsMargins(5, 5, 5, 5);
        INFO = new QVBoxLayout();
        INFO->setObjectName(QString::fromUtf8("INFO"));
        Title = new QLabel(verticalLayoutWidget_3);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setStyleSheet(QString::fromUtf8(""));

        INFO->addWidget(Title);

        Album_Name = new QLabel(verticalLayoutWidget_3);
        Album_Name->setObjectName(QString::fromUtf8("Album_Name"));

        INFO->addWidget(Album_Name);

        Artist = new QLabel(verticalLayoutWidget_3);
        Artist->setObjectName(QString::fromUtf8("Artist"));
        Artist->setEnabled(true);

        INFO->addWidget(Artist);


        Structure->addLayout(INFO);

        LyricAlbum = new QHBoxLayout();
        LyricAlbum->setObjectName(QString::fromUtf8("LyricAlbum"));
        LyricAlbum->setContentsMargins(5, 5, 5, 5);
        Album_Picture = new QLabel(verticalLayoutWidget_3);
        Album_Picture->setObjectName(QString::fromUtf8("Album_Picture"));

        LyricAlbum->addWidget(Album_Picture);

        scrollArea = new QScrollArea(verticalLayoutWidget_3);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        Lrc_Widget = new QWidget();
        Lrc_Widget->setObjectName(QString::fromUtf8("Lrc_Widget"));
        Lrc_Widget->setGeometry(QRect(0, 0, 641, 418));
        scrollArea->setWidget(Lrc_Widget);

        LyricAlbum->addWidget(scrollArea);

        LyricAlbum->setStretch(0, 1);
        LyricAlbum->setStretch(1, 2);

        Structure->addLayout(LyricAlbum);

        Structure->setStretch(0, 2);
        Structure->setStretch(1, 10);

        Main_Layout->addLayout(Structure);

        Controls = new QHBoxLayout();
        Controls->setObjectName(QString::fromUtf8("Controls"));
        horizontalSpacer_L = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Controls->addItem(horizontalSpacer_L);

        Previous = new QPushButton(verticalLayoutWidget_3);
        Previous->setObjectName(QString::fromUtf8("Previous"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../Pre.png"), QSize(), QIcon::Normal, QIcon::Off);
        Previous->setIcon(icon1);
        Previous->setIconSize(QSize(40, 40));
        Previous->setFlat(true);

        Controls->addWidget(Previous);

        PlayPause = new QPushButton(verticalLayoutWidget_3);
        PlayPause->setObjectName(QString::fromUtf8("PlayPause"));
        PlayPause->setCursor(QCursor(Qt::ArrowCursor));
        PlayPause->setFocusPolicy(Qt::StrongFocus);
        PlayPause->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../Pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8("../Play.png"), QSize(), QIcon::Normal, QIcon::On);
        PlayPause->setIcon(icon2);
        PlayPause->setIconSize(QSize(40, 40));
        PlayPause->setFlat(true);

        Controls->addWidget(PlayPause);

        Next = new QPushButton(verticalLayoutWidget_3);
        Next->setObjectName(QString::fromUtf8("Next"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../Next.png"), QSize(), QIcon::Normal, QIcon::Off);
        Next->setIcon(icon3);
        Next->setIconSize(QSize(40, 40));
        Next->setFlat(true);

        Controls->addWidget(Next);

        horizontalSpacer_R = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Controls->addItem(horizontalSpacer_R);

        Controls->setStretch(0, 4);
        Controls->setStretch(1, 1);
        Controls->setStretch(2, 1);
        Controls->setStretch(3, 1);
        Controls->setStretch(4, 4);

        Main_Layout->addLayout(Controls);

        Main_Layout->setStretch(0, 10);
        Main_Layout->setStretch(1, 1);

        retranslateUi(Window);

        Next->setDefault(false);


        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QWidget *Window)
    {
        Window->setWindowTitle(QCoreApplication::translate("Window", "Mini Player", nullptr));
        Title->setText(QCoreApplication::translate("Window", "Title Here", nullptr));
        Album_Name->setText(QCoreApplication::translate("Window", "Album Here", nullptr));
        Artist->setText(QCoreApplication::translate("Window", "Artists Here", nullptr));
        Album_Picture->setText(QCoreApplication::translate("Window", "TextLabel", nullptr));
#if QT_CONFIG(whatsthis)
        Previous->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        Previous->setText(QString());
        PlayPause->setText(QString());
        Next->setText(QString());
    } // retranslateUi
};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTMAINGUI_H
