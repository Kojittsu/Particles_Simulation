{
  description = "Particle Simulation flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    # Tell flake to use git submodules
    self.submodules = true;
  };

  outputs = { self, nixpkgs, ... }@inputs:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in {
    packages.${system}.default = pkgs.stdenv.mkDerivation {
      pname = "particle-simulation";
      version = "1.0.0";
      src = ./.;

      buildInputs = with pkgs; [
        glm
        glew
        glfw
        yaml-cpp
        zenity
      ];

      buildPhase = "make";

      installPhase = ''
        mkdir -p $out/bin
        cp particle-simulation-executable $out/bin/particle-simulation

        # Add config-example files
        mkdir -p $out/share/particle-simulation-config-examples
        cp -r config-examples/* $out/share/particle-simulation-config-examples/

        # Add desktop entry
        mkdir -p $out/share/applications
        cp particle-simulation.desktop $out/share/applications/
      '';
    };

    apps.${system}.default = {
      type = "app";
      program = "${self.packages.${system}.default}/bin/particle-simulation";
    };

    devShells.${system}.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        glm
        glew
        glfw
        yaml-cpp
        zenity

        doxygen
      ];
    };
  };
}
