#include "gui_menu.h"

void GuiMenu::create()
{
    _gpu->fill_rect(x,y,+len,y+hight,_gpu->back_color);
    for(int i = 0; i < max; i++)
    {
        if((i + index) >= current_menu->count)
            break;
        _gpu->printf(x,y+i*25,"%s",current_menu->items[i + index].title);
    }
    _gpu->printf(x - 10,y,">");

}
void GuiMenu::set_select(bool state)
{
}

void GuiMenu::update_item_index()
{
    
    _gpu->fill_rect(x,y,+len,y+hight,_gpu->back_color);
    for(int i = 0; i < max; i++)
    {
        if((i + index) >= current_menu->count)
            break;
        _gpu->printf(x,y+i*25,"%s",current_menu->items[i + index].title);
    }
}
