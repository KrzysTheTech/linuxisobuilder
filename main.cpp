#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>

// Function to display a menu and get user's choice
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
    
    std::cin.ignore(10000, '\n'); // Clear the buffer
    return choice;
}

// Function to execute the live-build command
void run_live_build(const std::string& distro, const std::string& desktop) {
    std::string command = "lb config -d " + distro + " --debian-installer live";
    if (!desktop.empty() && desktop != "No X11") {
        command += " -p " + desktop;
    }
    
    std::cout << "\nPreparing to run the following command: " << std::endl;
    std::cout << command << std::endl;
    std::cout << "This will create a new directory with the live-build configuration." << std::endl;
    std::cout << "Do you want to continue? (y/n): ";
    
    char confirm;
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        std::cout << "\nRunning live-build configuration..." << std::endl;
        int result = system(command.c_str());
        if (result == 0) {
            std::cout << "\nConfiguration created successfully." << std::endl;
            std::cout << "Navigate to the new directory and run 'lb build' to create the ISO." << std::endl;
        } else {
            std::cerr << "An error occurred while running the command." << std::endl;
        }
    } else {
        std::cout << "Operation cancelled." << std::endl;
    }
}

int main() {
    try {
        // --- Distribution Selection ---
        std::vector<std::string> distros = {
            "Ubuntu",
            "Debian"
        };
        int distro_choice = display_menu("Select a Distribution", distros);
        std::string selected_distro_name = distros[distro_choice - 1];

        // --- Version Selection ---
        std::vector<std::string> versions;
        if (selected_distro_name == "Ubuntu") {
            versions = {
                "devel (25.10)", "25.04", "24.10", "24.04 LTS", "22.04 LTS",
                "20.04 LTS", "18.04 LTS (ESM)", "16.04 LTS (ESM)", "14.04 LTS (ESM+Legacy)"
            };
        } else { // Debian
            versions = {
                "unstable (sid)", "testing (trixie)", "stable (bookworm)", "oldstable (bullseye)"
            };
        }
        int version_choice = display_menu("Select a Version", versions);
        std::string selected_version = versions[version_choice - 1];

        // --- Desktop Environment Selection ---
        std::vector<std::string> desktops = {
            "No X11 (Server)", "GNOME", "KDE", "XFCE", "LXQT"
        };
        int desktop_choice = display_menu("Select a Desktop Environment", desktops);
        std::string selected_desktop = desktops[desktop_choice - 1];

        // --- Summary and Execution ---
        std::cout << "\n--- Summary ---" << std::endl;
        std::cout << "Distribution: " << selected_distro_name << std::endl;
        std::cout << "Version:      " << selected_version << std::endl;
        std::cout << "Desktop:      " << selected_desktop << std::endl;

        // Extract the codename for the command
        std::string distro_codename;
        if (selected_distro_name == "Ubuntu") {
            if (selected_version == "devel (25.10)") distro_codename = "questing";
            else if (selected_version == "25.04") distro_codename = "plucky";
            else if (selected_version == "24.10") distro_codename = "oracular";
            else if (selected_version == "24.04 LTS") distro_codename = "noble";
            else if (selected_version == "22.04 LTS") distro_codename = "jammy";
            else if (selected_version == "20.04 LTS") distro_codename = "focal";
            else if (selected_version == "18.04 LTS (ESM)") distro_codename = "bionic";
            else if (selected_version == "16.04 LTS (ESM)") distro_codename = "xenial";
            else if (selected_version == "14.04 LTS (ESM+Legacy)") distro_codename = "trusty";
        } else { // Debian
             if (selected_version == "unstable (sid)") distro_codename = "sid";
             else if (selected_version == "testing (trixie)") distro_codename = "trixie";
             else if (selected_version == "stable (bookworm)") distro_codename = "bookworm";
             else if (selected_version == "oldstable (bullseye)") distro_codename = "bullseye";
        }

        std::string desktop_package;
        if (selected_desktop == "GNOME") desktop_package = "gnome-core";
        else if (selected_desktop == "KDE") desktop_package = "kde-standard";
        else if (selected_desktop == "XFCE") desktop_package = "xfce4";
        else if (selected_desktop == "LXQT") desktop_package = "lxqt";


        run_live_build(distro_codename, desktop_package);

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
