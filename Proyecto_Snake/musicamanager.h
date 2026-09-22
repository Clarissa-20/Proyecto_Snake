#ifndef MUSICAMANAGER_H
#define MUSICAMANAGER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>

class MusicaManager {
public:
    static MusicaManager& instance();

    void playMusicaJuego(const QString &fileName = "Musica_Juego.mp3");
    void playMusicaNiveles(const QString &fileName = "Musica_Niveles.mp3");
    void stopAll();

    void setVolumenGlobal(float volumen);
    void setVolumenNiveles(float volumen);
    float getVolumenGlobal() const;
    float getVolumenNiveles() const;

    void setVolumenGlobalPorcentaje(int porcentaje);
    void setVolumenNivelesPorcentaje(int porcentaje);

private:
    MusicaManager();
    ~MusicaManager();
    QMediaPlayer *globalPlayer;
    QAudioOutput *globalAudio;
    QMediaPlayer *levelPlayer;
    QAudioOutput *levelAudio;
};

#endif // MUSICAMANAGER_H