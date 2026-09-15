#ifndef RANKING_H
#define RANKING_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>

class Ranking : public QWidget
{
    Q_OBJECT
public:
    explicit Ranking(QWidget *parent = nullptr);

    explicit Ranking(QWidget *menuPrincipal, QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QWidget *menuPrincipal;
    QPixmap fondo;

    QTableWidget *listaGlobal;
    QTableWidget *listaNiveles;

    QLabel *marcosListas;

    QPushButton *btnVolver;

    void configurarListaGlobal();
    void configurarListaNiveles();

    void cargarDatosGlobal();
    void cargarDatosNiveles();

private slots:
    void volverAlMenu();
};

#endif // RANKING_H
