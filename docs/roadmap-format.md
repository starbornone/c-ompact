# Roadmap format contract

This repository keeps product status and work items in three JSON files under `roadmap/`. Other repos (and humans) can import or mirror the same contract.

## Files

| File | `file` field | Purpose |
|------|--------------|---------|
| `roadmap/roadmap.json` | `"roadmap"` | Project status + open items, **highest priority first** |
| `roadmap/completed.json` | `"completed"` | Finished items |
| `roadmap/cancelled.json` | `"cancelled"` | Explicitly abandoned items |

## Schema

```json
{
  "schema": "name-roadmap/v1",
  "file": "roadmap",
  "updatedAt": "2026-11-11T23:09:23+11:00",
  "project": {
    "key": "c-ompact",
    "title": "c++ompact",
    "status": "active",
    "summary": "Optional — roadmap.json only."
  },
  "items": [
    {
      "id": "stable-kebab-id",
      "title": "Short imperative title",
      "group": "Optional area",
      "notes": "Optional detail"
    }
  ]
}
```

### Field rules

1. `schema` is always `"name-roadmap/v1"`. `file` is `"roadmap"`, `"completed"`, or `"cancelled"` to match the filename.
2. `project.key`, `project.title`, and `project.status` are identical in all three files. Never change `project.key`. `status` is `active`, `paused`, or `complete`. `summary` appears only in `roadmap.json`.
3. Every item has an `id`: lowercase kebab-case, unique across all three files, never renamed and never reused. Titles and notes may change; the id stays forever.
4. Allowed item fields: `id`, `title`, `group`, `notes`, plus:
   - `completedAt` (required in `completed.json`)
   - `cancelledAt` and optional `reason` (in `cancelled.json`)
   - No other fields.
5. **Move semantics:** finish → move to end of `completed.json` + `completedAt`. Drop → move to end of `cancelled.json` + `cancelledAt` (+ `reason`). Never delete an item. Revive by moving back to `roadmap.json` with the same id and removing cancel fields.
6. Each item is in exactly one file. Split work with **new** ids; do not change what an existing id means.
7. Set `updatedAt` on every file you change (ISO 8601 with UTC offset).
8. Keep `roadmap.json` in priority order. Title ≤ 500 chars; notes/reasons ≤ 20,000; ≤ 2,000 items per file.
9. Valid JSON only: UTF-8, two-space indent, no comments, no trailing commas. Missing file → create with `"items": []`.
10. Update the roadmap in the same change as the work; mark completed only when the work is actually done.

## Minimal valid examples

### `roadmap/roadmap.json`

```json
{
  "schema": "name-roadmap/v1",
  "file": "roadmap",
  "updatedAt": "2026-11-11T23:09:23+11:00",
  "project": {
    "key": "c-ompact",
    "title": "c++ompact",
    "status": "active",
    "summary": "C++17 Huffman compression CLI built with CMake."
  },
  "items": [
    {
      "id": "example-todo",
      "title": "Fix an example issue",
      "group": "correctness",
      "notes": "Highest priority first."
    }
  ]
}
```

### `roadmap/completed.json`

```json
{
  "schema": "name-roadmap/v1",
  "file": "completed",
  "updatedAt": "2026-11-11T23:09:23+11:00",
  "project": {
    "key": "c-ompact",
    "title": "c++ompact",
    "status": "active"
  },
  "items": [
    {
      "id": "example-done",
      "title": "Ship encode CLI",
      "group": "cli",
      "notes": "Documented in README.",
      "completedAt": "2026-11-11T23:09:23+11:00"
    }
  ]
}
```

### `roadmap/cancelled.json`

```json
{
  "schema": "name-roadmap/v1",
  "file": "cancelled",
  "updatedAt": "2026-11-11T23:09:23+11:00",
  "project": {
    "key": "c-ompact",
    "title": "c++ompact",
    "status": "active"
  },
  "items": []
}
```

## This project’s identity

| Field | Value |
|-------|--------|
| `project.key` | `c-ompact` |
| `project.title` | `c++ompact` |
| Live files | [roadmap.json](../roadmap/roadmap.json), [completed.json](../roadmap/completed.json), [cancelled.json](../roadmap/cancelled.json) |

Agent-facing copy of these rules: [AGENTS.md](../AGENTS.md).
