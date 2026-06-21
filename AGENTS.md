# RespiroMeter/RespiroGui

## Architecture

**Two separate git repos**:
- `/respiro` - R backend package (R6 classes, hardware control, measurement logic)
- `/RespiroGui` - C++/QML frontend (Qt6 app with RInside embedding R)

**Communication pattern**: GUI → R via RInside callbacks, R → GUI via Qt signals/slots.

## Key entrypoints

- **Qt**: `main.cpp:main()` → `Respiro`, `RWrapper`, `MainModel`
- **R**: `respiro::RespiroControl` singleton, `RespiroChannel` ×14
- **GUI model**: `Respiro` (QAbstractListModel) exposes `_channels` vector via `data()`/`roleNames()`

## Critical context

1. **Status determination**: R side (`pushChannelStatus()` in respiroChannel.R) computes status, statusText, and color based on `leakPass`, `pressPass`, `inExperiment`. C++/QML only displays.

2. **Channel vs ChannelConf**:
   - `_channelConfs` in Respiro: static config (sampleID, thresholds, volPass, etc.)
   - `_channels` in Respiro: live Channel objects with statusText, color Q_PROPERTYs

3. **QML ListView**: `ChannelStatusses.qml` uses `respiro` as model, delegate is `ChannelStatus { }`. Qt auto-binds modelData (Channel object) to delegate properties.

4. **R active bindings**: `leakPass`, `pressPass`, `inExperiment`, `statusText`, `color` all push to GUI via `pushChannelStatus()`, `pushChannelStatusText()`, `pushChannelColor()`.

5. **Build**: `cmake . && make` in build directory. Requires R, RInside, SQLite3, Qt6.

6. **Hardware**: Controllino Mega over USB serial. Simulator available via `ArduinoSimulator` for testing.

## Build & run

```bash
cd /home/virtuoos/RespiroMeter/RespiroGui
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=DEBUG
make -j$(nproc)
./qmlR
```

## R environment

```r
# In /respiro
renv::restore(prompt = FALSE)
pkgload::load_all()
```

## Status mapping (R side)

```r
status <- case_when(
  inExperiment == 0 ~ "idle",
  inExperiment == 1 & leakPass == 1 & pressPass == 1 ~ "ok",
  inExperiment == 1 & is.na(pressPass) ~ "not_tested",
  inExperiment == 1 & leakPass == 0 & pressPass == 1 ~ "leak_fail",
  inExperiment == 1 & pressPass == 0 & leakPass == 0 ~ "press_fail"
)

color <- case_when(
  status == "ok"        ~ "#4CAF50",
  status == "idle"      ~ "#BDBDBD",
  status == "leak_fail" ~ "#F42336",
  status == "press_fail"~ "#F41336",
  status == "not_tested"~ "#FFEB7F"
)
```

## Important files

| Path | Purpose |
|------|---------|
| `main.cpp` | Qt main, RInside init, signal/slot wiring |
| `respiro.cpp/h` | C++ model, channel management, DB access |
| `channel.cpp/h` | Channel class with statusText/color properties |
| `rwrapper.cpp/h` | RInside glue, callback registrations |
| `respiroChannel.R` | R6 class, leak/volume tests, measure, calculate |
| `respiroControl.R` | Main controller, session lifecycle |
| `ChannelStatusses.qml` | ListView showing channel status delegates |
