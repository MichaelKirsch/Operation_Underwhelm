#include "ImprovedGui.h"

using namespace MBGL;

Logger Logger::_instance;


int main() {
    WindowManager mgr;
    mgr.init();
    GUI::ColorPalette palette;
    palette.loadFromFile("data/ColorSchemes/Example.mk_color");
    GUI::GUI gui(mgr,palette);

    auto* t = gui.generateNewButton({0.5,0.2,0.1,0.1});
    auto* test_unit = gui.generateNewUnit({0.1,0.1,0.2,0.2});
    auto* button_in_unit = gui.generateNewButton(test_unit,{0.1f,0.1f,0.35f,0.4});
    auto* sec_button_in_unit = gui.generateNewButton(test_unit,{0.2f+0.35f,0.1,0.35,0.4});
    auto* third_button_in_unit = gui.generateNewButton(test_unit,{0.2f+0.35f,0.6,0.35,0.3});
    auto* fourth_button_in_unit = gui.generateNewButton(test_unit,{0.1f,0.6,0.35,0.3});
    fourth_button_in_unit->setPrimaryColor(GUI::Success);
    third_button_in_unit->setPrimaryColor(GUI::Warning);




    mgr.getWindow().setFramerateLimit(60);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::vector<GUI::Widget*> wid;
    while(mgr.getWindow().isOpen())
    {
        gui.update(mgr.getMouse());
        mgr.clearWindow();
        sf::Event e;
        {

        }

        while(mgr.getWindow().pollEvent(e))
        {
            if(e.type==sf::Event::Closed)
                mgr.getWindow().close();
        }

        if(fourth_button_in_unit->is_clicked)
            fourth_button_in_unit->please_delete = true;

        if(test_unit->mouse_is_over)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                test_unit->global_outline.width = test_unit->global_outline.width*0.9;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                test_unit->global_outline.width = test_unit->global_outline.width*1.1;
        }


        if(button_in_unit->is_clicked)
            mgr.setClearColor({0.478, 0.478, 0.478,1.0});

        if(sec_button_in_unit->is_clicked)
            mgr.setClearColor({0.172, 0.313, 0.686,1.0});

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&&test_unit->mouse_is_over)
        {
            auto pos = gui.pixelToPercent(sf::Mouse::getPosition(mgr.getWindow()));
            test_unit->global_outline.x = pos.x-test_unit->global_outline.width/2;
            test_unit->global_outline.y = pos.y-test_unit->global_outline.height/2;
        }
        if(third_button_in_unit->is_clicked)
            mgr.getWindow().close();

        if(t->is_clicked)
        {
            auto x = 0.01f*((rand()%100));
            auto y = 0.01f*((rand()%100));
            auto s = gui.generateNewUnit({x,y,0.2,0.2});
            gui.generateNewButton(s,{x,y,0.2,0.2});
            wid.emplace_back(s);
        }
        gui.render();
        mgr.swapBuffer();
    }
    return 0;
}