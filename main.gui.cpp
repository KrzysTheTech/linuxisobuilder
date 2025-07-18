#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <vector>
#include <map>

// Helper macro to turn preprocessor definition into a string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// --- Data for our dropdowns ---
const std::map<std::string, std::vector<std::string>> distro_versions = {
    {"Debian", {"12 (bookworm)", "11 (bullseye)", "13 (trixie)", "unstable (sid)", "10 (buster) [EOL: June 30, 2024]"}},
    {"Ubuntu", {"24.04 LTS (noble)", "22.04 LTS (jammy)", "20.04 LTS (focal)", "18.04 LTS (bionic)", "25.10 (questing)", "25.04 (plucky)", "24.10 (oracular) [EOL: July 10, 2025]"}},
    {"Fedora", {"42", "41", "Rawhide"}},
    {"Arch Linux", {"Rolling Release"}}
};

const std::map<std::string, std::vector<std::string>> distro_desktops = {
    {"Debian", {"GNOME", "KDE", "XFCE", "LXQT", "No X11 (Server)"}},
    {"Ubuntu", {"GNOME", "KDE", "XFCE", "LXQT", "No X11 (Server)"}},
    {"Fedora", {"Kickstart (.ks) required"}},
    {"Arch Linux", {"Profile directory (e.g., releng)"}}
};

const std::map<std::string, std::map<std::string, std::string>> version_codename = {
    {"Debian", {
        {"12 (bookworm)", "bookworm"}, {"11 (bullseye)", "bullseye"},
        {"13 (trixie)", "trixie"}, {"unstable (sid)", "sid"},
        {"10 (buster) [EOL: June 30, 2024]", "buster"}
    }},
    {"Ubuntu", {
        {"24.04 LTS (noble)", "noble"}, {"22.04 LTS (jammy)", "jammy"},
        {"20.04 LTS (focal)", "focal"}, {"18.04 LTS (bionic)", "bionic"},
        {"25.10 (questing)", "questing"}, {"25.04 (plucky)", "plucky"},
        {"24.10 (oracular) [EOL: July 10, 2025]", "oracular"}
    }},
    {"Fedora", {
        {"42", "42"}, {"41", "41"}, {"Rawhide", "Rawhide"}
    }},
    {"Arch Linux", {
        {"Rolling Release", "rolling"}
    }}
};

// --- About Dialog ---
class AboutDialog : public Gtk::AboutDialog {
public:
    AboutDialog() {
        set_program_name("Linux ISO Builder");
#ifdef PROJECT_VERSION
        set_version(TOSTRING(PROJECT_VERSION));
#else
        set_version("unknown");
#endif
        set_comments("A GUI tool to help generate commands for building custom Linux ISOs.");
        set_logo_icon_name("drive-harddisk");
    }
};

// --- Main Window Class ---
class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    void on_distro_changed();
    void on_generate_clicked();
    void on_about_clicked();
    void populate_versions();

    // Member Widgets
    Gtk::Box m_main_box;
    Gtk::Frame m_distro_frame, m_version_frame, m_desktop_frame;
    Gtk::ComboBoxText m_combo_distro, m_combo_version, m_combo_desktop;
    Gtk::Button m_button_generate;
    Gtk::ScrolledWindow m_scrolled_window;
    Gtk::TextView m_text_view;
    Gtk::HeaderBar m_header_bar;
    Gtk::MenuButton m_menu_button;
};

MainWindow::MainWindow() :
    m_main_box(Gtk::Orientation::VERTICAL, 10),
    m_distro_frame("1. Select Distribution"),
    m_version_frame("2. Select Version"),
    m_desktop_frame("3. Select Desktop"),
    m_button_generate("Generate Command")
{
    set_title("Linux ISO Builder");
    set_default_size(500, 400);
    
    m_header_bar.set_show_title_buttons(true);
    set_titlebar(m_header_bar);

    auto popover = Gtk::make_managed<Gtk::Popover>();
    m_menu_button.set_popover(*popover);
    m_menu_button.set_icon_name("open-menu-symbolic");
    m_header_bar.pack_end(m_menu_button);

    auto about_button = Gtk::make_managed<Gtk::Button>("About");
    about_button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_about_clicked));
    popover->set_child(*about_button);

    m_main_box.set_margin(10);
    set_child(m_main_box);

    m_combo_distro.append("Select a Distribution...");
    m_combo_distro.append("Debian");
    m_combo_distro.append("Ubuntu");
    m_combo_distro.append("Fedora");        // FIX: Add missing Fedora
    m_combo_distro.append("Arch Linux");    // FIX: Add missing Arch Linux
    m_distro_frame.set_child(m_combo_distro);
    m_main_box.append(m_distro_frame);

    m_combo_version.set_sensitive(false);
    m_version_frame.set_child(m_combo_version);
    m_main_box.append(m_version_frame);
    
    m_desktop_frame.set_child(m_combo_desktop);
    m_main_box.append(m_desktop_frame);
    
    m_main_box.append(m_button_generate);

    m_scrolled_window.set_child(m_text_view);
    m_scrolled_window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_scrolled_window.set_expand();
    m_main_box.append(m_scrolled_window);

    m_combo_distro.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_distro_changed));
    m_button_generate.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_generate_clicked));
    
    m_combo_distro.set_active(0);
    populate_versions();
    m_combo_desktop.set_active(0);
}

