from experiments.analysis import run_analysis
from experiments.results import ExperimentResults,ExperimentConfig,RunResult
from experiments.runner import run_all,run_once
from experiments.storage import write_out
import json 
from pathlib import Path
import argparse

def load_config(path : Path) -> ExperimentConfig:
    with open(path, "r") as file:
        data = json.load(file)
        exp = ExperimentConfig(Path(data["executable_path"]),[(Path(matrix),method,rep) for matrix,method,rep in data["runs"]],Path(data["output_path"]))
        return exp

def run_experiment(exp : ExperimentConfig):
    res = run_all(exp)
    write_out(res,exp.output_path)
    summary = run_analysis(exp.output_path)
    return summary 

if __name__ == "__main__":
    parser = argparse.ArgumentParser() 
    parser.add_argument("path",type=Path)
    args = parser.parse_args()
    config_path = args.path
    exp = load_config(config_path)
    summary = run_experiment(exp)
    print(summary.to_string(index=False))
    