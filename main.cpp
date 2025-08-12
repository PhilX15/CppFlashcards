#include "session.h"
#include "menu.h"

int main() {
    srand(time(nullptr));
    
    Session session;
    Menu menu;

    menu.display_menu();
    option_t option = menu.get_option();
    switch (option) {
        case LEARNING:
            session.guessing();
            break;
        case LIST:
            break;
        case MODIFY:
            break;
        case EXIT:
            return 0;
    }

    return 0;
}