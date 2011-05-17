#include "mouseController.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include <iostream>

#include "clickButton.h"

#ifdef UNIX
    #include <X11/Xlib.h>
#elif WIN32
    #include <windows.h>
    #define IS_LEFT_PRESSED \
        ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && ! GetSystemMetrics(SM_SWAPBUTTON)) \
        || ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && GetSystemMetrics(SM_SWAPBUTTON))
    #define IS_RIGHT_PRESSED \
        ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) && ! GetSystemMetrics(SM_SWAPBUTTON)) \
        || ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && GetSystemMetrics(SM_SWAPBUTTON))
#endif

#include "mouse.h"

using FakeInput::Mouse;

MouseController::MouseController():
    QDialog(0)
{
    QVBoxLayout* vbox = new QVBoxLayout();

    QLabel* instructions = new QLabel(
            "Move mouse with arrow keys\nLeft click - x\nRight click - c",
            this);

    ClickButton* clickButton = new ClickButton(this);
    clickButton->setFocusPolicy(Qt::NoFocus);
    QPushButton* quitButton = new QPushButton("Close", this);
    quitButton->setFocusPolicy(Qt::NoFocus);

    QLabel* xLabel = new QLabel("x: ", this);
    QLabel* yLabel = new QLabel("y: ", this);
    xPos_ = new QSpinBox(this);
    xPos_->setFocusPolicy(Qt::NoFocus);
    xPos_->setSingleStep(50);
    xPos_->setMaximum(10000);
    yPos_ = new QSpinBox(this);
    yPos_->setFocusPolicy(Qt::NoFocus);
    yPos_->setSingleStep(50);
    yPos_->setMaximum(10000);
    QPushButton* setMousePosButton = new QPushButton("Set mouse position", this);
    setMousePosButton->setFocusPolicy(Qt::NoFocus);
    setMousePosButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    QSlider* slider = new QSlider(Qt::Vertical, this);
    slider->setFocusPolicy(Qt::NoFocus);
    slider->setValue(50);

    QGridLayout* grid = new QGridLayout();
    grid->addWidget(xLabel, 0, 0);
    grid->addWidget(xPos_, 0, 1);
    grid->addWidget(yLabel, 1, 0);
    grid->addWidget(yPos_, 1, 1);
    grid->addWidget(setMousePosButton, 0, 2, 2, 1);
    grid->addWidget(clickButton, 2, 0, 1, 3);
    grid->addWidget(quitButton, 3, 0, 1, 3);
    grid->addWidget(slider, 0, 3, 4, 1);

    vbox->addWidget(instructions);
    vbox->addLayout(grid);
    //vbox->addWidget(clickButton);
    //vbox->addWidget(quitButton);

    setLayout(vbox);

    connect(setMousePosButton, SIGNAL(clicked()), this, SLOT(setMousePos()));
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MouseController::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Left:
            FakeInput::Mouse::move(-5, 0);
            break;
        case Qt::Key_Right:
            FakeInput::Mouse::move(5, 0);
            break;
        case Qt::Key_Up:
            FakeInput::Mouse::move(0, -5);
            break;
        case Qt::Key_Down:
            FakeInput::Mouse::move(0, 5);
            break;
        case Qt::Key_X:
            FakeInput::Mouse::pressButton(FakeInput::Mouse_Left);
            break;
        case Qt::Key_C:
            FakeInput::Mouse::pressButton(FakeInput::Mouse_Right);
            break;
        case Qt::Key_Q:
            FakeInput::Mouse::wheelUp();
            break;
        case Qt::Key_A:
            FakeInput::Mouse::wheelDown();
            break;
        default:
            break;
    }
}

void MouseController::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_X:
            FakeInput::Mouse::releaseButton(FakeInput::Mouse_Left);
            break;
        case Qt::Key_C:
            FakeInput::Mouse::releaseButton(FakeInput::Mouse_Right);
            break;
        default:
            break;
    }
}

void MouseController::setMousePos()
{
    if(xPos_->text() != "" && yPos_->text() != "")
    {
        int x = xPos_->text().toInt();
        int y = yPos_->text().toInt();

        FakeInput::Mouse::moveTo(x, y);
    }
}

#ifdef UNIX
bool MouseController::x11Event(XEvent* event)
{
    if(event->type == FocusOut)
    {
        FakeInput::Mouse::releaseButton(FakeInput::Mouse_Left);
        FakeInput::Mouse::releaseButton(FakeInput::Mouse_Right);
    }

    return false;
}
#elif WIN32
bool MouseController::winEvent(MSG* message, long* result)
{
    if(message->message == WM_KILLFOCUS)
    {
        if(IS_LEFT_PRESSED)
        {
            std::cout << "left" << std::endl;
            FakeInput::Mouse::releaseButton(FakeInput::Mouse_Left);
        }
        else if(IS_RIGHT_PRESSED)
        {
            std::cout << "right" << std::endl;
            FakeInput::Mouse::releaseButton(FakeInput::Mouse_Right);
        }
    }

    return false;
}
#endif
