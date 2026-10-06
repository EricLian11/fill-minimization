from results import ExperimentConfig, RunResult, ExperimentResults
import subprocess

def run_once(ex_path, matrix, method) -> RunResult:
    result = subprocess.run([ex_path,matrix, method],capture_output = True,text=True, check=True)
    lines = result.stdout.splitlines()
    elapsed_ms = float(lines[0])
    fill_count = int(lines[1])
    return RunResult(matrix,method,elapsed_ms,fill_count)

def run_all(experiment : ExperimentConfig) -> ExperimentResults:
    exp_res = ExperimentResults()
    for matrix,method in experiment.runs:
        exp_res.results.append(run_once(experiment.executable_path,matrix,method))
    return exp_res