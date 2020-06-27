import pandas as pd
import numpy as np

import matplotlib.pyplot as plt
import argparse as ap

import omnetpp as op

p = ap.ArgumentParser()

p.add_argument("csv_file")
p.add_argument("out_file")

args = p.parse_args()

# run `scavetool x <*.vec-file> -o <*.csv-file>` beforehand

df = pd.read_csv(
    args.csv_file,
    converters={
        'attrvalue': op.parse_if_number,
        'binedges': op.parse_ndarray,
        'binvalues': op.parse_ndarray,
        'vectime': op.parse_ndarray,
        'vecvalue': op.parse_ndarray
    }
).dropna(subset=['vecvalue'])

print(df)
plt.hist(
    df.iloc[0].vecvalue,
    bins=16
)


plt.savefig(args.out_file)
