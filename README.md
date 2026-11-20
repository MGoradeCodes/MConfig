# MConfig

**A lightweight configuration file parser written in C++.**

MConfig is a custom-built C++ configuration parsing library designed to read structured configuration files, tokenize their contents, and extract key-value pairs into easily accessible data structures.

Built from scratch using the C++ Standard Library, MConfig aims to provide a lightweight and reusable solution for handling configuration data without relying on external parsing dependencies.

> **Status:** Active development 🚧

## Features

- [x] Configuration file loading.
- [x] Basic tokenization.
- [x] String extraction.
- [x] Key-value pair extraction.
- [x] Basic bracket syntax validation.
- [x] Token storage and retrieval.
- [ ] Additional primitive data types.
- [ ] Improved syntax validation and error handling.
- [ ] Escaped character support.
- [ ] Improved whitespace handling.
- [ ] Expanded nested object support.

## Project Structure

```text
MConfig/
├── src/
│   └── MConfig.hpp
├── tests/
│   ├── test.json
│   └── main.cpp
└── README.md
```

## Usage

Include the MConfig header in your project:

```cpp
#include "MConfig.hpp"
```

Create an instance of `MParse` and load a configuration file:

```cpp
#include <iostream>
#include "MConfig.hpp"

int main()
{
    MParse config;

    config.LoadFile("config.json");

    auto data = config.fetchData();

    std::cout << data["Name"] << '\n';

    return 0;
}
```

## Example Configuration

```json
{
    "Name": "Manthan",
    "Gender": "Male",
    "Employed": "false",
    "Address": {
        "Street": "Example Street",
        "Building": "42"
    }
}
```

## API Reference

| Method | Description |
|---|---|
| `LoadFile(filepath)` | Loads and parses a configuration file. |
| `fetchData()` | Returns the extracted key-value pairs. |
| `returnParse()` | Returns the generated token list. |

## Building & Testing

MConfig uses the C++ Standard Library and does not require external dependencies.

Compile the test program:

```bash
g++ tests/main.cpp -o MConfigTests
```

Run the executable from the `tests/` directory:

```bash
cd tests
./MConfigTests
```

The test suite checks whether the configuration file loads correctly, tokens are generated, and expected keys are extracted.

## Dependencies

- C++20 recommended.
- Standard C++ Library.
- No external parsing libraries.

## Development Goals

MConfig is an experimental project focused on understanding and implementing configuration parsing from the ground up.

Future development aims to introduce:

- More primitive data types.
- Robust syntax validation.
- Better error reporting.
- Improved nested data structures.
- A more flexible configuration access interface.

## License

License information coming soon.

---

*Made with C++ and curiosity.*