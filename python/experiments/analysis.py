from pathlib import Path 
import pandas as pd
def run_analysis(path : Path):
    df = pd.read_csv(path)
    grouped = df.groupby(["matrix","method"])
    summary = pd.DataFrame()
    summary["elapsed_median"] = grouped["elapsed_ms"].median()
    summary["elapsed_first_q"] = grouped["elapsed_ms"].quantile(0.25)
    summary["elapsed_third_q"] = grouped["elapsed_ms"].quantile(0.75)
    summary["fill_count"] = grouped["fill_count"].median()
    summary["runs"] = grouped.size()
    
    return summary.reset_index()
