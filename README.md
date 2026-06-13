# img4dc — Dreamcast Selfboot Toolkit (Linux Port)

This is a Linux port of [img4dc](https://sourceforge.net/projects/img4dc/) by SiZiOUS,
forked from [Kazade/img4dc](https://github.com/Kazade/img4dc), which switched the build
system to CMake and made the code compile on Linux.

## Why does this exist?

The original img4dc was Windows-only (CodeLite IDE, TDM-GCC, `windres`). The Kazade fork
was created to **programmatically compile img4dc inside a Docker container** — enabling
automated Dreamcast disc image builds in CI/CD pipelines without a Windows dependency.

If you're building Dreamcast homebrew in CI, you can now drop these tools into a
`debian:bookworm` Docker image and generate CDI/MDS files from your built ISOs
automatically.

If you're on **Windows**, use the [upstream release](https://sourceforge.net/projects/img4dc/)
instead — it has the original tooling and is better tested.

## Tools included

| Tool | Description |
|------|-------------|
| `cdi4dc` | Generates valid Padus DiscJuggler (CDI) images from an ISO |
| `mds4dc` | Generates valid Alcohol 120% (MDS/MDF) images from an ISO + RAW audio tracks |
| `lbacalc` | Computes the MSINFO value for `mkisofs -C` from RAW audio track sizes |

All three tools are **post-processors** — you create the ISO first with
`mkisofs`/`genisoimage`/`xorriso`, then feed it to `cdi4dc` or `mds4dc`.

## Building on Linux

### Prerequisites

```bash
apt install cmake gcc libc6-dev
```

### Build

```bash
git clone git@github.com:Conkwer/img4dc.git
cd img4dc
mkdir build && cd build
cmake ..
make
```

Binaries end up in `build/cdi4dc/cdi4dc`, `build/mds4dc/mds4dc`, and
`build/lbacalc/lbacalc`.

Pre-built Linux x86_64 binaries are also available in `bin/`.

### Install (optional)

```bash
cd build && sudo make install  # not yet implemented upstream
```

## What was fixed for Linux

* **`-D_DEFAULT_SOURCE`** — POSIX functions (`strdup`, `realpath`, `strcasecmp`) were
  implicitly declared under `-std=c99`, which on 64-bit Linux causes the compiler to
  assume they return `int` — truncating pointers and producing corrupt output.
* **`lbacalc` wired up** — the original depended on `fileutil.h` and `version.h` which
  were part of the author's private CodeLite workspace and never published. Recreated
  `fsize()` via `stat(2)` and inlined `get_version()` to replace the missing
  `windres`-generated `version.rc`.
* **Type fix in lbacalc** — `uint32_t filesize` could never match the `-1` error
  check (unsigned wraparound). Changed to `long`.
* **CMake build system** — replaced the Windows CodeLite `.mk`/`.project` files.

## Status

**Untested.** The tools compile cleanly on Linux (Debian 12, GCC 12.2, x86_64) and
print their usage text correctly, but no Dreamcast disc images have been verified
with this build. The original `unsigned long` → `uint32_t` fixes in the CDI/MDS
writers should produce correct output, but **test before relying on it.**

This port targets **Linux**. macOS may work (the Kazade fork was designed for it) but
is untested. Windows is unsupported — use the upstream release.

## License

GNU GPL v3. See `license.txt`.

## Credits

* **SiZiOUS** — original img4dc author (cdi4dc, mds4dc, lbacalc)
* **Kazade** — CMake conversion and initial Linux port, `uint32_t` fixes
* **libedc** — ripped from cdrtools by Heiko Eissfeldt and Joerg Schilling
