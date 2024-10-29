# nvhpc devcontainer setup for kokkos

Working in devcontainers is great: you can isolate and transport your environment.
Getting non-standard compilers working with vscode's intellisense isn't always trivial.

Here's an example setting up kokkos and mpi from an nvidia-hpc container.

### Running:
- Clone and open the project in vscode
- Open/build the devcontainer (sorry, these nvidia ones are big). N.B. Docker
must be running is needed for this.
- Open the directory in the devcontainer
- Inside the container (integrated terminal):
    ```
    cd build
    ./cmake.sh
    ```
- You can then use the build button in vscode.
- After a build cycle intellisense should be working.

### Notes

It seems necessary to use the not really documented
`Kokkos_ENABLE_COMPILE_AS_CMAKE_LANGUAGE` for intelisense to work properly in
this CUDA devcontainer. If you have another way around this, please let me know.
The current state of documentation for this feature is at:
https://github.com/kokkos/kokkos-core-wiki/pull/555
