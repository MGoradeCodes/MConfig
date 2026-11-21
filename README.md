![MConfig Banner](banner.png)

# MConfig

**A lightweight, header-only configuration file parser written in C++.**

MConfig is a custom-built C++ configuration parsing library designed to read structured JSON-like configuration files, tokenize their contents, flatten nested keys, and extract strongly typed values and arrays on demand.

Built from scratch using the C++ Standard Library, MConfig provides a fast, zero-dependency solution for handling configuration data in C++ projects.

> **Status:** Active development 🚧

## Features

- [x] Configuration file loading (`LoadFile`).
- [x] Custom lexer / tokenization (`returnParse`).
- [x] Nested object flattening via dot-notation (`Parent.Child`).
- [x] Type conversion (`get<T>`).
- [x] Boolean string parsing (`getBool`).
- [x] Typed array / vector parsing (`getVector<T>`).
- [x] Basic bracket and formatting syntax validation.
- [x] Whitespace trimming and handling.
- [ ] Improved syntax validation and detailed error reporting.
- [ ] Escaped character support inside strings.

## Project Structure

```text
MConfig/
├── src/
│   └── MConfig.hpp
├── tests/
│   ├── test.json
│   └── main.cpp
├── banner.png
└── README.md
```

## Usage

Include the `MConfig` header in your project:

```cpp
#include "MConfig.hpp"
```

Create an instance of `MParse`, load a configuration file, and query typed values, booleans, or vectors using dot-notation keys:

```cpp
#include <iostream>
#include <vector>
#include "MConfig.hpp"

int main()
{
    MParse config;
    config.LoadFile("config.json");

    // Fetch single values with automatic type conversion
    std::string name = config.get("Name");
    int building     = config.get<int>("Address.Building");
    bool employed    = config.getBool("Employed");

    // Fetch comma-separated values or arrays as a typed std::vector<T>
    std::vector<std::string> skills = config.getVector<std::string>("Skills");
    std::vector<int> ports          = config.getVector<int>("Server.Ports");

    std::cout << "Name: " << name << '\n';
    std::cout << "Building: " << building << '\n';
    std::cout << "Employed: " << std::boolalpha << employed << '\n';
    std::cout << "First Port: " << ports[0] << '\n';

    return 0;
}
```

## Example Configuration

```json
{
    "Name": "John",
    "Gender": "Male",
    "Employed": "false",
    "Skills": "C++, CMake, Git",
    "Address": {
        "Street": "Example Street",
        "Building": "42"
    },
    "Server": {
        "Ports": [8080, 9090, 3000]
    }
}
```

## API Reference

| Method | Description |
|---|---|
| `LoadFile(filepath)` | Loads, tokenizes, and parses a configuration file into memory. |
| `get<T>(key)` | Retrieves the value for `key` and converts it to type `T` (defaults to `std::string`). |
| `getBool(key)` | Parses and returns the boolean value (`true` / `false`) stored at `key`. |
| `getVector<T>(key)` | Splits a comma-separated list or array at `key` and converts each element into `std::vector<T>`. |
| `fetchData()` | Returns the underlying `std::unordered_map<std::string, std::string>` of flattened key-value pairs. |
| `returnParse()` | Returns the raw `std::vector<std::string>` token list generated during tokenization. |

## Building & Testing

MConfig is header-only and uses the C++ Standard Library with no external dependencies.

Compile the test program with C++17 or C++20:

```bash
g++ -std=c++20 tests/main.cpp -o program
```

Run the executable from the `tests/` directory:

```bash
cd tests
./program.exe
```

## Dependencies

- **C++17 or C++20** (uses `if constexpr` and `std::string_view`).
- **Standard C++ Library** only.
- No external parsing libraries.

## Development Goals

MConfig is an experimental project focused on building a clean, reusable configuration parser from the ground up.

Future updates aim to add:

- Fallback default value lookups.
- Escaped characters inside quoted strings (`\"`, `\n`, `\\`).
- Line-by-line syntax error reporting with line numbers.
- Support for quoted strings containing commas inside arrays.

## License

License information coming soon.

---

*Made with C++.*
