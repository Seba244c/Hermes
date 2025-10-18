{ lib
, stdenv
, pkgs ? import <nixpkgs> {}
}:
stdenv.mkDerivation {
    name = "hermes";
    src = lib.sourceByRegex ./. [
        "^src.*"
        "^qml.*"
        "CMakeLists.txt"
        "resources.qrc"
    ];

    nativeBuildInputs = with pkgs; [
        cmake
        ninja
        qt6.wrapQtAppsHook
    ];
    buildInputs = with pkgs; [
        qt6.qtbase
        qt6.qtdeclarative
    ];

    # Use clang as compiler
    CC = "${pkgs.clang}/bin/clang";
    CXX = "${pkgs.clang}/bin/clang++";

    meta = with pkgs.lib; {
        description = "A modern C++ file-explorer";
        platforms = platforms.linux;
        maintainers = with maintainers; [ ssnoer ];
    };
}
