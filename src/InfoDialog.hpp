#ifndef INFODIALOG_HPP
#define INFODIALOG_HPP

#include <QMessageBox>

class InfoDialog : public QMessageBox
{
    public:
        InfoDialog(QWidget * parent = 0);
        ~InfoDialog();
    protected:
    private:
};

#endif // INFODIALOG_HPP
