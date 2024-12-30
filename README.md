For Linux compilation:

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
