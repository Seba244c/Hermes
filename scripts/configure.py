#!/usr/bin/env python3
import os

os.system("cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B./build/")
if os.path.islink("./compile_commands.json"):
    os.unlink("./compile_commands.json")
os.system(f"ln -s ./build/compile_commands.json .")

