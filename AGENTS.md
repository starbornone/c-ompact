# AGENTS

## Project

- **Title:** c++ompact
- **Key:** `c-ompact`
- **Purpose:** Local C++17 Huffman compression CLI. Users build with CMake, then `--encode` / `--decode` files (plus `--help`). Google Test backs `cppompact_tests`. No network, auth, or database layer.

## Layout

| Path | Why it matters |
|------|----------------|
| `README.md` | Human entry point — build, run, troubleshoot |
| `AGENTS.md` | This file — agent agreements |
| `docs/` | Overview, architecture, getting started, development, contributing, decisions, roadmap format |
| `roadmap/` | `roadmap.json`, `completed.json`, `cancelled.json` |
| `CMakeLists.txt` | `cppompact_lib`, `cppompact`, `cppompact_tests` |
| `src/main.cpp` | CLI entry |
| `src/`, `include/` | Library implementation |
| `tests/test_huffman.cpp` | Google Test cases |
| `googletest/` | Submodule required for configure/tests |

## Working agreements

Prefer the README’s commands; do not invent alternate stacks.

```bash
mkdir -p build && cd build
cmake ..
make
./cppompact --encode ../input/input.txt ../output/encoded.bin
./cppompact --decode ../output/encoded.bin ../output/decoded.txt
./cppompact --help
make cppompact_tests
./cppompact_tests
```

On hosts without `make`, use `cmake --build .` / `cmake --build build` instead. Initialise Google Test with:

```bash
git submodule update --init --recursive
```

Create sample `input/` files yourself if they are missing — the README paths are not always committed.

## Documentation

- Update `docs/` when behaviour, layout, build, or contribution process changes.
- Keep `README.md` examples consistent with `docs/getting-started.md`.
- Record scope/format choices in `docs/decisions.md` and structure in `docs/architecture.md`.
- Start from [docs/overview.md](docs/overview.md).

## Roadmap

This project's key is `c-ompact` and its title is `c++ompact`. Keep the
roadmap in three files in `roadmap/` at the repository root:

- `roadmap/roadmap.json`: project status and items still to do, highest priority first
- `roadmap/completed.json`: finished items
- `roadmap/cancelled.json`: items that will not be done

All three use this shape:

```json
{
  "schema": "name-roadmap/v1",
  "file": "roadmap",
  "updatedAt": "2026-10-14T09:30:00+11:00",
  "project": { "key": "c-ompact", "title": "c++ompact", "status": "active", "summary": "Optional, roadmap.json only." },
  "items": [
    { "id": "stable-kebab-id", "title": "Short imperative title", "group": "Optional area", "notes": "Optional detail" }
  ]
}
```

Rules:

1. `schema` is always `"name-roadmap/v1"`. `file` is `"roadmap"`,
   `"completed"` or `"cancelled"` to match the filename.
2. `project.key`, `project.title` and `project.status` are identical in all
   three files. Never change `project.key`. `status` is `active`, `paused` or
   `complete`. `summary` appears only in `roadmap.json`.
3. Every item has an `id`: lowercase kebab-case, unique across all three files,
   never renamed and never reused, even after the item is completed or cancelled.
   Titles and notes may be edited freely; the id stays the same.
4. Allowed item fields are `id`, `title`, `group` and `notes`, plus
   `completedAt` (`completed.json` only, required) and `cancelledAt` with an
   optional `reason` (`cancelled.json` only). Add no other fields.
5. When work is finished, move the item from `roadmap.json` to the end of
   `completed.json` and add `completedAt`. When it is dropped, move it to the
   end of `cancelled.json` and add `cancelledAt` and a short `reason`. Never
   delete an item outright. If a cancelled item is revived, move it back to
   `roadmap.json` with the same id and remove `cancelledAt`/`reason`.
6. Each item is in exactly one file. Split work into new items with new ids
   rather than changing what an existing id means.
7. Set `updatedAt` in every file you change. Timestamps are ISO 8601 with a
   UTC offset, e.g. `2026-10-14T09:30:00+11:00`.
8. Keep `roadmap.json` items in priority order. Titles are at most 500
   characters; notes and reasons at most 20,000; at most 2,000 items per file.
9. Output valid JSON only: UTF-8, two-space indent, no comments, no trailing
   commas. Create a missing file with an empty `items` array.
10. Update the roadmap in the same change as the work it describes: mark an
    item completed only when that work is actually done.

The format contract for other repositories this repo will import is in
[docs/roadmap-format.md](docs/roadmap-format.md).

## Do / don’t

**Do**

- Prefer small diffs; touch encode and decode together when the format changes
- Update roadmap files in the same change as the work
- Add or extend Google Test coverage for packing and edge cases
- Match existing C++17 / CMake conventions

**Don’t**

- Rename or reuse roadmap ids
- Invent CLI flags, network APIs, auth, databases, or CI the project does not use
- Mark roadmap items completed before the work lands
- Commit `build/`, `output/`, or generated binaries
