{
    description = "C template";
    inputs = {
            nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    };
    outputs = {self, nixpkgs,...}:
    let
        system = "x86_64-linux";
        pkgs = nixpkgs.legacyPackages.${system};
    in
    {
        devShells.${system}.default = pkgs.mkShell {
            packages = with pkgs; [
                gcc
                clang
                gnumake
                cmake
                pkg-config
            ];

            buildInputs = with pkgs; [
                gdb
                valgrind
                clang-tools

                raylib
            ];
            shellHook = ''
                export CC=clang
                export CXX=clang++
                export PKG_CONFIG_PATH="${pkgs.ncurses.dev}/lib/pkgconfig:${pkgs.SDL2.dev}/lib/pkgconfig:$PKG_CONFIG_PATH"
                export LD_LIBRARY_PATH="/run/opengl-driver/lib:$LD_LIBRARY_PATH"
                echo this shi worked
            '';
        };
    };
}
