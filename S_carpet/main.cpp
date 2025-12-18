#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "SierpinskyWidget.h"

int main() {
    Fl_Window win(800, 800, "Carpet");
    SierpinskiWidget carpet(0, 0, 800, 800);
    win.end();
    win.show();
    return Fl::run();
}
