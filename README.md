# linuxisobuilder

A command-line tool and graphical application to simplify the creation of custom Linux ISO images.

## 📜 Description

This project provides both a command-line interface (CLI) and a graphical user interface (GUI) to guide users through selecting a distribution. It then provides the necessary commands to build a custom live CD using the distribution's native tools.

## ✨ Supported Distributions

The tool provides interactive menus and build command generation for the following operating systems:

* **Debian** (via `live-build`)
    * **Versions:** 13 (trixie), 12 (bookworm), 11 (bullseye), unstable (sid), and 10 (buster) `[EOL]`
* **Ubuntu** (via `live-build`)
    * **Versions:** 25.10, 25.04, 24.04 LTS, 22.04 LTS, 20.04 LTS, 18.04 LTS, and 24.10 `[EOL]`
* **Fedora** (via `lorax` and Kickstart)
    * **Versions:** 42, 41, and Rawhide
* **Arch Linux** (via `archiso`)
    * Rolling Release

***

## 💻 Supported Architectures and Operating Systems

Official pre-built binaries are provided for the following platforms:

* **Linux**
    * **Architectures:** `amd64`, `arm64`, `i386`, `ppc64el`, `riscv64`, `s390x`.
    * **Available Versions:**
        * **CLI:** Supported on all listed architectures.
        * **GUI:** Supported on `x86_64` (amd64) only.

* **Windows**
    * **Architectures:** `x86_64` (x64)
    * **Available Versions:** GUI only.

* **macOS**
    * **Architectures:** `x86_64` (Intel). Support for `aarch64` (Apple Silicon) is planned.
    * **Available Versions:** GUI only.

For all other architectures, you will need to compile the application from the source.

***

## 📦 Prerequisites

The tool is designed to be self-sufficient. When you run it and select a distribution family, it will check for the necessary build tools and prompt you to install them if they are missing.

To compile the tool itself, you will need a C++ compiler and `make` or `cmake`.

***

## 🚀 How to Use

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/KrzysTheTech/linuxisobuilder.git
    cd linuxisobuilder
    ```

2.  **Compile the program:**
    * **For the CLI:**
        ```bash
        make
        ```
    * **For the GUI:**
        ```bash
        mkdir build && cd build
        cmake ..
        cmake --build .
        ```

3.  **Run the builder:**
    ```bash
    # Run the CLI version
    ./build-iso --version
    ./build-iso

    # Run the GUI version from the 'build' directory
    ./linuxisobuilder-gui
    ```

***

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!
