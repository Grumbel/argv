{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in rec {
        packages = rec {
          argv = pkgs.stdenv.mkDerivation {
            pname = "argv";
            version = "0.1.0";
            src = nixpkgs.lib.cleanSource ./.;
            nativeBuildInputs = with pkgs; [
              cmake
            ];
          };
          default = argv;
        };
      }
    );
}
