# World Data Storage Format (Register + Per-Map Files)

## Goal

Split world storage into two concerns:

1. A **map register** that stores only catalog metadata and file references.
2. One **data file per map** containing that map's terrain payload.

This avoids mixing index-offset and per-file patterns in the same format.

---

## Pattern Decision

Use **manifest/register + per-map file**.

- Keep in register: identity, dimensions, flags, map filename, optional per-map version/hash.
- Remove from register: payload offsets/sizes used for monolithic blob layout.

If offsets/sizes are needed later, they should belong inside each map file's own chunk/table format, not the global register.

---

## Files

Expected files under `assets\\world\\`:

- `map_register.jpup` (new)
- `map_<id>.jpup` (one file per map)
- optional: `entity_register.jpup` and per-map/per-entity files later

Example:

- `map_register.jpup`
- `map_0001.jpup`
- `map_0002.jpup`

---

## Binary Schema

All integer fields are **little-endian**.

### Register Header (`map_register.jpup`)

| Field | Type | Notes |
|---|---|---|
| signature | `uint32_t` | Suggested: `'MREG'` (0x4745524D) |
| version   | `uint16_t` | Start at `1` |
| reserved  | `uint16_t` | Must be `0`  |
| mapCount  | `uint32_t` | Number of register entries |

Header size: **12 bytes**.

### Register Entry v1

Use fixed-size entries for easy random access and simple parsing.

|   Field      | Type       | Notes                                  |
|--------------|------------|----------------------------------------|
|   mapId      | `uint32_t` | Stable identifier (savegame-safe)      |
|   width      | `uint16_t` | Terrain X extent                       |
|   length     | `uint16_t` | Terrain Z extent                       |
|   flags      | `uint32_t` | Gameplay/render flags                  |
| dataVersion  | `uint16_t` | Version of map payload file format     |
|   nameLen    | `uint8_t`  | Bytes in `fileName` excluding terminator |
|   reserved   | `uint8_t`  | Must be `0`                            |
| fileName[48] | `char[48]` | UTF-8, NUL-terminated if shorter       |

Entry size: **64 bytes**.

Validation:

- `nameLen` must be `> 0` and `< 48`.
- `fileName[nameLen]` should be `\0` after normalization.
- reject path traversal (`..`, drive prefixes, absolute paths).

### Per-Map File (`map_<id>.jpup`)

Keep map file independently versioned.

| Field | Type | Notes |
|---|---|---|
| signature | `uint32_t` | Suggested: `'MAPD'` (0x4450414D) |
| version | `uint16_t` | Start at `1` |
| reserved | `uint16_t` | Must be `0` |
| mapId | `uint32_t` | Must match register entry |
| width | `uint16_t` | Can be cross-validated with register |
| length | `uint16_t` | Can be cross-validated with register |
| payloadSize | `uint32_t` | Number of payload bytes following header |
| payload[...] | bytes | Terrain encoding data |

Header size before payload: **20 bytes**.

---

## C Struct Targets

Suggested replacements for existing map key structure:

```c
typedef struct MapEntry_t {
    uint32_t mapId;
    uint16_t width;
    uint16_t length;
    uint32_t flags;
    uint16_t dataVersion;
    uint8_t  nameLen;
    char     fileName[48];
} MapEntry_t;
```

World state:

```c
typedef struct World_t {
    MapEntry_t* mapEntries;
    uint32_t mapCount;
    Terrain_t* currentMap;
} World_t;
```

---

## API Transition Plan

Current APIs are inconsistent (`ParseMap`, `ParseMapRegister`, `ParseMapHeader`).

Standardize to:

```c
uint8_t ParseMapRegister(World_t* world);
Terrain_t* LoadMapByIndex(World_t* world, uint32_t mapIndex);
Terrain_t* LoadMapById(World_t* world, uint32_t mapId);
void FreeMapRegister(World_t* world);
```

Recommended behavior:

- `ParseMapRegister`:
  - reads `map_register.jpup`
  - validates header + each entry
  - allocates and sets `world->mapEntries`, `world->mapCount`
  - returns non-zero on failure

- `LoadMapByIndex`:
  - bounds check index
  - resolve `fileName` from register entry
  - open per-map file and validate map header
  - verify `mapId` and dimensions against register entry
  - build `Terrain_t`

- `LoadMapById`:
  - linear search first (can optimize with hash later)

---

## Error and Validation Rules

1. Register parse fails hard on bad signature/version.
2. Entry-level failures may either:
   - fail fast (simpler and safer early on), or
   - skip invalid entries with warning (later if needed).
3. Reject empty map files or payload-size mismatches.
4. Keep loader path sandboxed to `assets\\world\\`.

---

## Migration Steps (Low Risk)

1. Introduce new structs + constants in `mapio.h` without deleting old fields yet.
2. Implement register parsing for v1 and populate `world->mapEntries`.
3. Update world creation to call only `ParseMapRegister`.
4. Replace offset/size map loading with filename-based loading.
5. Remove old `offset`/`size` fields and dead parser code.
6. Add tiny test register with 1-2 map entries and verify load paths.

---

## Why This Fits Your Engine

- Better source control diffs: each map changes independently.
- Better streaming and patching: load only selected map file.
- Better fault isolation: one corrupt map file does not invalidate all maps.
- Cleaner format ownership: register indexes maps, map file owns payload layout.

---

## Optional Next Upgrade

When entity system expands, mirror this with:

- `entity_register.jpup` (catalog)
- `entity_<id>.jpup` or `entities_map_<mapId>.jpup`

The same header/version strategy can be reused.