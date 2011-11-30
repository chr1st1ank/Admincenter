#include "InfoDialog.hpp"

#include <QDebug>
#include <QString>

#include <fstream>
#include <string>

InfoDialog::InfoDialog(QWidget * parent) : QMessageBox(parent)
{
    setWindowTitle(QObject::tr("Admincenter"));

    std::ifstream inFile("README.txt", std::ios::in);
    if (!inFile)
    {
        setText("https://github.com/wirdbald/Admincenter");
        setInformativeText("See README.txt for details.");
    }else{
        std::string txt = "";
        char c[128];
        do
        {
            inFile.read(c,128);
            txt += std::string(c).substr(0,inFile.gcount());
        }
        while (inFile);
        inFile.close();
        setText(QString::fromLocal8Bit(txt.c_str()));
    }
}

InfoDialog::~InfoDialog()
{
    qDebug() << "Deleting InfoDialog";
}
