
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <unistd.h>

int min(int a, int b)
{
    if (a>b)
    {
        return b;
    }
    else 
    {
        return a;
    }
}

class SierpinskiWidget : public Fl_Widget {
public:
    SierpinskiWidget(int X, int Y, int W, int H)
        : Fl_Widget(X, Y, W, H), depth_(50), margin_(10) {}

    void setDepth(int d) { depth_ = d; redraw(); }
    int depth() const { return depth_; }

protected:
    void draw() override {
        fl_color(FL_WHITE);
        fl_rectf(x(), y(), w(), h());

        int side = min(w(), h()) - 2 * margin_;
        int startX = x() + (w() - side) / 2;
        int startY = y() + (h() - side) / 2;

        fl_color(FL_BLACK);
        drawCarpet(startX, startY, side, depth_);
    }

private:
    int depth_;
    int margin_;

    void drawCarpet(int x, int y, int size, int depth) {
        if (depth == 0 || size <= 1) {
            fl_rectf(x, y, size, size);
            return;
        }

        usleep(100);
        

        int child = size / 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == 1 && j == 1) continue;
                drawCarpet(x + i * child, y + j * child, child, depth - 1);
            }
        }
    }
};
