// #ifndef INSTRUCCIONESGENERALES_H
// #define INSTRUCCIONESGENERALES_H

// #include <QMainWindow>
// #include <QLabel>
// #include <QPushButton>

// class InstruccionesGenerales : public QMainWindow {
//     Q_OBJECT

// public:
//     explicit InstruccionesGenerales(QWidget *parent = nullptr, const QString &usuario = "");
//     QString usuarioActual;
//     ~InstruccionesGenerales();

// private slots:
//     void onVolverMenuClicked();

// private:
//     QLabel *labelFondo;
//     QPushButton *btnVolver;
// };

// #endif // INSTRUCCIONESGENERALES_H

#ifndef INSTRUCCIONESGENERALES_H
#define INSTRUCCIONESGENERALES_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>

class InstruccionesGenerales : public QMainWindow {
    Q_OBJECT

public:
    explicit InstruccionesGenerales(QWidget *parent = nullptr);
    ~InstruccionesGenerales();

    void setUsuario(const QString &usuario);

private slots:
    void onVolverMenuClicked();

private:
    QLabel *labelFondo;
    QPushButton *btnVolver;
    QString usuarioActual;
};

#endif // INSTRUCCIONESGENERALES_H