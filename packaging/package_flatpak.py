#!/usr/bin/env python3
import os

if not os.path.isdir("build/package_flatpak/"):
    os.mkdir("build/package_flatpak/")

os.system(
    "flatpak-builder --force-clean --user --install-deps-from=flathub --repo=repo --install build/package_flatpak/ packaging/dk.sebsa.Hermes.yml"
)
