# linuxisobuilder

A command-line tool to simplify the creation of custom Linux ISO images.

## 📜 Description

This project provides a simple C++ based interactive tool that guides the user through selecting a distribution, and then provides the necessary commands to build a custom live CD using the distribution's native tools.

## ✨ Supported Distributions
* **Debian** (using `live-build`)
* **Ubuntu** (using `live-build`)
* **Fedora** (using `lorax` and Kickstart)
* **Arch Linux** (using `archiso`)

## 📦 Package Formats

The official builds are provided in several formats for wide compatibility:

* **`.deb`**: For **Debian**, **Ubuntu**, **Mint**, **Zorin OS**, and other Debian-based distributions.
* **`.rpm`**: For **Fedora**, **openSUSE**, **RHEL**, **CentOS**, **AlmaLinux**, **Rocky Linux**, **PLD Linux**, and other RPM-based distributions.
* **`.pkg.zst`**: For **Arch Linux** and its derivatives. This package can be used to submit to the AUR (Arch User Repository).

***

## ⚙️ Architecture Support

The official pre-built packages provided in the **Releases** section are automatically built for the following common architectures:

* **Linux:** `x86_64` (amd64), `aarch64` (arm64)
* **Windows:** `x86_64` (x64)
* **macOS:** `x86_64` (Intel), `aarch64` (Apple Silicon)

**Note:** Support for **Windows on ARM (`arm` and `arm64`)** is planned and will be available soon.

For all other architectures (such as i386, PowerPC, RISC-V, etc.), you will need to **compile the application from the source** on the target machine.

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
