import subprocess
result = subprocess.run(["./build-release/fillmin","./data/benchmarks/bcsstk01.mtx", "mf"],capture_output = True,text=True, check=True)
print(result.stdout)
lines = result.stdout.splitlines()
elapsed_ms = float(lines[0])
fill_count = float(lines[1])
