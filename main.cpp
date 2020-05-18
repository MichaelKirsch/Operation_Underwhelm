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
    sf::Sound sound;
    sf::SoundBuffer t;
    t.loadFromFile("data/music/kenney_uiaudio/Audio/switch15.ogg");
    WindowManager mgr;
    sound.setBuffer(t);
    mgr.init();
    GUI::ColorPalette palette;
    palette.loadFromFile("data/ColorSchemes/Example.mk_color");
    GUI::GUI gui(mgr,palette);

    GUI::Unit test_unit(&gui,{0.1,0.1,0.3,0.3});
    GUI::Button test_button(&test_unit,{0.1,0.1,0.25,0.25});
    GUI::Button ttest_button(&test_unit,{0.5,0.1,0.25,0.25});
    GUI::FreeSlider slider1(&test_unit,{0.1,0.4,0.6,0.15});
    GUI::FreeSlider slider2(&test_unit,{0.1,0.6,0.6,0.15});
    GUI::FreeSlider slider3(&test_unit,{0.1,0.8,0.6,0.15});
    GUI::FreeSlider soundslider(&test_unit,{0.75,0.8,0.2,0.075});
    GUI::Button test_button2(&test_unit,{0.75,0.5,0.2,0.2});

    mgr.getWindow().setFramerateLimit(100);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::list<car*> wid;
    while(mgr.getWindow().isOpen())
    {
        test_unit.setTransparency(soundslider.getValue());
        sound.setVolume(soundslider.getValue()*100.f);
        gui.update(mgr.getMouse());
        mgr.clearWindow();
        sf::Event e;
        if(test_button.mouse_is_over && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            test_unit.moveable = true;
            sound.stop();
            sound.play();
            test_unit.setSecondaryColor(GUI::Success);
        }

        if(ttest_button.mouse_is_over && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            test_unit.moveable = false;
            sound.stop();
            sound.play();
            test_unit.setSecondaryColor(GUI::Warning);
        }

        if(test_button2.mouse_is_over && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mgr.getWindow().close();
        }

        test_button2.setPrimaryColor({slider1.getValue(),slider2.getValue(),slider3.getValue()});

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