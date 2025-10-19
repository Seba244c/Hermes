#!/usr/bin/env python3
import os
import subprocess

conan_build_type = "Debug"
preset = "conan-debug"

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
        "build_type=" + conan_build_type,
    ],
    env=env,
)

subprocess.run(
    [
        "cmake",
        "--preset",
        preset,
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
