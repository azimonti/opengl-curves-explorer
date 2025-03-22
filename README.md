# Opengl Curves Explorer

OpenGL engine exploring 3D curves

## Required Tools

- Git
- CMake
- clang
- OpenGL
- GLEW
- GLFW
- Dear ImGui
- implot

## Getting Started

To get started with the OpenGL engine:

1. Clone the repository:
   ```
   git clone https://github.com/azimonti/opengl-curves-explorer
   ```
2. Navigate to the repository directory:
   ```
   cd opengl-curves-explorer
   ```
3. Initialize and update the submodules:
  ```
  git submodule update --init --recursive
  ```

Further update of the submodule can be done with the command:
  ```
  git submodule update --remote
  ```

4. Compile the libraries in `ma-libs`
  ```
  cd externals/ma-libs
  # optional steps if dependencies are not installed globally
  # ./manage_dependency_libraries.sh -d
  # ./manage_dependency_libraries.sh -b
  ./cbuild.sh --build-type Debug --cmake-params -DCPP_LIBGRAPHIC_ENGINE=ON
  ./cbuild.sh --build-type Release --cmake-params -DCPP_LIBGRAPHIC_ENGINE=ON
  cd ../..
  ```

  If any error or missing dependencies please look at the instructions [here](https://github.com/azimonti/ma-libs)

5. Compile the binaries
  ```
  ./cbuild.sh -t Release (or -t Debug)
  ```

6. Run the program
  ```
  ./build/Release/opengl-curves-explorer
  ```

Here some screenshots to show the possibilities of the application.

![Screenshot 1](screenshots/screenshot_1.png)

![Screenshot 2](screenshots/screenshot_2.png)

![Screenshot 3](screenshots/screenshot_3.png)

## Contributing

Contributions to the Opengl Curves Explorer project are welcome. Whether it's through submitting bug reports, proposing new features, or contributing to the code, your help is appreciated. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

If you have any questions or want to get in touch regarding the project, please open an issue or contact the repository maintainers directly through GitHub.
