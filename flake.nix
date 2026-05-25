{
  description = "Multi-platform dev shell with safe platform-specific tools";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {inherit system;};
        windowsPkgs = pkgs.pkgsCross.mingwW64;
      in {
        devShells = {
          default = pkgs.mkShell {
            name = "native-dev";
            nativeBuildInputs = with pkgs; [
              git
              cmake
              ninja
              clang-tools
              cmake-language-server
              # valgrind
            ];
          };

          windows = windowsPkgs.mkShell {
            name = "windows-dev";
            nativeBuildInputs = with pkgs; [
              cmake
              ninja
            ];
          };
        };
      }
    );
}
