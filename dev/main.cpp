#include <stdio.h>                  // for getchar
#include <ftxui/dom/elements.hpp>   // for filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <memory>                   // for allocator
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Radiobox, Horizontal, Menu, Renderer, Tab
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/node.hpp"      // for Render
#include "ftxui/screen/color.hpp"  // for ftxui
 
int main(int argc, const char* argv[]) {
    using namespace ftxui;
    std::vector<std::string> tab_values{
      "ch1",
      "ch2",
      "ch3",
      "ch4",
      "ch5"
  };
    int tab_selected = 0;
    auto tab_menu = Menu(&tab_values, &tab_selected);
        std::vector<std::string> tab_1_entries{
      "arr",
      "scene",
      "pattern",
    };
    int tab_1_selected = 0;
    std::vector<std::string> tab_2_entries{
      "arr",
      "scene",
      "pattern",
    };
    int tab_2_selected = 0;
 
    std::vector<std::string> tab_3_entries{
      "arr",
      "scene",
      "pattern",
    };
    int tab_3_selected = 0;
  
    //start drawing!
    auto tab_container = Container::Tab(
    {
        Radiobox(&tab_1_entries, &tab_1_selected),
        Radiobox(&tab_2_entries, &tab_2_selected),
        Radiobox(&tab_3_entries, &tab_3_selected),
    },
      &tab_selected);

    //cant construct Container type with a vbox?
    auto testColumn = vbox({
        text("hello"),
        text("text!") | bold | color(Color::Blue)
    });
    auto container = Container::Horizontal({
        tab_menu,
        tab_container,
    });

    auto renderer = Renderer(container, [&]
        { return hbox({
            tab_menu->Render(),
            separator(),
            tab_container->Render(),
        }) |
        border; });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
    getchar();
 
    return 0;
}
