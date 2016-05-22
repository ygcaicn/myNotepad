#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFile>
#include<QFileDialog>
#include<QDir>
#include<QTextStream>
#include<QFontDialog>
#include<QFont>
#include<QColor>
#include<QColorDialog>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/myicon"));
    this->setWindowTitle("Untitled.txt----------PN结记事本");
    QObject::connect(ui->newFile,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    QObject::connect(ui->openFile,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    QObject::connect(ui->saveFile,SIGNAL(triggered()),this,SLOT(saveFileSlot()));
    QObject::connect(ui->saveAsFile,SIGNAL(triggered()),this,SLOT(saveAsFileSlot()));
    QObject::connect(ui->quit,SIGNAL(triggered()),this,SLOT(close()));
    QObject::connect(ui->undoAction,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));
    QObject::connect(ui->redoAction,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));
    QObject::connect(ui->copyAction,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));
    QObject::connect(ui->pastAction,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));
    QObject::connect(ui->cutAction,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));
    QObject::connect(ui->deleteAction,SIGNAL(triggered()),ui->textEdit,SLOT(clear()));
    QObject::connect(ui->allAction,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()));
    QObject::connect(ui->fontAction,SIGNAL(triggered()),this,SLOT(setFontSlot()));
    QObject::connect(ui->colorAction,SIGNAL(triggered()),this,SLOT(setColorSlot()));
    QObject::connect(ui->aboutAction,SIGNAL(triggered()),this,SLOT(aboutSlot()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::newFileSlot()
{
    if(ui->textEdit->document()->isModified())
    {
       // qDebug()<<"内容已经改变";
        QString FileName=QFileDialog::getSaveFileName(this,tr("Save File"),"Untitled.txt",tr("Text(*.txt);;C++ (*.cpp)"));
        if(FileName.isEmpty())
        {
            QMessageBox::information(this,"Error Message","请选择一个文件");
            return;
        }
        else
        {
            QFile *file=new QFile;
            file->setFileName(FileName);
            bool ok=file->open(QIODevice::WriteOnly);
            if(ok)
            {
                QTextStream out(file);
                out<<ui->textEdit->toPlainText();
                file->close();
                 delete file;
            }
            else
            {
                QMessageBox::warning(this,"Error","保存不成功");
            }
        }
    }
    else
    {
        ui->textEdit->clear();
        this->setWindowTitle("Untitled.txt----------PN结记事本");
    }
}
void MainWindow::openFileSlot()
{
    QString FileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
   // qDebug()<<FileName;
    if(FileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","请选择有效路径");
        return;
    }
    else
    {
        QFile *file=new QFile;
        file->setFileName(FileName);
        bool ok=file->open(QIODevice::ReadOnly);
        if(ok)
        {
            QTextStream in(file);
            ui->textEdit->setText(in.readAll());
            file->close();
            delete file;
        }
        else
        {
            QMessageBox::warning(this,"Error","文件打开不成功！"+file->error());

        }
    }
}
void MainWindow::saveFileSlot()
{
    if(saveFileName==NULL)
    {
        saveFileName=QFileDialog::getSaveFileName(this,tr("Save File"),"Untitled.txt",tr("Text(*.txt);;C++ (*.cpp)"));
        if(saveFileName.isEmpty())
        {
            QMessageBox::information(this,"Error Message","请选择一个文件");
        }
    }

    this->setWindowTitle(saveFileName+".txt----------PN结记事本");
    QString FileName=saveFileName;
    QFile *file=new QFile;
    file->setFileName(FileName);
    bool ok=file->open(QIODevice::WriteOnly);
    if(ok)
    {
      QTextStream out(file);
      out<<ui->textEdit->toPlainText();
      file->close();

    }
    else
    {
      QMessageBox::warning(this,"Error","保存不成功");
    }
    delete file;
}
void MainWindow::saveAsFileSlot()
{
    QString FileName=QFileDialog::getSaveFileName(this,tr("Save File"),"Untitled.txt",tr("Text(*.txt);;C++ (*.cpp)"));
    this->saveFileName=FileName;
    if(FileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","未能保存，请选择一个文件");
        return;
    }
    else
    {
        this->setWindowTitle(saveFileName+".txt----------PN结记事本");
        QFile *file=new QFile;
        file->setFileName(FileName);
        bool ok=file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            out<<ui->textEdit->toPlainText();
            file->close();

        }
        else
        {
            QMessageBox::warning(this,"Error","保存不成功");
        }
        delete file;
    }
}
void MainWindow::setFontSlot()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this);
    if (ok) {
        // font is set to the font the user selected
        ui->textEdit->setFont(font);
    } else {
        QMessageBox::information(this,"Error","获取字体失败！");
        // the user canceled the dialog; font is set to the initial
        // value, in this case Times, 12.
    }
}
void MainWindow::setColorSlot()
{
    const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color");
       if (color.isValid())
       {
          ui->textEdit->setTextColor(color);
       }
       else
       {
           QMessageBox::information(this,"Error","颜色设置失败！");
       }
}
void MainWindow::aboutSlot()
{

}
