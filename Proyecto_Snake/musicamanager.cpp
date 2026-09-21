#include "musicamanager.h"
#include <QCoreApplication>
#include <QtGlobal>

MusicaManager& MusicaManager::instance() {
    static MusicaManager instance;
    return instance;
}

// MusicaManager::MusicaManager() {
//     globalPlayer = new QMediaPlayer();
//     globalAudio = new QAudioOutput();
//     globalPlayer->setAudioOutput(globalAudio);
//     globalAudio->setVolume(0.4);

//     levelPlayer = new QMediaPlayer();
//     levelAudio = new QAudioOutput();
//     levelPlayer->setAudioOutput(levelAudio);
//     levelAudio->setVolume(0.5);

//     QObject::connect(globalPlayer, &QMediaPlayer::playbackStateChanged, [=](QMediaPlayer::PlaybackState state){
//         if(state == QMediaPlayer::StoppedState) globalPlayer->play();
//     });

//     QObject::connect(levelPlayer, &QMediaPlayer::playbackStateChanged, [=](QMediaPlayer::PlaybackState state){
//         if(state == QMediaPlayer::StoppedState) levelPlayer->play();
//     });
// }

MusicaManager::MusicaManager() {
    globalPlayer = new QMediaPlayer();
    globalAudio = new QAudioOutput();
    globalPlayer->setAudioOutput(globalAudio);
    globalAudio->setVolume(0.4);
    globalPlayer->setLoops(QMediaPlayer::Infinite);

    levelPlayer = new QMediaPlayer();
    levelAudio = new QAudioOutput();
    levelPlayer->setAudioOutput(levelAudio);
    levelAudio->setVolume(0.5);
    levelPlayer->setLoops(QMediaPlayer::Infinite);
}

MusicaManager::~MusicaManager() {
    delete globalPlayer; delete globalAudio;
    delete levelPlayer; delete levelAudio;
}

void MusicaManager::playMusicaJuego(const QString &fileName) {
    if (levelPlayer->isPlaying()) levelPlayer->stop();
    QString fullPath = QCoreApplication::applicationDirPath() + "/musica/" + fileName;
    globalPlayer->setSource(QUrl::fromLocalFile(fullPath));
    globalPlayer->play();
}

void MusicaManager::playMusicaNiveles(const QString &fileName) {
    if (globalPlayer->isPlaying()) globalPlayer->stop();
    QString fullPath = QCoreApplication::applicationDirPath() + "/musica/" + fileName;
    levelPlayer->setSource(QUrl::fromLocalFile(fullPath));
    levelPlayer->play();
}

void MusicaManager::stopAll() {
    globalPlayer->stop();
    levelPlayer->stop();
}

void MusicaManager::setVolumenGlobal(float volumen) {
    volumen = qBound(0.0f, volumen, 1.0f);
    if (globalAudio) globalAudio->setVolume(volumen);
}

void MusicaManager::setVolumenNiveles(float volumen) {
    volumen = qBound(0.0f, volumen, 1.0f);
    if (levelAudio) levelAudio->setVolume(volumen);
}

float MusicaManager::getVolumenGlobal() const {
    return globalAudio ? globalAudio->volume() : 0.0f;
}

float MusicaManager::getVolumenNiveles() const {
    return levelAudio ? levelAudio->volume() : 0.0f;
}

void MusicaManager::setVolumenGlobalPorcentaje(int porcentaje) {
    setVolumenGlobal(qBound(0, porcentaje, 100) / 100.0f);
}

void MusicaManager::setVolumenNivelesPorcentaje(int porcentaje) {
    setVolumenNiveles(qBound(0, porcentaje, 100) / 100.0f);
}