import json
import os
import re

SRC_DIR = "./src"
JSON_FILE = "functions.json"
README_FILE = "README.md"

PATTERN = re.compile(
    r"//\s*@original:\s*(0x[0-9a-fA-F]+)(?:\s*@status:\s*(wip|done))?", re.IGNORECASE
)


def get_implemented_functions():
    implemented = {}
    for root, _, files in os.walk(SRC_DIR):
        for file in files:
            if file.endswith((".cpp", ".c", ".h", ".hpp")):
                filepath = os.path.join(root, file)
                with open(filepath, "r", encoding="utf-8") as f:
                    for line in f:
                        match = PATTERN.search(line)
                        if match:
                            addr = hex(int(match.group(1), 16))
                            status = match.group(2).lower() if match.group(2) else "wip"
                            implemented[addr] = status

    return implemented


def replace_between_markers(text, start_marker, end_marker, replacement):
    start_idx = text.find(start_marker)
    end_idx = text.find(end_marker)

    if start_idx == -1 or end_idx == -1:
        return text

    return (
        text[: start_idx + len(start_marker)]
        + "\n"
        + replacement
        + "\n"
        + text[end_idx:]
    )


def main():
    if not os.path.exists(JSON_FILE):
        print(f"Could not find {JSON_FILE}")
        return

    with open(JSON_FILE, "r", encoding="utf-8") as f:
        all_funcs = json.load(f)

    func_dict = {}
    total_funcs = len(all_funcs)
    total_size = 0

    for f in all_funcs:
        addr = hex(int(f["address"], 16))
        func_dict[addr] = f["size"]
        total_size += f["size"]

    implemented = get_implemented_functions()

    stats = {
        "done": {"count": 0, "size": 0},
        "wip": {"count": 0, "size": 0},
        "missing": {"count": 0, "size": 0},
    }

    for addr, size in func_dict.items():
        if addr in implemented:
            status = implemented[addr]
            stats[status]["count"] += 1
            stats[status]["size"] += size
        else:
            stats["missing"]["count"] += 1
            stats["missing"]["size"] += size

    done_pct = (stats["done"]["size"] / total_size) * 100 if total_size else 0
    wip_pct = (stats["wip"]["size"] / total_size) * 100 if total_size else 0
    missing_pct = (stats["missing"]["size"] / total_size) * 100 if total_size else 0

    top_badges_markdown = f"""![Done](https://img.shields.io/badge/Done-{done_pct:.3f}%25-success)
![WIP](https://img.shields.io/badge/WIP-{wip_pct:.3f}%25-yellow)
![Missing](https://img.shields.io/badge/Missing-{missing_pct:.3f}%25-red)"""

    table_markdown = f"""
| Status | Functions | Bytes | Percentage |
| :--- | ---: | ---: | ---: |
| 🟢 **Done** | {stats["done"]["count"]:,} | {stats["done"]["size"]:,} | {done_pct:.3f}% |
| 🟡 **WIP** | {stats["wip"]["count"]:,} | {stats["wip"]["size"]:,} | {wip_pct:.3f}% |
| 🔴 **Missing** | {stats["missing"]["count"]:,} | {stats["missing"]["size"]:,} | {missing_pct:.3f}% |
| 📊 **Total** | **{total_funcs:,}** | **{total_size:,}** | **100%** |
"""

    with open(README_FILE, "r", encoding="utf-8") as f:
        readme_content = f.read()

    readme_content = replace_between_markers(
        readme_content,
        "<!-- TOP_BADGES_START -->",
        "<!-- TOP_BADGES_END -->",
        top_badges_markdown,
    )
    readme_content = replace_between_markers(
        readme_content,
        "<!-- PROGRESS_START -->",
        "<!-- PROGRESS_END -->",
        table_markdown,
    )

    with open(README_FILE, "w", encoding="utf-8") as f:
        f.write(readme_content)


if __name__ == "__main__":
    main()
