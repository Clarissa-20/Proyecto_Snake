#ifndef FILTROVENTANAS_H
#define FILTROVENTANAS_H

#include <QObject>
#include <QEvent>
class FiltroVentanas : public QObject
{
public:
    explicit FiltroVentanas(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // FILTROVENTANAS_H
