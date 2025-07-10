# linuxisobuilder

A command-line tool to simplify the creation of custom Linux ISO images.

## 📜 Description

This project provides a simple C++ based interactive tool that guides the user through selecting a distribution, and then provides the necessary commands to build a custom live CD using the distribution's native tools.

## ✨ Supported Distributions
* **Debian** (using `live-build`)
* **Ubuntu** (using `live-build`)
* **Fedora** (using `lorax` and Kickstart)
* **Arch Linux** (using `archiso`)

***

## ⚙️ Architecture Support

The official pre-built packages provided in the **Releases** section are automatically built for the following common architectures:

* **Linux:** `x86_64` (amd64), `aarch64` (arm64)
* **Windows:** `x86_64` (x64)
* **macOS:** `x86_64` (Intel), `aarch64` (Apple Silicon)

For all other architectures (such as i386, PowerPC, RISC-V, etc.), you will need to **compile the application from the source** on the target machine.

***

## 📦 Prerequisites

This tool is designed to be self-sufficient. When you first run it and select a distribution family, it will check for the necessary build tools and prompt you to install them if they are missing.

To compile the tool itself, you will need a C++ compiler (`g++` or `clang++`) and `cmake`.

***

## 🚀 How to Use

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/KrzysTheTech/linuxisobuilder.git](https://github.com/KrzysTheTech/linuxisobuilder.git)
    cd linuxisobuilder
    ```

2.  **Compile the program:**
    ```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
    ```

3.  **Run the builder:**
    ```bash
    ./linuxisobuilder-gui
    ```

***

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!
