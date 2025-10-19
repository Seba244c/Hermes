#!/usr/bin/env python3
with open("scripts/generated.py", "w") as file:
    file.write(
        """
conan_build_type = "Release"
preset = "conan-release"
    """
    )
