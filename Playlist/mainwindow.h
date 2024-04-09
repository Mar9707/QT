#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
//#include "playlist.h"
#include "play.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTime(qint64);
    int percent (int, double);



public slots:
    void dataChanged();
    void handleDuration();
    void handlePosition(qint64 m);
    void resizeEvent(QResizeEvent*);
    void play_pause();
    void pauseSong();
    void handleVolume();
    void openFile();
    void handle_next();
    void handle_prev();
    // void handleSongReady();
    void handleCurrentChanged(qint64 curr);



private:
   // Ui::MainWindow *ui;
    QPushButton* play;
    QPushButton* stop;
    QPushButton* open;
    QLabel* name;
    QLabel* time;
    QSlider* volume;
    QSlider* dur;
    QMediaPlayer* player;
    QAudioOutput* out;
    bool play_flag = false;
    qint64 milis;
    bool lock = false;
    QPushButton *next;
    QPushButton *prev;
    //Playlist *playlist;
    Play *list;


};
#endif // MAINWINDOW_H
