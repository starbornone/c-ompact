# Development

Local workflow for changing, building, and testing c++ompact.

## Repository layout

```
c-ompact/
  AGENTS.md              # Agent working agreements
  CMakeLists.txt         # Library, CLI, Google Test targets
  README.md              # Human entry point
  docs/                  # Architecture and contributor docs
  roadmap/               # todo / completed / cancelled JSON
  include/               # Public headers for cppompact_lib
  src/                   # Library + main.cpp
  tests/                 # Google Test sources (test_huffman.cpp)
  googletest/            # Git submodule (required for tests)
  input/                 # Not committed; create locally for README examples
  output/                # Generated; gitignored
  build/                 # Out-of-source build; gitignored
```

Important entrypoints:

- CLI: `src/main.cpp`
- Library sources: listed in `CMakeLists.txt` as `CPPO_COMPACT_SOURCES`
- Tests: `tests/test_huffman.cpp`

## Configure and build

Always use an out-of-source `build/` directory:

```bash
cmake -S . -B build
cmake --build build
```

Equivalent to the README’s `mkdir build && cd build && cmake .. && make` on Make-based generators.

Targets:

| Target | Purpose |
|--------|---------|
| `cppompact_lib` | Core library |
| `cppompact` | CLI executable |
| `cppompact_tests` | Google Test runner |

CMake always calls `add_subdirectory(googletest)`, so **configure requires Google Test to be present**.

### Google Test submodule

```bash
git submodule update --init --recursive
```

If that does not populate `googletest/` (missing gitlink / empty checkout), fix the submodule registration before expecting `cmake` to succeed. Do not invent a second test framework; the project uses Google Test as documented in the README.

## Run tests

From `build/` (README style):

```bash
make cppompact_tests
./cppompact_tests
```

Or:

```bash
cmake --build build --target cppompact_tests
ctest --test-dir build --output-on-failure
```

**Notes for agents:**

- Tests create files under relative paths such as `tests/sample_input.txt` and `output/…`. Run them with a predictable CWD (typically `build/`) so paths resolve consistently.
- There is no project lint/format toolchain in-repo today. Prefer matching existing C++17 style (and existing include patterns) over introducing new formatters unless the roadmap says so.
- Compiler warning flags in `CMakeLists.txt` are currently commented out.

## Safe navigation rules

- Prefer small, focused diffs in `src/` + `include/` + matching `tests/`.
- Encode and decode format changes must stay paired; add a round-trip test when touching bit packing or tree serialization.
- Do not commit secrets, large binaries, or contents of `build/`, `output/`, or generated `*.bin` (see `.gitignore`).
- Update [roadmap](../roadmap/roadmap.json) in the same change as the work ([roadmap format](roadmap-format.md)).

## Related

- [Getting started](getting-started.md)
- [Contributing](contributing.md)
- [AGENTS.md](../AGENTS.md)
