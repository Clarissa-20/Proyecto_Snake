#ifndef INICIOSCREEN_H
#define INICIOSCREEN_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class InicioScreen : public QMainWindow {
    Q_OBJECT

public:
    InicioScreen(QWidget *parent = nullptr);
    ~InicioScreen();

    void setUsuario(const QString &usuario);

private slots:
    void onIniciarAventuraClicked();
    void regresar();

private:
    QLabel *labelFondo;
    QPushButton *btnIniciar;
    QPushButton *btnRegresar;
    QString usuarioActual;
};

#endif // INICIOSCREEN_H