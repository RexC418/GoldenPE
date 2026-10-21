# MCPE 0.8.1 + generador de terreno RD-132211

Proyecto listo para compilar en GitHub Actions (APK arm64-v8a, minSdk 24, targetSdk 34).

## Qué hace

- La pantalla de crear mundo tiene un botón nuevo, **Terrain Settings**, bajo la caja *Seed*.
- Abre otra pantalla con **Terrain Generation**: `[◀] [RD-132211] [▶]`. El centro muestra la versión del generador;
  las flechas ya funcionan (recorren la lista de generadores) pero, con un solo generador, no cambian nada.
- Los mundos nuevos usan el generador **RD-132211** (port 1:1 de `Level.java`/`RubyDung.java`):
  mundo de 256 x 256, **42 capas de Cobblestone** (y = 0-41) + **1 capa de Grass Block** (y = 42), cada capa de 1 bloque
  de alto; todo lo demás es aire. Altura máxima de construcción: **64** (no se pueden colocar bloques en y >= 64
  ni fuera de los 256 x 256).
- **Sin Invisible Bedrock**: al salir del mundo se cae al vacío. La muerte de MCPE al caer por debajo de y = 0 se mantiene.
- El spawn queda sobre la hierba en el centro del mundo (128, 43, 128) en vez de una posición aleatoria en el aire.
- Guardado y carga: **el sistema original de MCPE 0.8.1**. Solo se añade la etiqueta `TerrainGenerator` en `level.dat`
  para recordar el generador (y así el vacío sigue funcionando al volver a abrir el mundo). Los mundos antiguos, que no
  tienen la etiqueta, se comportan exactamente como antes.
- Multiplayer LAN: `StartGamePacket` lleva un entero extra al final con el generador. Los clientes originales lo ignoran.

## Compilar en GitHub Actions

1. Sube **todo** el contenido de esta carpeta a un repositorio nuevo **con git** (`git add -A && git commit && git push`).
   `pcm_data.c` pesa unos 31 MB y la web de GitHub solo admite 25 MB por archivo.
2. Actions > *Build APK (arm64-v8a)* > *Run workflow* (también corre solo al hacer push a `main`/`master`).
3. El APK queda en *Artifacts*: `MCPE-0.8.1-RD132211-arm64-v8a`. Es un APK release (código nativo optimizado)
   firmado con la clave de depuración, así que se puede instalar directamente.

Configuración: JDK 17, AGP 8.4.0, Gradle 8.6, NDK 16.1.4479499 (r16b), CMake 3.22.1, runner `ubuntu-24.04`.

## Dónde está cada cosa

Carpeta `app/src/main/cpp/minecraftpe/` (código C++ de MCPE):

| Nuevo | Qué es |
|---|---|
| `headers/level/gen/TerrainGenerator.hpp`, `impl/level/gen/TerrainGenerator.cpp` | Lista de generadores, nombres de versión, selección, constantes de RD-132211 |
| `headers/level/gen/RD132211LevelSource.hpp`, `impl/level/gen/RD132211LevelSource.cpp` | El generador (cada chunk de 16 x 128 x 16) |
| `headers/gui/screens/TerrainSettingsScreen.hpp`, `impl/gui/screens/TerrainSettingsScreen.cpp` | Pantalla *Terrain Settings* |
| `headers/gui/buttons/TerrainSelectorButton.hpp`, `impl/gui/buttons/TerrainSelectorButton.cpp` | Botones del selector `[◀][versión][▶]` |
| `app/src/main/assets/images/gui/terrain_arrows.png` | Triángulos pixelados (misma geometría que las flechas del D-pad original) |

Modificados: `LevelSettings.hpp`, `LevelData.hpp/.cpp` (etiqueta `TerrainGenerator`), `Dimension.cpp` (elige el generador),
`EmptyLevelChunk.hpp` (sin Invisible Bedrock), `Level.hpp/.cpp` (spawn, límite de altura, `hasVoidBorder()`),
`CreateWorldScreen.hpp/.cpp` (botón nuevo), `Touch_SelectWorldScreen.cpp`, `StartGamePacket.hpp`,
`ServerSideNetworkHandler.cpp`, `ClientSideNetworkHandler.cpp`.

Fuera del C++: `app/build.gradle` (minSdk 24, targetSdk 34, solo arm64-v8a, firma del release), `AndroidManifest.xml`
(quitado `<uses-sdk>`; los valores salen de Gradle), `.github/workflows/build-apk.yml`. Se colocaron `res/`, `assets/` y
`pcm_data.c` donde corresponde y se corrigieron dos `.gitignore` que habrían dejado fuera `assets/` y `pcm_data.c`.

## Añadir más generadores en el futuro

1. Añade su id a `TerrainGeneratorType` y su nombre en `getVersionName()` (`TerrainGenerator.cpp`).
2. Añádelo a `selectableGenerators[]`: las flechas ya recorren la lista y el centro muestra el nombre.
3. En `Dimension::createRandomLevelSource()` devuelve su `ChunkSource` para ese id.

## Notas

- En el `Chunk.java` descompilado de rd-132211 los nombres `Tile.rock`/`Tile.grass` parecen invertidos respecto a la capa
  a la que se aplican (la capa superior usa `rock`). Se siguió tu descripción: Cobblestone abajo y Grass Block arriba.
- Mobs: el spawn de MCPE no forma parte del terreno y se dejó como está (según el bioma).
- Los chunks siguen guardándose con la altura de 128 de MCPE (formato de guardado intacto); el límite de 64 se aplica al construir.
