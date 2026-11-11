# Getting started

Build c++ompact with CMake, then encode and decode a sample file from the `build` directory.

## Prerequisites

| Tool | Notes |
|------|--------|
| CMake ≥ 3.10 | Project minimum in `CMakeLists.txt` |
| C++17 compiler | MSVC, GCC, or Clang |
| Build tool | `make` on Unix; on Windows use a generator your environment supports (Visual Studio, Ninja, or MinGW Make) |
| Git | Needed if you initialise the Google Test submodule for tests |

**Assumption:** The README’s Windows section still shows `make`. If `make` is not on your PATH, configure an explicit generator, for example `cmake -G Ninja ..` or open the generated Visual Studio solution.

## Build

```bash
mkdir -p build
cd build
cmake ..
make
```

Success looks like an executable in `build/`:

- Unix: `./cppompact`
- Windows: `cppompact.exe` (may live under `build/Debug` or similar for multi-config generators)

### First-run failures

| Symptom | Likely cause | What to do |
|---------|--------------|------------|
| `CMakeLists.txt not found` | Not configuring from `build/` against the repo root | From `build/`, run `cmake ..` |
| Configure fails on `googletest` | Submodule not present | `git submodule update --init --recursive` from the repo root (see [development](development.md) if that still fails) |
| `make: command not found` | Unix-only instructions on a Make-less Windows host | Use your CMake generator’s build command (`cmake --build .`) |
| File not found when encoding | Sample paths from the README do not exist yet | Create `input/input.txt` (and `output/` if needed) relative to your working directory, or pass real paths |

## First useful action

1. Create a tiny input file (from the repo root):

   ```bash
   mkdir -p input output
   echo hello > input/input.txt
   ```

2. From `build/`, encode then decode:

   ```bash
   ./cppompact --encode ../input/input.txt ../output/encoded.bin
   ./cppompact --decode ../output/encoded.bin ../output/decoded.txt
   ```

   On Windows:

   ```bat
   cppompact.exe --encode ..\input\input.txt ..\output\encoded.bin
   cppompact.exe --decode ..\output\encoded.bin ..\output\decoded.txt
   ```

3. Compare `input/input.txt` and `output/decoded.txt`. They should match for a successful round-trip.

4. Optional — show CLI help:

   ```bash
   ./cppompact --help
   ```

## CLI reference (as shipped)

| Flag | Meaning |
|------|---------|
| `--encode` / `-e` `<input>` `<output>` | Encode input → output |
| `--decode` / `-d` `<input>` `<output>` | Decode input → output |
| `--help` / `-h` | Print usage |

Paths are relative to your **current working directory**. The README examples assume you are in `build/` and that `../input/input.txt` exists.

## Tests (optional for first run)

```bash
cd build
make cppompact_tests
./cppompact_tests
```

If Google Test is missing, initialise the submodule first. See [development](development.md).

## Next

- [Architecture](architecture.md) — what happens under encode/decode
- [Development](development.md) — layout and agent workflow
- [Contributing](contributing.md) — how to propose changes
