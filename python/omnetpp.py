import pandas as pd
import numpy as np
import glob
import subprocess as sp
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages


def parse_if_number(s):
    try:
        return float(s)
    except Exception:
        return True if s == "true" else False if s == "false" else s if s else None


def parse_ndarray(s):
    return np.fromstring(s, sep=' ') if s else None


def parse_scaved_file(filename):
    return pd.read_csv(
        csv_file,
        converters={
            'attrvalue': parse_if_number,
            'binedges': parse_ndarray,
            'binvalues': parse_ndarray,
            'vectime': parse_ndarray,
            'vecvalue': parse_ndarray
        }
    ).dropna(subset=['vecvalue'])


if __name__ == "__main__":
    plt.style.use("bmh")
    outdir = "python/results"
    ueb = "ueb05"
    for file in glob.glob(f"{ueb}/simulations/results/*.vec"):
        complete = {}

        basename = file.split("/")[-1].split(".")[0].replace("#", "")

        csv_file = f"{outdir}/{ueb}/{basename}.csv"
        pdf_file = f"{outdir}/{ueb}/{basename}.pdf"

        sp.call(['scavetool', 'x', file, '-o', csv_file])

        df = parse_scaved_file(csv_file)

        for index, row in df.iterrows():
            filter = (row['name'].split(":")[0]
                      + " of " + row['module'].split('.')[2].split("[")[0])
            if complete.get(filter, None) is None:
                complete[filter] = {
                    row['module']: row['vecvalue'],
                    row['module'] + ".t": row['vectime'],
                }
            else:
                complete[filter][row['module']] = row['vecvalue']
                complete[filter][row['module'] + ".t"] = row['vectime']

        with PdfPages(pdf_file) as pdf:
            for name in complete:
                plt.figure(figsize=(19.2 / 2, 10.8 / 2))
                plt.style.use("bmh")
                for mod in [m for m in complete[name] if not m.endswith(".t")]:
                    times = complete[name][mod + ".t"]
                    vals = complete[name][mod]
                    plt.errorbar(
                        1e3 * np.mean(
                            times[:len(times) - len(times) % 10].reshape(-1, 10),
                            axis=1),
                        np.mean(
                            vals[:len(vals) - len(vals) % 10].reshape(-1, 10),
                            axis=1),
                        label=mod,
                        lw="1",
                        markersize="1",
                        alpha=.5
                    )
                plt.title(name)
                plt.legend()
                plt.xlabel("SimTime / ms")
                plt.tight_layout()
                pdf.savefig()
                plt.close()
