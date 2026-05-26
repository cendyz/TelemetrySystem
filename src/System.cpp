#include "System.h"

System::System() {
    run();
}

void System::run() {
    sysUI = std::make_unique<SystemUI>();
}
