import json
import os

from dotenv import load_dotenv
from ghidra.util.task import ConsoleTaskMonitor
from pyghidra import open_project

load_dotenv()

with open_project(
    os.getenv("GHIDRA_PROJECT_DIR"), os.getenv("GHIDRA_PROJECT_NAME")
) as project:
    df = project.getProjectData().getFile("/SPEED2.EXE")

    program = df.getImmutableDomainObject("me", -1, ConsoleTaskMonitor())

    funcs = []

    fm = program.getFunctionManager()

    for f in fm.getFunctions(True):
        funcs.append(
            {
                "name": f.getName(),
                "address": str(f.getEntryPoint()),
                "size": f.getBody().getNumAddresses(),
            }
        )

    with open("functions.json", "w") as fp:
        json.dump(funcs, fp, indent=2)
