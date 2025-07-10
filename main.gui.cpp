#include <gtkmm-4.0/gtkmm.h>
#include <string>
#include <vector>
#include <map>

// Helper macro to turn preprocessor definition into a string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// --- Data for our dropdowns ---
// (Data maps are not shown for brevity but are required)

// --- About Dialog ---
class AboutDialog : public Gtk::AboutDialog {
public:
    AboutDialog() {
        set_program_name("Linux ISO Builder");
        set_version(TOSTRING(PROJECT_VERSION));
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
    auto about_dialog = Gtk::make_managed<AboutDialog>();
    about_dialog->set_transient_for(*this);
    about_dialog->set_modal(true);
    about_dialog->show();
}

void MainWindow::populate_versions() { /* ... function logic ... */ }
void MainWindow::on_distro_changed() { populate_versions(); }
void MainWindow::on_generate_clicked() { /* ... function logic ... */ }

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
