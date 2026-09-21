#ifndef MANUALUSUARIO_H
#define MANUALUSUARIO_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>

class ManualUsuario : public QMainWindow {
    Q_OBJECT

public:
    explicit ManualUsuario(QWidget *parent = nullptr);
    ~ManualUsuario();

    void setUsuario(const QString &usuario);

private slots:
    void onVolverMenuClicked();

private:
    QLabel *labelFondo;
    QPushButton *btnVolver;
    QString usuarioActual;
};

#endif // MANUALUSUARIO_H