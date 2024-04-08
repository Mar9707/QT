#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QLabel>
#include <QBoxLayout>
#include <QObject>
#include <QSet>

class Playlist : public QLabel
{
    Q_OBJECT
public:
    explicit Playlist(QWidget *parent = nullptr);
    void append_songs(QStringList& songs);
    void init_song(qint64);
    void set_next();
    void set_prev();
    QString getCurrentSong();
    ~Playlist();

private:
    QVBoxLayout *lay;
    QSet<QString> set;
    QStringList plist;
    QString cursong;
    qint64 ind {0};
    qint64 curindex = 0;

signals:
    void songIsReady();
};

#endif // PLAYLIST_H
