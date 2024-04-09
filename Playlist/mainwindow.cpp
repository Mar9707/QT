#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(900, 600);
    play = new QPushButton("Play", this);
    stop = new QPushButton("Stop", this);
    open = new QPushButton("Open", this);
    name = new QLabel("Song name", this);
    time = new QLabel("00:00", this);
    volume = new QSlider(Qt::Horizontal, this);
    dur = new QSlider(Qt::Horizontal, this);
    player = new QMediaPlayer(this);
    out = new QAudioOutput(this);
    player->setAudioOutput(out);

    player->setSource(QUrl("/home/mariam/Downloads/1.mp3"));
    player->play();
    next = new QPushButton(">>", this);
    prev = new QPushButton("<<", this);
    //playlist = new Playlist(this);
    list = new Play(this);


    QString path = "/home/mariam/Downloads/1.mp3";
    QStringList l = path.split("/");
    name->setText(l[l.length()-1]);

    volume->setMaximum(100);
    volume->setMinimum(0);
    volume->setValue(50);

    connect(play, &QPushButton::clicked, this, &MainWindow::play_pause);
    connect(stop, &QPushButton::clicked, this, &MainWindow::play_pause);
    connect (player, &QMediaPlayer::metaDataChanged, this, &MainWindow::dataChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::handlePosition);
    connect (dur, &QSlider::valueChanged, this, &MainWindow::handleDuration);
    connect(volume, &QSlider::valueChanged, this,  &MainWindow::handleVolume);
    connect(open, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(next, &QPushButton::clicked, this, &MainWindow::handle_next);
    connect(prev, &QPushButton::clicked, this, &MainWindow::handle_prev);
    //connect(playlist, &Playlist::songIsReady, this, &MainWindow::handleSongReady);
    connect(list, &QListWidget::currentRowChanged, this, &MainWindow::handleCurrentChanged);
}



void MainWindow::handle_next(){
    //playlist->set_next();
    list->set_next();
}

void MainWindow::handle_prev(){
    //playlist->set_prev();
    list->set_prev();
}

/*void MainWindow::handleSongReady(){
    player->setSource(playlist->getCurrentSong());
    QStringList l = playlist->getCurrentSong().split("/");
    name->setText(l[l.length()-1]);
}*/



void MainWindow::handleCurrentChanged(qint64 curr){
    player->setSource(QUrl(list->cursong()));
    QStringList l = list->cursong().split("/");
    name->setText(l[l.length()-1]);
}


void MainWindow::handleVolume() {
    out->setVolume(volume->value()/100.0);
}

void MainWindow::openFile() {
    /*QString path = QFileDialog::getOpenFileName();
    if (path == "") {
        return;
    }
    player->setSource(QUrl(path));
    QStringList l = path.split("/");
    name->setText(l[l.length()-1]);*/

    QStringList songs=QFileDialog::getOpenFileNames(this, tr("Open Audio File"), QDir::homePath(), tr("Audio Files (*.mp3 *.wav *.ogg)"));
   // playlist->append_songs(songs);
    list->append_songs(songs);
}



void MainWindow::dataChanged () {
    milis = player->duration();
    dur->setMinimum(0);
    dur->setMaximum(milis);
    setTime(0);
}

void MainWindow::setTime (qint64 m){
    qint64 t = milis-m;
    time->setText(QString::number(t/60000)+":"+QString::number((t % 60000)/1000));
}

void MainWindow::handlePosition(qint64 m){
    if (!lock){
        lock = true;
        dur -> setValue(m);
        setTime(m);
        lock = false;
    }

}

void MainWindow::handleDuration(){
    if(!lock){
        lock = true;
        qint64 t = dur->value();
        setTime(t);
        player->setPosition(t);
        lock = false;
    }

}

int MainWindow::percent(int val, double p) {
    return (p * val) / 100;
}


void MainWindow::resizeEvent(QResizeEvent* e) {
    QMainWindow::resizeEvent(e);

    this->setStyleSheet("background: Lavender");

    int h = this->height();
    int w = this->width();

    int start_h = percent(h, 5);
    play->setGeometry(percent(w, 5), percent(h, 5), percent(w, 10), start_h);
    play->setStyleSheet("background: MediumPurple");

    int pause_h = percent(h, 5);
    stop->setGeometry(percent(w, 20), percent(h, 5), percent(w, 10), pause_h);
    stop->setStyleSheet("background: MediumPurple");

    int name_h = percent(h, 10);
    name->setGeometry(percent(w, 35), percent(h, 5), percent(w, 35), name_h);
    name->setStyleSheet("background: MediumPurple");
    name->setAlignment(Qt::AlignCenter);

    int open_h = percent(h, 5);
    open->setGeometry(percent(w, 75), percent(h, 5), percent(w, 20), open_h);
    open->setStyleSheet("background: MediumPurple");

    int volume_h = percent(h, 5);
    volume->setGeometry(percent(w, 75), percent(h, 12.5), percent(w, 20), volume_h);
    volume->setStyleSheet("color: darkCyan");

    int duration_h = percent(h, 5);
    dur->setGeometry(percent(w, 5), percent(h, 20), percent(w, 70), duration_h);
    dur->setStyleSheet("color: darkCyan");

    int sliderDur_h = percent(h, 5);
    time->setGeometry(percent(w, 85), percent(h, 20), percent(w, 10), sliderDur_h);
    time->setStyleSheet("background: MediumPurple");
    time->setAlignment(Qt::AlignCenter);

    //int playlist_h = percent(h, 50);
    //playlist->setGeometry(percent(w, 5), percent(h, 40), percent(w, 90), playlist_h);
    //playlist->setStyleSheet("background: Plum");

    int list_h = percent(h, 50);
    list->setGeometry(percent(w, 5), percent(h, 40), percent(w, 90), list_h);
    list->setStyleSheet("background: Plum");

    int next_h = percent (h, 5);
    next->setGeometry(percent(w, 85), percent(h, 32.5), percent(w, 10), next_h);
    next->setStyleSheet("background: LightSlateGrey");

    int prev_h = percent (h, 5);
    prev->setGeometry(percent(w, 5), percent(h, 32.5), percent(w, 10), prev_h);
    prev->setStyleSheet("background: LightSlateGrey");
}

void MainWindow::play_pause() {
    if (!play_flag) {
        player->play();
        play->setText("⏸️");
    } else {
        player->pause();
        play->setText("▶️");
    }
    play_flag = !play_flag;
}
void MainWindow::pauseSong() {
    player->stop();
    play_flag = false;
}


MainWindow::~MainWindow()
{
    delete play;
    delete stop;
    delete open;
    delete name;
    delete time;
    delete volume;
    delete dur;
    delete player;
    delete next;
    delete prev;
    //delete playlist;
    delete list;
    delete out;
}
