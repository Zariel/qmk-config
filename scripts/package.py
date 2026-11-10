"""Package firmware alongside the complete source used to build it."""

import os
from pathlib import Path
import shutil
import tarfile

root = Path(__file__).resolve().parent.parent
firmware = Path(os.environ.get("QMK_HOME", root / "qmk_firmware"))
output = root / "dist"
output.mkdir(exist_ok=True)

binaries = [path for pattern in ("*.uf2", "*.hex", "*.bin") for path in root.glob(pattern)]
if not binaries:
    raise SystemExit("No firmware binaries found; run make build first.")

for binary in binaries:
    shutil.copyfile(binary, output / binary.name)


def source_only(member):
    path = Path(member.name)
    if {".git", ".build", "__pycache__", ".cache"}.intersection(path.parts):
        return None
    if path.parent == Path("qmk_firmware") and path.suffix in {".uf2", ".hex", ".bin", ".elf"}:
        return None
    return member


# An explicit list keeps local credentials and workspace metadata out of releases.
with tarfile.open(output / "firmware-source.tar.gz", "w:gz") as archive:
    for name in (
        "LICENSE", "LICENSES", "README.md", "Makefile", "qmk.mk", "qmk.json",
        "flake.nix", "flake.lock", ".gitignore", ".github", "scripts", "keyboards", "vendor", "backups",
    ):
        archive.add(root / name, arcname=name, filter=source_only)
    archive.add(firmware, arcname="qmk_firmware", filter=source_only)

print(f"Packaged {len(binaries)} firmware file(s) and firmware-source.tar.gz in {output}")
