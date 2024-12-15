{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  name = "ParticleSimulation";

  nativeBuildInputs = with pkgs; [
  ];

  buildInputs = with pkgs; [
    glew
    glfw
    yaml-cpp
  ];

  shellHook = ''
          export LD_LIBRARY_PATH=${pkgs.wayland}/lib:$LD_LIBRARY_PATH
          '';
}
