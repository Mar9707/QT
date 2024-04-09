#include "play.h"

Play::Play(QWidget *parent)
    : QListWidget{parent}
{

}

void Play::append_songs(QStringList& songs) {
    for (auto& song : songs){
        if (set.contains(song)){
            continue;
        }
        set.insert(song);
        QStringList l = song.split("/");
        plist << song;
        this -> addItem(l[l.length()-1]);
    }
}


void Play::set_next(){
    qint64 cur = currentRow();
    ++cur;
    if(cur >= count()){
        cur = 0;
    }
    setCurrentRow(cur);
}

void Play::set_prev(){
    qint64 cur = currentRow();
    --cur;
    if (cur <= -1){
        cur = count() - 1;
    }
    setCurrentRow(cur);
}


QString Play::cursong(){
    return plist[currentRow()];
}
