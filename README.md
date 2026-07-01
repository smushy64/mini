# Mini : C++ Header Only Libraries

This is a collection of header-only C++ libraries.

## Usage

- Standalone: Copy libraries you want into your project and include.
- Bundled[^1]: Use `bundle.sh` script to bundle the libraries that you want into a single `mini.h` header.

## Libraries

| name           | description                        |
| -------------- | ---------------------------------- |
| `mini-slice.h` | Slices and buffers                 |
| `mini-fmt.h`   | Text formatting                    |
| `mini-io.h`    | Files and pipes                    |
| `mini-proc.h`  | Processes. Depends on `mini-io.h`  |
| `mini-log.h`   | Logging. Depends on `mini-io.h`    |
| `mini-math.h`  | Math.                              |

[^1]: Recommended, bundle script will bring in dependencies.

