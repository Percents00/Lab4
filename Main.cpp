#include <iostream>

#include "Tests.h"
#include "ConsoleUI.h"

int main() {
    startTests();
    ConsoleUI<int> ui;
    ui.run();
    return 0;
}