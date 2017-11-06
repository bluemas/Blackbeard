#include "network\NetworkManager.h"
#include "main\MainController.h"

int main() {
    MainController::start();
    NetworkManager::start();
}