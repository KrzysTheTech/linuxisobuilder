#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <map>
#include <algorithm>

// Helper macros to turn preprocessor definitions into strings
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// --- Function Declarations ---
int display_menu(const std::string& title, const std::vector<std::string>& options);
bool command_exists(const std::string& command);
void install_dependencies(const std::string& distro_family);
void handle_debian_build();
void handle_ubuntu_build();
void handle_fedora_build();
void handle_arch_build();
std::string to_lower(std::string s);

// --- Main Function ---
int main(int argc, char* argv[]) {
    // Check for --version or --about flag
    if (argc > 1 && (std::string(argv[1]) == "--version" || std::string(argv[1]) == "--about")) {
        std::cout << "linuxisobuilder (CLI)" << std::endl;
        #ifdef PROJECT_VERSION
            std::cout << "Version: " << TOSTRING(PROJECT_VERSION) << std::endl;
        #else
            std::cout << "Version: information not available." << std::endl;
        #endif
        #ifdef TARGET_ARCH
            std::cout << "Architecture: " << TOSTRING(TARGET_ARCH) << std::endl;
        #endif
        return 0;
    }
    
    // Original program logic
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

std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
    return s;
}

int display_menu(const std::string& title, const std::vector<std::string>& options) {
    std::cout << "\n--- " << title << " ---" << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << std::endl;
    }
    std::cout << "Enter your choice: ";
    int choice = 0;
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
        if (system("sudo apt-get update && sudo apt-get install -y live-build") != 0) {
            throw std::runtime_error("Failed to install live-build. Please install it manually.");
        }
    } else if (distro_family == "Fedora" && !command_exists("lorax")) {
        std::cout << "lorax not found. Attempting to install..." << std::endl;
        if (command_exists("dnf")) {
             if (system("sudo dnf install -y pykickstart lorax") != 0) throw std::runtime_error("Failed to install lorax.");
        } else if (command_exists("yum")) {
             if (system("sudo yum install -y pykickstart lorax") != 0) throw std::runtime_error("Failed to install lorax.");
        }
    } else if (distro_family == "Arch Linux" && !command_exists("mkarchiso")) {
        std::cout << "archiso not found. Attempting to install..." << std::endl;
        if (system("sudo pacman -S --noconfirm archiso") != 0) {
            throw std::runtime_error("Failed to install archiso. Please install it manually.");
        }
    } else {
        std::cout << "Dependencies are satisfied." << std::endl;
    }
}

void handle_debian_build() {
    std::map<std::string, std::string> versions = {
        {"12 (bookworm)", "bookworm"}, {"11 (bullseye)", "bullseye"},
        {"13 (trixie)", "trixie"}, {"unstable (sid)", "sid"},
        {"10 (buster) [EOL: June 30, 2024]", "buster"}
    };
    std::vector<std::string> desktops = {"GNOME", "KDE", "XFCE", "LXQT", "No X11 (Server)"};
    
    std::vector<std::string> version_keys;
    for(auto const& [key, val] : versions) version_keys.push_back(key);

    std::string version_key = version_keys[display_menu("Select Debian Version", version_keys) - 1];
    std::string desktop_key = desktops[display_menu("Select Desktop Environment", desktops) - 1];
    std::string codename = versions[version_key];

    std::string command = "lb config -d " + codename;
    if (desktop_key != "No X11 (Server)") {
        command += " --packages \"";
        command += to_lower(desktop_key);
        command += "-core\"";
    }
    
    std::cout << "\nTo build your Debian ISO, create a directory and run the following commands inside it:" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << command << std::endl;
    std::cout << "sudo lb build" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}

void handle_ubuntu_build() {
    // CORRECTED: All string literals are now properly terminated.
    std::map<std::string, std::string> versions = {
        {"24.04 LTS (noble)", "noble"}, 
        {"22.04 LTS (jammy)", "jammy"}, 
        {"20.04 LTS (focal)", "focal"},
        {"18.04 LTS (bionic)", "bionic"}, 
        {"25.10 (questing)", "questing"}, 
        {"25.04 (plucky)", "plucky"},
        {"24.10 (oracular) [EOL: July 10, 2025]", "oracular"}
    };
    std::vector<std::string> desktops = {"GNOME", "KDE", "XFCE", "LXQT", "No X11 (Server)"};

    std::vector<std::string> version_keys;
    for(auto const& [key, val] : versions) version_keys.push_back(key);

    std::string version_key = version_keys[display_menu("Select Ubuntu Version", version_keys) - 1];
    std::string desktop_key = desktops[display_menu("Select Desktop Environment", desktops) - 1];
    std::string codename = versions[version_key];

    std::string command = "lb config -d " + codename;
    if (desktop_key != "No X11 (Server)") {
        command += " --packages \"";
        command += to_lower(desktop_key);
        command += "-desktop\"";
    }

    std::cout << "\nTo build your Ubuntu ISO, create a directory and run the following commands inside it:" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << command << std::endl;
    std::cout << "sudo lb build" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}

void handle_fedora_build() {
    std::vector<std::string> versions = {"42", "41", "Rawhide"};
    std::string selected_version = versions[display_menu("Select Fedora Version", versions) - 1];
    
    std::cout << "\nFedora " << selected_version << " selected." << std::endl;
    std::cout << "Building a Fedora ISO requires a Kickstart (.ks) file." << std::endl;
    std::string command = "sudo lorax --product=\"Fedora\" --version=\"" + selected_version + "\" --release=\"Fedora " + selected_version + "\" ./output fedora.ks";
    std::cout << "Create a Kickstart file and run a command similar to this to build the ISO:\n" << command << std::endl;
}

void handle_arch_build() {
    std::cout << "\nArch Linux is a rolling release." << std::endl;
    std::cout << "Building an Arch Linux ISO requires a profile directory (e.g., 'releng')." << std::endl;
    std::string command = "sudo mkarchiso -v -w /tmp/archiso-work -o . releng";
    std::cout << "Create a profile directory and run the following command to build the ISO:\n" << command << std::endl;
}
