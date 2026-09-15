#ifndef INSTRUCCIONESGENERALES_H
#define INSTRUCCIONESGENERALES_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class InstruccionesGenerales : public QMainWindow {
    Q_OBJECT

public:
    explicit InstruccionesGenerales(QWidget *parent = nullptr);
    ~InstruccionesGenerales();

private slots:
    void onVolverMenuClicked();

private:
    QLabel *labelFondo;
    QPushButton *btnVolver;
};

#endif // INSTRUCCIONESGENERALES_H