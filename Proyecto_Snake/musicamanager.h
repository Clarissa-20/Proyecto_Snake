#ifndef MUSICAMANGER_H
#define MUSICAMANGER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>

class MusicaManger {
public:
    static MusicaManger& instance();

    void playMusicaJuego(const QString &fileName = "Musica_Juego.wav");
    void playMusicaNiveles(const QString &fileName = "Musica_Niveles.wav");
    void stopAll();

private:
    MusicaManger();
    ~MusicaManger();
    QMediaPlayer *globalPlayer;
    QAudioOutput *globalAudio;
    QMediaPlayer *levelPlayer;
    QAudioOutput *levelAudio;
};

#endif // MUSICAMANGER_H