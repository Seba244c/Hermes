#!/usr/bin/env python3
import os
import subprocess

env = os.environ.copy()
env["CC"] = "clang"
env["CXX"] = "clang++"

subprocess.run(
    [
        "conan",
        "install",
        ".",
        "--output-folder=build",
        "--build=missing",
        "-s",
        "build_type=Debug",
    ],
    env=env,
)

subprocess.run(
    [
        "cmake",
        "--preset",
        "conan-debug",
        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
        "-B",
        "./build/",
    ],
    env=env,
)

if os.path.islink("./compile_commands.json"):
    os.unlink("./compile_commands.json")
os.system(f"ln -s ./build/compile_commands.json .")

if os.path.islink("./qmldir"):
    os.unlink("./qmldir")
os.system(f"ln -s ./build/Hermes/qmldir .")
