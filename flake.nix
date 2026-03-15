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
      pname = "particle-simulation-executable";
      version = "1.0.0";
      src = self;

      buildInputs = with pkgs; [
        glm
        glew
        glfw
        yaml-cpp
      ];

      buildPhase = "make";

      installPhase = ''
        mkdir -p $out/bin
        cp particle-simulation-executable $out/bin/
      '';
    };

    apps.${system}.default = {
      type = "app";
      program = "${self.packages.${system}.default}/bin/particle-simulation-executable";
    };

    devShells.${system}.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        glm
        glew
        glfw
        yaml-cpp

        doxygen
      ];
    };
  };
}
