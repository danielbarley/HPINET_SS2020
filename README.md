# OMNeT++ Projects for HPINET SS2020

## Usage

- Set OMNeT++ Wordir to repo root

- If a Project does not show up:
  - Create a new `OMNeT++ Project` (`File > New > OMNet++ Project`)
  - Set its name to the missing project
  - Setup as empty (as to not overwrite any project file)

## Simulation w/o OMNeT++ Eclipse IDE

- in `<project-root>` run

```bash
cd src
opp_makemake -f
make MODE=release clean all
```

- then invoke simulator w/

```bash
cd ../simulations
../src/<proj_name> -n .:../src
```
