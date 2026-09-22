#ifndef MIPERFIL_H
#define MIPERFIL_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>
#include <QShowEvent>

class MiPerfil : public QWidget {
    Q_OBJECT
private:
    QWidget *menuAnterior;
    QString usuarioActual;

    QPushButton *btnVolver;

    QPixmap imgFondoPerfil;
    QPixmap imgAvatarUser;
    QPixmap imgAvatarSkin;

    QFrame *frameInfoUsuario;
    QLabel *lblAvatarMarco;
    QLabel *lblNombre;
    QLabel *lblPuntaje;
    QLabel *lblGemas;

    QFrame *frameBloqueNiveles;
    QFrame *frameBloqueInsignias;
    QFrame *frameBloqueMapa;
    QFrame *frameBloqueSkin;

    QLabel *lblSkinImgBlock;
    QLabel *lblSkinNameBlock;
    QLabel *lblMapaStatus;
    QLabel *lblInsStatus;

    QLabel *lblNivelStatus[3];
    QLabel *lblInsImg[3];
    QLabel *lblMapaImg[3];

    int nivelesProgreso[3] = {0, 0, 0};
    bool insigniasDesbloqueadas[3] = {false, false, false};
    int pedazosMapaRecolectados = 0; // 0 a 3

    QPixmap makeGrayscale(const QPixmap &pix) const;
    void actualizarBloquesVisuales();

public:
    explicit MiPerfil(QWidget *parent = nullptr);
    ~MiPerfil() override;

    void setMenuAnterior(QWidget *menu);
    void setUsuarioActual(const QString &usuario);
    void cargarDatosUsuario();
    void setProgresoDatos(int n1, int n2, int n3, bool ins1, bool ins2, bool ins3, int mapPieces);

    void setUsuario(const QString &usuario);

protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void onVolverClicked();
};

#endif // MIPERFIL_H