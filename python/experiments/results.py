from dataclasses import dataclass,field
from pathlib import Path

@dataclass
class ExperimentConfig:
    executable_path : Path
    runs : list[tuple[Path,str,int]]
    output_path : Path
    
@dataclass
class RunResult:
    matrix : Path 
    method : str
    elapsed_ms : float 
    fill_count : int 

@dataclass
class ExperimentResults:
    results : list[RunResult] = field(default_factory=list)
    
    
    
    
    