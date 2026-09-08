/*#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class LoginWindow : public QMainWindow {
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onEntrarClicked();
    void onRegistrarClicked(const QPoint &pos); // Para detectar el clic en el texto inferior

private:
    QLabel *labelFondo;
    QLabel *labelCampoUsuario;
    QLabel *labelCampoPassword;
    QLineEdit *txtUsuario;
    QLineEdit *txtPassword;
    QPushButton *btnEntrar;
    QLabel *lblRegistrarse;
};

#endif // LOGINWINDOW_H*/