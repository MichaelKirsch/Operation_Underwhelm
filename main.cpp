#include "ImprovedGui.h"

using namespace MBGL;

Logger Logger::_instance;

class car
{
public:
    car(float x, float y,GUI::GUI* gui)
    {
        b = new GUI::Button(gui,{x,y,0.1,0.1});
    }

    void update()
    {
        if(b->mouse_is_over)
            b->private_outline.x*=1.01;
    }

    ~car()
    {
        delete b;
    }

private:
    GUI::Button* b;
};


int main() {
    WindowManager mgr;
    mgr.init();
    GUI::ColorPalette palette;
    palette.loadFromFile("data/ColorSchemes/Example.mk_color");
    GUI::GUI gui(mgr,palette);

    GUI::Unit test_unit(&gui,{0.1,0.1,0.3,0.3});

    GUI::Button test_button(&test_unit,{0.1,0.1,0.3,0.3});
    GUI::Button ttest_button(&test_unit,{0.5,0.1,0.3,0.3});
    GUI::Button test_button2(&gui,{0.5,0.1,0.3,0.3});

    mgr.getWindow().setFramerateLimit(100);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::list<car*> wid;
    while(mgr.getWindow().isOpen())
    {
        gui.update(mgr.getMouse());
        mgr.clearWindow();
        sf::Event e;
        if(test_button.mouse_is_over && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            test_unit.moveable = true;
        }

        if(ttest_button.mouse_is_over && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            test_unit.moveable = false;
        }

        if(test_button2.mouse_is_over && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(!wid.empty())
            {
                delete wid.back();
                wid.pop_back();
            }
        }

        for(auto& d:wid)
            d->update();

        while(mgr.getWindow().pollEvent(e))
        {
            if(e.type==sf::Event::Closed)
                mgr.getWindow().close();
        }


        gui.render();
        mgr.swapBuffer();
    }
    return 0;
}