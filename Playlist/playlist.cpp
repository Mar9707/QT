/*
#include "playlist.h"
#include "qpushbutton.h"

Playlist::Playlist(QWidget *parent)
    : QLabel{parent}
{
    lay = new QVBoxLayout();
    setLayout(lay);
}


void Playlist::append_songs(QStringList& songs){
    for (auto& song : songs) {
        if (set.contains(song)){
            continue;
        }
        set.insert(song);
        QStringList l = song.split("/");
        QPushButton *btn = new QPushButton(l[l.length()-1]);
        lay->addWidget(btn);
        plist << song;
        qint64 i = this->curindex;
        connect(btn, &QPushButton::clicked, [=](){
            init_song(i);
        });
        ++curindex;
    }
}


void Playlist::init_song(qint64 i) {
    if (plist.isEmpty()) {
        return;
    }

    if (i < 0) {
        i = plist.size() - 1;
    } else if (i >= plist.size()) {
        i = 0;
    }

    /*if (i < 0){
        i = ind - 1;
    }

    if (i >= ind){
        i = 0;
    }
    cursong = plist[i];
    curindex = i;


    emit songIsReady();
}


void Playlist::set_next(){
    init_song(curindex + 1);
}


void Playlist::set_prev(){
    init_song(curindex-1);
}


QString Playlist::getCurrentSong(){
    return cursong;
}


Playlist::~Playlist(){
    delete lay;
}
*/
