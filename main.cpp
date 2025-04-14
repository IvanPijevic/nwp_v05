#include <tchar.h>
#include <list>

#include "nwpwin.h"


class main_window : public vsite::nwp::window
{
private:
    std::list<POINT> points;

protected:
    void on_paint(HDC hdc) override
    {
        if (points.size() >= 2) 
        {
            auto it = points.begin();
            MoveToEx(hdc, it->x, it->y, nullptr);
            ++it;

            while (it != points.end()) 
            {
                LineTo(hdc, it->x, it->y);
                ++it;
            }
        }
    }

    void on_left_button_down(POINT p) override
    {
        points.emplace_back(p);
        InvalidateRect(*this, nullptr, TRUE);
    }

    void on_key_down(int vk) override
    {
        bool changed = false;

        switch (vk) 
        {
        case VK_ESCAPE:
            if (!points.empty()) 
            {
                points.clear();
                changed = true;
            }
            break;

        case VK_BACK:
            if (!points.empty()) 
            {
                points.pop_back();
                changed = true;
            }
            break;
        }
        if (changed) 
        {
            InvalidateRect(*this, nullptr, TRUE);
        }
    }

    void on_destroy() override
    {
        ::PostQuitMessage(0);
    }
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    vsite::nwp::application app;
    main_window w;
    w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5");
    return app.run();
}