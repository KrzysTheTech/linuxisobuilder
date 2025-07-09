#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <map>

// --- Function Declarations ---
int display_menu(const std::string& title, const std::vector<std::string>& options);
bool command_exists(const std::string& command);
void install_dependencies(const std::string& distro_family);
void handle_debian_build();
void handle_ubuntu_build();
void handle_fedora_build();
void handle_arch_build();

// --- Main Function ---
int main() {
    try {
        std::vector<std::string> distros = { "Debian", "Ubuntu", "Fedora", "Arch Linux" };
        int choice = display_menu("Select a Distribution", distros);
        std::string selection = distros[choice - 1];

        install_dependencies(selection);

        if (selection == "Debian") {
            handle_debian_build();
        } else if (selection == "Ubuntu") {
            handle_ubuntu_build();
        } else if (selection == "Fedora") {
            handle_fedora_build();
        } else if (selection == "Arch Linux") {
            handle_arch_build();
        }

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

// --- Function Implementations ---

int display_menu(const std::string& title, const std::vector<std::string>& options) {
    std::cout << "--- " << title << " ---" << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << std::endl;
    }

    int choice = 0;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > static_cast<int>(options.size())) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        throw std::runtime_error("Invalid input. Please enter a number from the list.");
    }
    std::cin.ignore(10000, '\n');
    return choice;
}

bool command_exists(const std::string& command) {
    return system(("command -v " + command + " > /dev/null 2>&1").c_str()) == 0;
}

void install_dependencies(const std::string& distro_family) {
    std::cout << "\nChecking for dependencies..." << std::endl;
    if ((distro_family == "Debian" || distro_family == "Ubuntu") && !command_exists("lb")) {
        std::cout << "live-build not found. Attempting to install..." << std::endl;
        if (system("sudo apt-get update && sudo apt-get install live-build -y") != 0) {
            throw std::runtime_error("Failed to install live-build. Please install it manually.");
        }
    } else if (distro_family == "Fedora" && !command_exists("lorax")) {
        std::cout << "lorax not found. Attempting to install..." << std::endl;
        if (command_exists("dnf")) {
             if (system("sudo dnf install pykickstart lorax -y") != 0) throw std::runtime_error("Failed to install lorax.");
        } else if (command_exists("yum")) {
             if (system("sudo yum install pykickstart lorax -y") != 0) throw std::runtime_error("Failed to install lorax.");
        } else {
            throw std::runtime_error("No DNF or YUM package manager found.");
        }
    } else if (distro_family == "Arch Linux" && !command_exists("mkarchiso")) {
        std::cout << "archiso not found. Attempting to install..." << std::endl;
        if (system("sudo pacman -S archiso --noconfirm") != 0) {
            throw std::runtime_error("Failed to install archiso. Please install it manually.");
        }
    } else {
        std::cout << "Dependencies are satisfied." << std::endl;
    }
}

void handle_debian_build() {
    std::map<std::string, std::string> versions;
    versions["10 (buster)"] = "buster";
    versions["11 (bullseye)"] = "bullseye";
    versions["12 (bookworm)"] = "bookworm";
    versions["13 (trixie)"] = "trixie";
    versions["unstable (sid)"] = "sid";
    
    std::vector<std::string> version_keys;
    for(auto const& [key, val] : versions) version_keys.push_back(key);

    std::string version_key = version_keys[display_menu("Select Debian Version", version_keys) - 1];
    std::string codename = versions[version_key];
    
    std::string command = "lb config -d " + codename;
    std::cout << "Run the following command in your terminal:\n" << command << std::endl;
}

void handle_ubuntu_build() {
    std::map<std::string, std::string> versions;
    versions["14.04 LTS (trusty)"] = "trusty";
    versions["16.04 LTS (xenial)"] = "xenial";
    versions["18.04 LTS (bionic)"] = "bionic";
    versions["20.04 LTS (focal)"] = "focal";
    versions["22.04 LTS (jammy)"] = "jammy";
    versions["24.04 LTS (noble)"] = "noble";
    versions["24.10 (oracular)"] = "oracular";
    versions["25.04 (plucky)"] = "plucky";
    versions["25.10 (questing)"] = "questing";

    std::vector<std::string> version_keys;
    for(auto const& [key, val] : versions) version_keys.push_back(key);

    std::string version_key = version_keys[display_menu("Select Ubuntu Version", version_keys) - 1];
    std::string codename = versions[version_key];

    std::string command = "lb config -d " + codename;
    std::cout << "Run the following command in your terminal:\n" << command << std::endl;
}

void handle_fedora_build() {
    std::vector<std::string> versions = {"42", "41", "Rawhide"};
    int version_choice = display_menu("Select Fedora Version", versions);
    std::string selected_version = versions[version_choice - 1];
    
    std::cout << "\nFedora " << selected_version << " selected." << std::endl;
    std::cout << "A kickstart file (e.g., 'fedora.ks') is required." << std::endl;
    std::string command = "sudo lorax --product=\"Fedora\" --version=\"" + selected_version + "\" --release=\"Fedora " + selected_version + "\" ./output fedora.ks";
    std::cout << "Run a command similar to this to build the ISO:\n" << command << std::endl;
}

void handle_arch_build() {
    std::cout << "\nArch Linux is a rolling release." << std::endl;
    std::cout << "An archiso profile directory (e.g., 'releng') is required." << std::endl;
    std::string command = "sudo mkarchiso -v -w /tmp/archiso-work -o . releng";
    std::cout << "Run the following command from within your profile directory's parent to build the ISO:\n" << command << std::endl;
}
