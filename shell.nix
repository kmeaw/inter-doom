{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = [ pkgs.cmake pkgs.gcc_multi pkgs.pkgconfig pkgs.SDL2 pkgs.SDL2_gfx pkgs.SDL2_mixer pkgs.SDL2_net pkgs.glibc pkgs.valgrind ];
}
