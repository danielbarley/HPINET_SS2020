import pandas as pd
import numpy as np
import glob
import subprocess as sp
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages


def parse_if_number(s):
    try:
        return float(s)
    except Exception as _:
        return True if s == "true" else False if s == "false" else s if s else None


def parse_ndarray(s):
    return np.fromstring(s, sep=' ') if s else None

if __name__ == "__main__":
    plt.style.use("bmh")
    for file in glob.glob("ueb05/simulations/results/*.vec"):
        complete = {}

        csv_file = file.split(".")[0] + ".csv"
        sp.call(['scavetool', 'x', file, '-o', csv_file])

        df = pd.read_csv(
            csv_file,
            converters={
                'attrvalue': parse_if_number,
                'binedges': parse_ndarray,
                'binvalues': parse_ndarray,
                'vectime': parse_ndarray,
                'vecvalue': parse_ndarray
            }
        ).dropna(subset=['vecvalue'])

        print(df.columns)
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
        print(complete)
        with PdfPages(file.split(".")[0].replace("#", "") + ".pdf") as pdf:
            for name in complete:
                plt.figure(figsize=(19.2/2, 10.8/2))
                plt.style.use("bmh")
                for mod in [m for m in complete[name] if not m.endswith(".t")]:
                    times = complete[name][mod+".t"]
                    vals = complete[name][mod]
                    plt.errorbar(
                        1e3*np.mean(times[:len(times)-len(times)%10].reshape(-1, 10), axis=1),
                        np.mean(vals[:len(vals)-len(vals)%10].reshape(-1, 10), axis=1),
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
