import pandas as pd
import numpy as np


def parse_if_number(s):
    try:
        return float(s)
    except Exception as _:
        return True if s == "true" else False if s == "false" else s if s else None


def parse_ndarray(s):
    return np.fromstring(s, sep=' ') if s else None
