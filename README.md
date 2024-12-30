# Compiling the Project on Windows

## Requirements

- C++ Builder 6.0

## Compilation Steps

1. Open C++ Builder 6.0.
2. Select `File` -> `Open...` and open the `.bpr` project file located in the project directory.
3. Ensure all source files are added to the project.
4. Configure the build settings as needed.
5. Click `Project` -> `Build All` to compile the entire project.
6. After the compilation is complete, run the application directly from the IDE or find the executable file in the project's output directory.

## Troubleshooting

- Ensure all paths to header files and libraries are correctly configured.
- Check the compilation and linking error messages to identify and fix issues.

# Compiling the Project on Linux

# Power Strip Project

## Compilation and Execution Instructions

### Prerequisites
- CMake 3.2 or higher
- A C compiler (GCC or MSVC)

### Steps to Compile
1. Open a terminal and navigate to the project directory:
    ```sh
    cd /home/artur/Projekty/RelayBoard/linux
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

4. Compile the project:
    ```sh
    make
    ```

### Running the Executable
After successful compilation, you can run the executable:

```sh
./power_strip
```

### Notes
- If you are using Windows, ensure you have MSVC installed and use the appropriate commands for your environment.
- The executable will be located in the `build` directory after compilation.
