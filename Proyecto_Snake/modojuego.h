#ifndef MODOJUEGO_H
#define MODOJUEGO_H

#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QString>

class ModoJuego : public QWidget {
    Q_OBJECT
public:
    explicit ModoJuego(QWidget *parent = nullptr);
    ~ModoJuego();

    void setMenuAnterior(QWidget *menu);
    void setUsuarioActual(const QString &usuario);

private slots:
    void onModoHistoriaClicked();
    void onModoLibreClicked();
    void onVolverClicked();

private:
    QPixmap imgFondo;
    QPushButton *btnModoHistoria;
    QPushButton *btnModoLibre;
    QPushButton *btnVolver;
    QWidget *menuAnterior;
    QString usuarioActual;

    void paintEvent(QPaintEvent *event) override;
};

#endif // MODOJUEGO_H