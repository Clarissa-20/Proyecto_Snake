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

    explicit Ranking(QWidget *menuPrincipal, QWidget *parent, const QString &usuario="");

    void setUsuarioActual(const QString &usuario)
    {
        usuarioActual=usuario;
        cargarDatosNiveles();
    }
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QWidget *menuPrincipal;
    QPixmap fondo;
    QString usuarioActual;
    QTableWidget *listaGlobal;
    QTableWidget *listaNiveles;

    QLabel *marcosListas;

    QPushButton *btnVolver;

    void configurarListaGlobal();
    void configurarListaNiveles();

    void cargarDatosGlobal();
    void cargarDatosNiveles();


    QString carpetaPartidaUsuarios() const;
    void agregarFilaEncabezado(int fila, const QString &texto);
    void agregarFilaPartida(int fila, int nivel, int rojas, int doradas);
private slots:
    void volverAlMenu();
};

#endif // RANKING_H