MainWindow::~MainWindow() {}

void MainWindow::on_about_clicked() {
    AboutDialog about_dialog;
    about_dialog.set_transient_for(*this);
    about_dialog.set_modal(true);
    about_dialog.show();
}

void MainWindow::populate_versions() {
    m_combo_version.remove_all();
    m_combo_desktop.remove_all();

    std::string distro = m_combo_distro.get_active_text();
    if (distro_versions.count(distro)) {
        for (const auto& v : distro_versions.at(distro)) {
            m_combo_version.append(v);
        }
        m_combo_version.set_sensitive(true);
        m_combo_version.set_active(0);
    } else {
        m_combo_version.set_sensitive(false);
        m_combo_version.set_active(-1);     // FIX: Reset selection if not valid
    }

    if (distro_desktops.count(distro)) {
        for (const auto& d : distro_desktops.at(distro)) {
            m_combo_desktop.append(d);
        }
        m_combo_desktop.set_sensitive(true);
        m_combo_desktop.set_active(0);
    } else {
        m_combo_desktop.set_sensitive(false);
        m_combo_desktop.set_active(-1);     // FIX: Reset selection if not valid
    }
}

void MainWindow::on_distro_changed() { populate_versions(); }

void MainWindow::on_generate_clicked() {
    std::string distro = m_combo_distro.get_active_text();
    std::string version = m_combo_version.get_active_text();
    std::string desktop = m_combo_desktop.get_active_text();
    std::string output;

    if (distro == "Debian" || distro == "Ubuntu") {
        if (version_codename.at(distro).count(version)) { // FIX: Check if version exists
            std::string codename = version_codename.at(distro).at(version);
            output = "lb config -d " + codename;
            if (desktop != "No X11 (Server)") {
                output += " --packages \"";
                Glib::ustring desktop_str(desktop);
                output += desktop_str.lowercase();
                output += (distro == "Debian" ? "-core\"" : "-desktop\"");
            }
            output += "\nsudo lb build";
        } else {
            output = "# Please select a valid version.";
        }
    } else if (distro == "Fedora") {
        output = "sudo lorax --product=\"Fedora\" --version=\"" + version + "\" --release=\"Fedora " + version + "\" ./output fedora.ks\n";
        output += "# Create a Kickstart (.ks) file and run the above command.";
    } else if (distro == "Arch Linux") {
        output = "sudo mkarchiso -v -w /tmp/archiso-work -o . releng\n";
        output += "# Create a profile directory (e.g., 'releng') and run the above command.";
    } else {
        output = "# Please select a distribution.";
    }

    m_text_view.set_buffer(Gtk::TextBuffer::create());
    m_text_view.get_buffer()->set_text(output);
}

// --- Application Class ---
class IsoBuilderApplication : public Gtk::Application {
public:
    // The create() method is the standard way to get an instance.
    static Glib::RefPtr<IsoBuilderApplication> create() {
        return Glib::RefPtr<IsoBuilderApplication>(new IsoBuilderApplication());
    }

protected:
    IsoBuilderApplication() : Gtk::Application("tech.krzys.linuxisobuilder.gui") {}

    void on_activate() override {
        auto main_window = new MainWindow();
        add_window(*main_window);
        main_window->show();
    }
};

int main(int argc, char* argv[]) {
    // CORRECTED: Use the static create() method instead of Gtk::make_refptr
    auto app = IsoBuilderApplication::create();
    return app->run(argc, argv);
}
