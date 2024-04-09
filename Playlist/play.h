#ifndef PLAY_H
#define PLAY_H

#include <QListWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QObject>
#include <QSet>
#include <QFileInfo>

class Play : public QListWidget
{
    Q_OBJECT
public:
    Play();
    explicit Play(QWidget *parent = nullptr);
    void append_songs(QStringList& s);
    void set_next();
    void set_prev();
    QString cursong();

private:
    QStringList plist;
    qint64 currindex;
    QSet <QString> set;
};

#endif // PLAY_H
