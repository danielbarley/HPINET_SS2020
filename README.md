# OMNeT++ Projects for HPINET SS2020

## Usage

- Set OMNeT++ workdir to repo root

- If a Project does not show up:
  - Create a new `OMNeT++ Project` (`File > New > OMNet++ Project`)
  - Set its name to the missing project
  - Setup as empty (as to not overwrite any project file)

## Simulation w/o OMNeT++ Eclipse IDE

- in `<project-root>` run

```bash
opp_makemake -f --deep
cd src
make MODE=release all
```

- then invoke simulator w/

```bash
cd ../simulations
../src/<proj_name> -n .:../src
```

## Statistics w/ Python

1) run `scavetool x <vec-file> -o <csv-file>`
2) use `<csv-file>` in python e.g.:

```bash
python python/main.py <csv-file> <output-pdf>
```

## References

- [Simulation Manual](https://doc.omnetpp.org/omnetpp/manual/)
- [Users's Guide](https://inet.omnetpp.org/docs/users-guide/index.html)
- [INET Framework](https://doc.omnetpp.org/inet/api-current/neddoc/index.html)
- [Result Analysis w/ Python](https://docs.omnetpp.org/tutorials/pandas/)
