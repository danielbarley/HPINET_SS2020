import pandas as pd
import omnetpp as op
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv(
    './03.csv',
    converters={
        'attrvalue': op.parse_if_number,
        'binedges': op.parse_ndarray,
        'binvalues': op.parse_ndarray,
        'vectime': op.parse_ndarray,
        'vecvalue': op.parse_ndarray
    }
).dropna(subset=['vecvalue'])

# Busy Times
avgs0 = []
avgs1 = []
binsize = 200  # us

print(df['name'])
plt.figure(figsize=(16, 12))

for modnum, mod in enumerate(['Net2.node0.buffer', 'Net2.node1.buffer']):
    avgs = []
    series = df[df['module'] == mod][df['name'] == 'statBusyLine:vector'].iloc[0]['vecvalue'][:-1]
    for i, v in enumerate(series):
        if i % binsize == 0:
            avgs.append(v)
        else:
            avgs[i // binsize] += v

    plt.errorbar(
        np.arange(0, len(avgs) * binsize / 1000, binsize / 1000),
        [float(avg) / binsize*100.0 for avg in avgs],
        c=f"C{modnum}",
        label=mod+".statBusyLine",
        fmt="."
    )

    plt.axhline(
        sum(series)*100 / len(series),
        c=f"C{modnum}",
        ls=":",
        label=mod+".statBusyLine.mean"
    )

plt.xlabel("SimTime / ms")
plt.ylabel(f"Busy / % (avg over {binsize}$\mu$s)")
plt.legend()
plt.savefig("03_01.pdf")
plt.clf()

# Queue Size
binsize = 100  # us
stat = 'statNumInQueue'


for modnum, mod in enumerate(['Net2.node0.buffer', 'Net2.node1.buffer']):
    avgs = []
    mins = []
    maxs = []
    tavgs = []
    series = df[df['module'] == mod][df['name'] == stat+':vector'].iloc[0]['vecvalue'][:-1]
    for i, v in enumerate(series):
        if i % binsize == 0:
            avgs.append(v)
            mins.append(v)
            maxs.append(v)
        else:
            avgs[i // binsize] += v
            maxs[i // binsize] = max(v, maxs[i // binsize])
            mins[i // binsize] = min(v, maxs[i // binsize])

    for i, v in enumerate(
        df[df['module'] == mod][df['name'] == stat+':vector'].iloc[0]['vectime'][:-1]):
        if i % binsize == 0:
            tavgs.append(v)
        else:
            tavgs[i // binsize] += v

    plt.errorbar(
        # np.arange(0, len(avgs) * binsize / 1000, binsize / 1000),
        [tavg/binsize for tavg in tavgs],
        [avg/binsize for avg in avgs],
        c=f"C{modnum}",
        label=mod+"."+stat,
        fmt="."
    )

    plt.axhline(
        sum(series) / len(series),
        c=f"C{modnum}",
        ls=":",
        label=mod+"."+stat+".mean"
    )

    plt.axhline(
        max(series),
        c=f"C{modnum}",
        ls="dashed",
        label=mod+"."+stat+".max"
    )

plt.xlabel("SimTime / ms")
plt.ylabel(f"Queue Size / Packets (avg over {binsize}$\mu$s)")
plt.legend()
plt.savefig("03_02.pdf")

# Num Discarded
binsize = 50  # us
stat = 'statNumDiscarded'


# for modnum, mod in enumerate(['Net2.node0.buffer', 'Net2.node1.buffer']):
    # series = df[df['module'] == mod][df['name'] == stat+':vector'].iloc[0]['vecvalue'][:-1]
    # tseries = df[df['module'] == mod][df['name'] == stat+':vector'].iloc[0]['vectime'][:-1]

    # plt.errorbar(
        # tseries,
        # series,
        # c=f"C{modnum}",
        # label=mod+"."+stat,
        # fmt="."
    # )

    # plt.axhline(
        # sum(series) / len(series),
        # c=f"C{modnum}",
        # ls=":",
        # label=mod+"."+stat+".mean"
    # )

# plt.xlabel("SimTime / ms")
# plt.ylabel("Busy / %")
# plt.legend()
# plt.show()
