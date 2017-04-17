#include "dialog.h"
#include "ui_dialog.h"
#include <mytile.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startScene() {
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    timer = new QTimer(this);
    timer->setInterval(8);
    timer->start();
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));

    //QRectF rect(-100,-100,200,200);
    //QPen rectpen(Qt::red);

    //MyTile *t = new MyTile(0,0,200,200);
    //MyTile *t2 = new MyTile(200,200,210,210);

    //scene->addItem(t);
    //scene->addItem(t2);
}

void Dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dialog::on_addTileButton_clicked()
{
    //tiles.push_back(MyTile(0,0,100,100));
    //scene->addItem( &tiles.last() );
    scene->addItem(new MyTile(0,0,100,100));
}
