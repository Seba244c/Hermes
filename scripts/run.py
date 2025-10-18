#!/usr/bin/env python3
import os
import subprocess

env = os.environ.copy()
env["CC"] = "/usr/bin/clang"
env["CXX"] = "/usr/bin/clang++"

os.chdir("build/")
subprocess.run(["cmake", "--build", "--preset", "conan-debug"], env=env)
os.system("./hermes")
