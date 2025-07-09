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

## 📦 Prerequisites

This tool is designed to be self-sufficient. When you first run it and select a distribution family, it will check for the necessary build tools (`live-build`, `lorax`, or `archiso`) and prompt you to install them if they are missing.

You only need a C++ compiler and `make` to build this tool itself.

```bash
# On Debian/Ubuntu
sudo apt-get install build-essential

# On Fedora
sudo dnf groupinstall "Development Tools"
