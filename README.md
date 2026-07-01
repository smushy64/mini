# Mini : C++ Header Only Libraries

This is a collection of header-only C++ libraries.

## Usage

- Standalone: Copy libraries you want into your project and include.
- Bundled[^1]: Use `bundle.sh` script to bundle the libraries that you want into a single `mini.h` header.

## Libraries

| name                | description                                                           |
| ------------------- | --------------------------------------------------------------------- |
| `mini-containers.h` | Slices and buffers                                                    |
| `mini-fmt.h`        | Text formatting. Depends on `mini-containers.h`                       |
| `mini-io.h`         | Files and pipes. Depends on `mini-containers.h`                       |
| `mini-proc.h`       | Processes. Depends on `mini-io.h` and `mini-containers.h`             |
| `mini-log.h`        | Logging. Depends on `mini-io.h`, `mini-containers.h` and `mini-fmt.h` |
| `mini-math.h`       | Math                                                                  |

[^1]: Recommended, bundle script will bring in dependencies.

