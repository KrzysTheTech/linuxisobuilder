# linuxisobuilder

A command-line tool to simplify the creation of custom Ubuntu and Debian based ISO images using `live-build`.

## 📜 Description

This project provides a simple C++ based interactive tool that guides the user through selecting a distribution, version, and desktop environment. It then generates the necessary `live-build` configuration to build a custom live CD.

**Version: 0.0.1**

## 📦 Prerequisites

Before you begin, you need to have `live-build` and `g++` (or another C++ compiler) installed.

```bash
sudo apt-get update
sudo apt-get install live-build g++
