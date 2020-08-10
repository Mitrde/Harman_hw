#include "editdialog.h"
#include "linedrawer.h"
#include <QLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

EditDialog::EditDialog(QWidget* pwgt)
    :QDialog(pwgt, Qt::WindowTitleHint )
{
    QVBoxLayout *pvbl = new QVBoxLayout(this);
    QHBoxLayout *phbl = new QHBoxLayout(this);
    pspb = new QSpinBox(this);
    QLabel      *plbl = new QLabel("Number of points: ", this);
    QPushButton *pbtn = new QPushButton("OK",this);
    pspb->setRange(1,100);
    phbl->addWidget(plbl);
    phbl->addWidget(pspb);
    pvbl->addLayout(phbl);
    pvbl->addWidget(pbtn);
    setLayout(pvbl);

    connect(pbtn, SIGNAL(clicked()), SLOT(buttonPressed()));
    connect(this, SIGNAL(numChanged(size_t)),pwgt,SIGNAL(numChanged(size_t)));
}

void EditDialog::buttonPressed()
{
    emit numChanged(pspb->value());    
    delete this;
}
