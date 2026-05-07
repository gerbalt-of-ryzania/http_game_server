# Game Server

C++20 HTTP backend for a multiplayer dog courier game. The server loads maps from a JSON
configuration file, serves the browser client from `static/`, exposes a REST API for game
state and movement, generates loot, handles collection/return scoring, and persists retired
player records in PostgreSQL.

## Highlights

- Asynchronous HTTP server in C++20 using Boost.Asio/Beast
- REST API with token-based player sessions
- PostgreSQL persistence with indexed leaderboard queries
- Dockerized deployment
- Unit and integration tests
- CI pipeline with build/test/static analysis

## Features

- HTTP server built on Boost.Asio/Boost.Beast.
- Static file hosting for the bundled web client.
- JSON map loading with roads, buildings, offices, loot types, dog speed, and bag capacity.
- Player join, movement, game state, manual or automatic ticking, and leaderboard endpoints.
- Loot generation, collision-based pickup, office returns, scoring, and bag limits.
- Idle player retirement: dogs that remain stopped for 60 seconds leave the game and are saved
  to the records table.
- PostgreSQL persistence through `libpqxx`.
- Catch2 unit tests for model behavior and loot generation.

## Project Layout

```text
.
|-- CMakeLists.txt
|-- conanfile.txt
|-- Dockerfile
|-- data/
|   `-- config.json
|-- src/
|   |-- main.cpp
|   |-- request_handler.*
|   |-- model.*
|   |-- json_loader.*
|   |-- records_repository.*
|   `-- ...
|-- static/
|   |-- index.html
|   |-- game.html
|   `-- js/, assets/, images/
`-- tests/
    |-- loot_generator_tests.cpp
    `-- model-tests.cpp
```

## Requirements

- C++20 compiler.
- CMake 3.11 or newer.
- Conan 1.x.
- PostgreSQL server.
- Dependencies from `conanfile.txt`:
  - Boost 1.78.0
  - Catch2 3.1.0
  - libpqxx 7.7.5

## Build

From the repository root:

```bash
mkdir build
cd build
conan install .. -s build_type=Release --build=missing
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

On Linux with GCC, if Conan selects the old standard library ABI, use:

```bash
conan profile update settings.compiler.libcxx=libstdc++11 default
```

The build creates:

- `game_server`
- `game_server_tests`

## Database

The server requires a PostgreSQL connection string in `GAME_DB_URL`.

Example local database with Docker:

```bash
docker run --name game-postgres \
  -e POSTGRES_DB=game \
  -e POSTGRES_USER=game \
  -e POSTGRES_PASSWORD=game \
  -p 5432:5432 \
  -d postgres:15
```

Then set:

```bash
export GAME_DB_URL="postgres://game:game@localhost:5432/game"
```

On PowerShell:

```powershell
$env:GAME_DB_URL = "postgres://game:game@localhost:5432/game"
```

The application creates this table automatically if it does not exist:

```sql
retired_players(id, name, score, play_time_ms)
```

## Run

```bash
./game_server --config-file ../data/config.json --www-root ../static
```

On Windows from `build/`:

```powershell
.\game_server --config-file ..\data\config.json --www-root ..\static
```

The server listens on:

```text
http://localhost:8080
```

Useful options:

```text
-h, --help                    Show help
-c, --config-file <path>      Path to map configuration JSON
-w, --www-root <path>         Static file root
-t, --tick-period <ms>        Advance the game automatically every N milliseconds
--randomize-spawn-points      Spawn dogs at random road positions
```

If `--tick-period` is omitted, the debug endpoint `/api/v1/game/tick` is enabled and the client
or tests can advance time manually. If `--tick-period` is provided, manual HTTP ticks are disabled.

## Run With Docker

Build the image:

```bash
docker build -t game-server .
```

Run it with a reachable PostgreSQL connection string:

```bash
docker run --rm -p 8080:8080 \
  -e GAME_DB_URL="postgres://game:game@host.docker.internal:5432/game" \
  game-server
```

The Docker image starts the server with:

```text
--config-file /app/data/config.json --www-root /app/static
```

## Tests

After building:

```bash
cd build
ctest --output-on-failure
```

Or run the test binary directly:

```bash
./game_server_tests
```

## API

All API responses are JSON and include `Cache-Control: no-cache`.

### Maps

```http
GET /api/v1/maps
```

Returns a short list of maps:

```json
[
  { "id": "map1", "name": "Map 1" }
]
```

```http
GET /api/v1/maps/{mapId}
```

Returns roads, buildings, offices, and loot type metadata for one map.

### Join Game

```http
POST /api/v1/game/join
Content-Type: application/json

{
  "userName": "Tuzik",
  "mapId": "map1"
}
```

Response:

```json
{
  "authToken": "32_hex_character_token",
  "playerId": 0
}
```

### Authenticated Requests

The following endpoints require:

```http
Authorization: Bearer <authToken>
```

### Players

```http
GET /api/v1/game/players
```

Returns players on the current player's map:

```json
{
  "0": { "name": "Tuzik" }
}
```

### Game State

```http
GET /api/v1/game/state
```

Returns players, positions, speeds, directions, bags, scores, and lost objects:

```json
{
  "players": {
    "0": {
      "pos": [0, 0],
      "speed": [0, 0],
      "dir": "U",
      "bag": [],
      "score": 0
    }
  },
  "lostObjects": {}
}
```

### Player Action

```http
POST /api/v1/game/player/action
Content-Type: application/json
Authorization: Bearer <authToken>

{ "move": "R" }
```

Allowed movement values:

- `"L"`: left
- `"R"`: right
- `"U"`: up
- `"D"`: down
- `""`: stop

Successful response:

```json
{}
```

### Manual Tick

Available only when the server was started without `--tick-period`.

```http
POST /api/v1/game/tick
Content-Type: application/json

{ "timeDelta": 1000 }
```

`timeDelta` is measured in milliseconds.

### Records

```http
GET /api/v1/game/records?start=0&maxItems=100
```

Returns retired player records ordered by highest score, then shortest play time, then name:

```json
[
  {
    "name": "Tuzik",
    "score": 30,
    "playTime": 72.5
  }
]
```

`maxItems` must not exceed `100`.

## Configuration

The game config is stored in `data/config.json`.

Top-level fields:

- `defaultDogSpeed`: default movement speed for maps without `dogSpeed`.
- `defaultBagCapacity`: optional default bag size for maps without `bagCapacity`.
- `dogRetirementTime`: optional idle retirement time in seconds; defaults to `60`.
- `lootGeneratorConfig.period`: average loot generation period in seconds.
- `lootGeneratorConfig.probability`: generation probability.
- `maps`: list of game maps.

Each map can define:

- `id`, `name`
- `dogSpeed`
- `bagCapacity`
- `lootTypes` with visual metadata and score `value`
- `roads`
- `buildings`
- `offices`

## Gameplay Notes

- Players spawn at the first road start by default.
- `--randomize-spawn-points` changes spawning to a random road position.
- Dogs move only along roads and stop at road boundaries.
- Loot appears on roads and can be collected while moving through it.
- Returning to an office transfers bag item values into the player's score.
- A stopped dog retires after `dogRetirementTime` seconds, leaves active game state, and is stored in PostgreSQL.
