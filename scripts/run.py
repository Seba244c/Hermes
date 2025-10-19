#!/usr/bin/env python3
import os
import subprocess

import generated

env = os.environ.copy()
env["CC"] = "/usr/bin/clang"
env["CXX"] = "/usr/bin/clang++"

os.chdir("build/")
subprocess.run(["cmake", "--build", "--preset", generated.preset], env=env)
os.system("./hermes")
