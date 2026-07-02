#!/usr/bin/env python3

import os
import subprocess
import sys

from dotenv import load_dotenv

load_dotenv()

ghidra_dir = os.getenv("GHIDRA_INSTALL_DIR")

script = sys.argv[1]
args = sys.argv[2:]

cmd = [
    "python3",
    "-m",
    "pyghidra",
    "--install-dir",
    ghidra_dir,
    script,
] + args

subprocess.run(cmd, check=True)
