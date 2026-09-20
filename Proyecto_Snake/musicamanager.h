#ifndef MUSICAMANAGER_H
#define MUSICAMANAGER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>

class MusicaManager {
public:
    static MusicaManager& instance();

    void playMusicaJuego(const QString &fileName = "Musica_Juego.wav");
    void playMusicaNiveles(const QString &fileName = "Musica_Niveles.wav");
    void stopAll();

    //control de volumen (rango 0.0 a 1.0)
    void setVolumenGlobal(float volumen);
    void setVolumenNiveles(float volumen);
    float getVolumenGlobal() const;
    float getVolumenNiveles() const;

    //control auxiliar para sliders de 0 a 100
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