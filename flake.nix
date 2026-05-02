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

      nativeBuildInputs = [ pkgs.makeWrapper ];

      buildInputs = with pkgs; [
        glm
        glew
        glfw
        yaml-cpp
      ];

      buildPhase = "make";

      installPhase = ''
        mkdir -p $out/bin
        cp particle-simulation-executable $out/bin/particle-simulation

        wrapProgram $out/bin/particle-simulation \
          --prefix PATH : ${pkgs.zenity}/bin

        # Add config-example files
        mkdir -p $out/share/particle-simulation-config-examples
        cp -r config-examples/* $out/share/particle-simulation-config-examples/

        # Add desktop entry
        mkdir -p $out/share/applications
        cp particle-simulation.desktop $out/share/applications/

        # Add icon
        mkdir -p $out/share/icons/hicolor/256x256/apps
        cp .github/assets/particle-simulation-icon-256.png $out/share/icons/hicolor/256x256/apps/particle-simulation-icon.png
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
