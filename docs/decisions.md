# Decisions

Lightweight records of choices implied by the README and the current CMake/C++ layout. These are not a full ADR process — they document scope so agents do not re-litigate settled defaults.

---

## ADR-001: CMake + C++17 library/CLI split

**Context:** The project needs a portable desktop build with a clear place for unit tests.

**Decision:** Use CMake 3.10+, require C++17, build `cppompact_lib` and link it into `cppompact` and `cppompact_tests`.

**Consequences:** Contributors must use an out-of-source `build/`. Tests and the CLI share one library, so core logic should not live only in `main.cpp`.

---

## ADR-002: Local Huffman CLI only

**Context:** The README presents encode/decode file paths and help — no server or library packaging story.

**Decision:** Ship a single local CLI (`--encode` / `--decode` / `--help`). Non-goals include network APIs, auth, databases, and cloud deploy.

**Consequences:** Documentation and roadmap stay focused on correctness, DX, and tests. Do not invent service layers.

---

## ADR-003: Google Test via git submodule

**Context:** The README documents `cppompact_tests` and troubleshooting via `git submodule update --init --recursive`.

**Decision:** Depend on Google Test from the `googletest` submodule directory (`add_subdirectory(googletest)` in CMake).

**Consequences:** Configure fails if the submodule is missing. Repair the submodule (or a roadmap-approved FetchContent alternative) rather than switching frameworks casually.

---

## ADR-004: Tree-prefixed custom binary format

**Context:** Encode must be self-contained so decode does not need the original frequency table.

**Decision:** Store a serialized Huffman tree, a padding byte, then MSB-packed payload bits in the output file.

**Consequences:** Format changes require paired encode/decode updates and round-trip tests. There is no magic/version yet — treat the layout as internal until framing is added on the roadmap.

---

## ADR-005: README paths are relative to the caller’s CWD

**Context:** Examples run from `build/` with `../input/…` and `../output/…`.

**Decision:** Document and keep path resolution as ordinary filesystem paths relative to the process working directory; do not embed a project-root path finder.

**Consequences:** Missing `input/` samples cause “file not found”. Docs and troubleshooting must tell newcomers to create those files or pass real paths.

---

## Related

- [Architecture](architecture.md)
- [Roadmap](../roadmap/roadmap.json)
