# Contributing

Contributions should keep the CLI behaviour documented in the [README](../README.md) accurate and improve correctness, tests, or docs without inventing unrelated product surface.

## Propose changes

1. Branch from `main` (or the default branch).
2. Make a focused change — prefer one concern per PR (bugfix, test harness repair, docs).
3. Build and exercise the path you touched:

   ```bash
   cmake -S . -B build
   cmake --build build
   # if tests are available:
   cmake --build build --target cppompact_tests
   ./build/cppompact_tests   # or from build/: ./cppompact_tests
   ```

4. Manually encode/decode a small file when you change packing, trees, or CLI args (see [getting started](getting-started.md)).
5. Open a PR that states what changed and how you verified it.

## Documentation expectations

- User-facing CLI behaviour belongs in `README.md` and [getting-started.md](getting-started.md).
- Structural / agent guidance belongs under `docs/` and [AGENTS.md](../AGENTS.md).
- Keep README examples and docs in sync (paths, flags, build commands).
- If you change the on-disk format or module boundaries, update [architecture.md](architecture.md) and [decisions.md](decisions.md).

## Roadmap moves with the work

Roadmap items live in `roadmap/` and must move in the **same change** as the work they describe:

| When | Action |
|------|--------|
| You finish an item | Move it from `roadmap.json` → end of `completed.json` and set `completedAt` |
| You drop an item | Move it to `cancelled.json` with `cancelledAt` and a short `reason` |
| You start related new work | Add a **new** id in `roadmap.json`; never reuse or rename an id |

Full contract: [roadmap-format.md](roadmap-format.md). Agent rules: [AGENTS.md](../AGENTS.md).

## What not to do

- Do not add auth, databases, network services, or CI tooling in a drive-by change unless a roadmap item explicitly calls for it.
- Do not rename roadmap `id` values.
- Do not invent CLI flags or format fields undocumented in the README/docs.

## Related

- [Development](development.md)
- [Decisions](decisions.md)
