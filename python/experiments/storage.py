from results import ExperimentResults, RunResult
from pathlib import Path
import csv

def write_out(exp_res : ExperimentResults,output_path : Path):
    with open(output_path, "w",newline = "") as file:
        writer = csv.writer(file)
        writer.writerow(["matrix","method","elapsed_ms","fill_count"])
        for result in exp_res.results:
            writer.writerow([result.matrix,result.method,result.elapsed_ms,result.fill_count])
    