{
  description = "A modern C++ file-explorer";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable"; # un-stable Nixpkgs

  outputs =
    { self, ... }@inputs:

    let
      supportedSystems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];
      forEachSupportedSystem =
        f:
        inputs.nixpkgs.lib.genAttrs supportedSystems (
          system:
          f {
            pkgs = import inputs.nixpkgs { inherit system; };
          }
        );
    in
    {
        packages = forEachSupportedSystem(
        { pkgs }: 
        {
            default = pkgs.callPackage ./package.nix { };
        });
      devShells = forEachSupportedSystem (
        { pkgs }:
        {
          default =
            pkgs.mkShell.override
              {
                # Override stdenv in order to change compiler:
                stdenv = pkgs.clangStdenv;
              }
              {
                packages =
                  with pkgs;
                  [
                    cmake
                    ninja
                    python3
                    qt6.qtbase
                    qt6.qtdeclarative
                  ];
              shellHook = ''
            export CC=clang
            export CXX=clang++
          '';
                  #++ (if system == "aarch64-darwin" then [ ] else [ gdb ]);
              };
        }
      );
    };
}
