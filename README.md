# CPU-RayTracer

## About
**CPU-RayTracer** is a simple ray tracer implemented in C++. It is a learning project where I explore ray tracing concepts, algorithms, and implementations while building a CPU-based ray tracer from scratch.

This project follows the Ray Tracing in One Weekend book series by Peter Shirley, available at [Ray Tracing in One Weekend](https://raytracing.github.io/). While working through the series, I also expand on its ideas, experiment with modifications, and add personal insights to reinforce my understanding.

The goal of this project is to create a ray tracer that evolves over time. It will initially focus on basic features like ray-sphere intersection, then move towards more advanced concepts such as global illumination, path tracing, and physically based rendering (PBR). As the project grows, I plan to split the development into different repositories, which I will be sure to share.

## Features
- Basic ray-sphere intersection
- Simple shading model
- PPM image output
- C++ and CMake-based build system
- Extensible design for future enhancements

## Screenshots 

<details>
	<summary>Ray Tracing in One Weekend</summary>
	
	![Final Image](https://github.com/tuananohut/CPU-RayTracer/blob/main/images/48_final_image.png)
</details>

## Build
### Prerequisites
Ensure you have CMake installed on your computer. You can download it from [cmake.org](https://cmake.org/download/).

### Building the Project
Run the following commands to configure and build the project:

```sh
cmake -B build
cmake --build build
```

For Windows users:
```sh
cmake -B build
cmake --build build --config Release  # Create release binaries in `build\Release`
cmake --build build --config Debug    # Create debug binaries in `build\Debug`
```

## Running the Program
Once compiled, you can execute the program to generate an image in **PPM format**:

```sh
build\Debug\CPU-RayTracer > image.ppm
```

Or, for an optimized version:

```sh
build\Release\CPU-RayTracer > image.ppm
```

The output file `image.ppm` can be opened with an image viewer that supports PPM format or converted to other formats using tools like ImageMagick. You can also use an online resource [ppm viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html).

## Roadmap
This project will be continuously updated with new features as the **Ray Tracing Series** progresses. Future updates may include:
- Support for multiple objects
- Reflection and refraction
- Acceleration structures (BVH, KD-Trees)
- Multi-threading for better performance
- Texture mapping and materials
- Path tracing for realistic global illumination

## Contributing
Contributions and suggestions are welcome! Feel free to open issues or submit pull requests to improve this project.

## Acknowledgements

This project is heavily based on the Ray Tracing in One Weekend book series by Peter Shirley.
The series is freely available online at [Ray Tracing in One Weekend](https://raytracing.github.io/) and has been an invaluable resource in my learning journey.

Special thanks to:

Peter Shirley, for making advanced rendering concepts accessible and approachable.


