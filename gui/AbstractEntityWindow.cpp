#include "AbstractEntityWindow.h"
#include <FL/fl_ask.H>

template<typename T>
AbstractEntityWindow<T>::AbstractEntityWindow(int w, int h, const char *title, void *eventInvoker,
                                                AbstractEntityWindow::Type type, T entity):Fl_Window(w, h, title),
                                                eventInvoker(eventInvoker), type(type), entity(entity) {

    int btnWith = 140;
    int btnHeight = 60;

    int btn_y = h - btnHeight - 10 ;
    int btn_cancel_x = 10;
    int btn_create_x = w - btnWith - 10;

    this->btnCancel = new Fl_Button(btn_cancel_x, btn_y, btnWith, btnHeight, "CANCEL");
    btnCancel->callback(AbstractEntityWindow<T>::cancel, this);



    if (this->type == New) {
        this->btnCreate = new Fl_Button(btn_create_x, btn_y, btnWith, btnHeight, "CREATE");
    } else if (this->type == Replace) {
        this->btnCreate = new Fl_Button(btn_create_x, btn_y, btnWith, btnHeight, "REPLACE");
        //this->fillOutInputs();
    }

    btnCreate->callback(AbstractEntityWindow<T>::create, this);

    this->set_modal();
}

template<typename T>
void AbstractEntityWindow<T>::cancel(Fl_Widget *widget, void *data) {
    auto abstractEntityWindow = (AbstractEntityWindow<T>*) data;
    delete abstractEntityWindow;
}

template<typename T>
void AbstractEntityWindow<T>::create(Fl_Widget *widget, void *data) {
    auto abstractEntityWindow = (AbstractEntityWindow<T>*) data;
    try {
        abstractEntityWindow->inputValidationCheck();
        if (abstractEntityWindow->type == New) {
            abstractEntityWindow->createEventHandler();
        }
        else if (abstractEntityWindow->type == Replace){
            abstractEntityWindow->replaceEventHandler();
        }
    } catch (logic_error error) {
        fl_alert(error.what());
        return;
    }
}

template class AbstractEntityWindow<Business*>;