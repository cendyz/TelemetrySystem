#pragma once
#include "SystemUI.h"

class System {
public:
    System();
    void run();

private:
    std::unique_ptr<SystemUI> sysUI;
};
