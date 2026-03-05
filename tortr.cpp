#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

bool exists(string cmd) {
    string check = "which " + cmd + " > /dev/null 2>&1";
    return system(check.c_str()) == 0;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "tortr - universal linux package installer\n";
        cout << "usage:\n";
        cout << " tortr install <package>\n";
        cout << " tortr search <package>\n";
        cout << " tortr update\n";
        cout << " tortr setup\n";
        cout << " tortr help\n";
        return 0;
    }

    string command = argv[1];

    if (command == "help") {
        cout << "tortr commands:\n";
        cout << " install <package>\n";
        cout << " search <package>\n";
        cout << " update\n";
        cout << " setup\n";
        return 0;
    }

    if (command == "setup") {
        cout << "Installing tortr to /usr/local/bin...\n";
        system("sudo cp tortr /usr/local/bin/tortr");
        cout << "Done.\n";
        return 0;
    }

    string manager;

    if (exists("pacman")) manager = "pacman";
    else if (exists("apt")) manager = "apt";
    else if (exists("dnf")) manager = "dnf";
    else if (exists("zypper")) manager = "zypper";
    else manager = "unknown";

    cout << "Detected package manager: " << manager << "\n";

    if (command == "install") {

        if (argc < 3) {
            cout << "package required\n";
            return 1;
        }

        string package = argv[2];
        int result = 1;

        if (manager == "pacman")
            result = system(("sudo pacman -S --needed " + package).c_str());

        else if (manager == "apt")
            result = system(("sudo apt install -y " + package).c_str());

        else if (manager == "dnf")
            result = system(("sudo dnf install -y " + package).c_str());

        else if (manager == "zypper")
            result = system(("sudo zypper install " + package).c_str());

        if (result != 0) {

            if (exists("flatpak")) {
                cout << "Trying flatpak...\n";
                system(("flatpak install flathub " + package).c_str());
            }

            else if (exists("snap")) {
                cout << "Trying snap...\n";
                system(("sudo snap install " + package).c_str());
            }
        }
    }

    else if (command == "search") {

        if (argc < 3) {
            cout << "package required\n";
            return 1;
        }

        string package = argv[2];

        if (manager == "pacman")
            system(("pacman -Ss " + package).c_str());

        else if (manager == "apt")
            system(("apt search " + package).c_str());

        else if (manager == "dnf")
            system(("dnf search " + package).c_str());

        else if (manager == "zypper")
            system(("zypper search " + package).c_str());
    }

    else if (command == "update") {

        if (manager == "pacman")
            system("sudo pacman -Syu");

        else if (manager == "apt")
            system("sudo apt update && sudo apt upgrade -y");

        else if (manager == "dnf")
            system("sudo dnf upgrade -y");

        else if (manager == "zypper")
            system("sudo zypper update");

        if (exists("flatpak"))
            system("flatpak update");

        if (exists("snap"))
            system("sudo snap refresh");
    }

    else {
        cout << "unknown command\n";
    }

    return 0;
}
