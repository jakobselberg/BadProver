{ pkgs ? import (builtins.fetchGit {
    url = "https://github.com/NixOS/nixpkgs";
    ref = "nixos-unstable";
    rev = "b3d51a0365f6695e7dd5cdf3e180604530ed33b4";
  }) {}
}:
let
  python   = pkgs.python313;
  pyPkgs   = pkgs.python313Packages;
in
pkgs.mkShell.override {
  stdenv = pkgs.clangStdenv;
} {

  packages = with pkgs; [

    # compiler + tooling
    clang-tools

    # build system
    cmake
    ninja

    #commandline parsing
    pkgs.cxxopts

    # testing
    pkgs.doctest

    # benchmarking tool dependencies
    python
    pyPkgs.matplotlib

    # vampire
    vampire
  ];

  shellHook = ''
    echo "C++ development shell loaded"
    clang++ --version
  '';
}