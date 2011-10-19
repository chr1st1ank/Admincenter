#ifndef BACKBUTTON_HPP
#define BACKBUTTON_HPP

#include "EmptyButton.hpp"

class BackButton : public EmptyButton
{
    Q_OBJECT

    public:
        BackButton(const QIcon& icon, const QString& text, QWidget* parent = 0);

    public slots:
        void execute();
};

#endif // BACKBUTTON_HPP
