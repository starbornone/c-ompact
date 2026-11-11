# Overview

**c++ompact** (`c-ompact`) is a C++17 command-line tool that compresses and decompresses files with Huffman coding. You point it at an input path and an output path; it either encodes bytes into a compact binary form or decodes that form back to the original bytes.

## Who it is for

- Developers learning Huffman coding through a small, readable CMake project
- Anyone who wants a local encode/decode CLI without network, auth, or server dependencies

## Core capabilities

| Capability | How you use it |
|------------|----------------|
| Encode a file | `cppompact --encode <input> <output>` (or `-e`) |
| Decode a file | `cppompact --decode <input> <output>` (or `-d`) |
| Show usage | `cppompact --help` (or `-h`) |
| Build with CMake | Out-of-source `build/` → `cppompact` / `cppompact.exe` |
| Run unit tests | Build and run `cppompact_tests` (Google Test) |

The encode path builds a Huffman tree from byte frequencies, serializes the tree with the payload, and writes packed bits. The decode path reads that tree back and reconstructs the original file.

## Non-goals

These are intentionally out of scope unless the [roadmap](../roadmap/roadmap.json) says otherwise:

- Network services, APIs, or multi-user access
- Databases, authentication, or cloud deployment
- Guaranteed stable bit-identical archives across runs when frequencies tie
- A general-purpose archive format (no zip/tar compatibility)

## Project status

**Active.** The README documents a working CMake build, encode/decode CLI, and Google Test target. Known gaps (sample `input/` paths, Google Test submodule setup, and correctness edge cases) are tracked in the roadmap.

## Next reads

- [Getting started](getting-started.md) — build, encode, decode, verify
- [Architecture](architecture.md) — modules and data flow
- [Development](development.md) — layout, tests, local workflow
- [AGENTS.md](../AGENTS.md) — conventions for coding agents
- [Roadmap](../roadmap/roadmap.json) — prioritized open work
