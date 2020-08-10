#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QSpinBox>

class EditDialog :public QDialog
{
    Q_OBJECT
public:
    EditDialog(QWidget* pwgt = 0);
signals:
    void numChanged(size_t);
public slots:
    void buttonPressed();
private:
    QSpinBox *pspb;

};

#endif // EDITDIALOG_H
