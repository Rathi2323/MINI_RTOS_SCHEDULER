import subprocess
import time
import sys
from colorama import Fore, Style, init

# Initialize colorama for colored console output
init(autoreset=True)

def colorize_output(line: str) -> str:
    """Adds color to different ECU logs based on keywords."""
    if "[ENGINE ECU]" in line:
        return Fore.RED + line
    elif "[TEMP_SENSOR]" in line:
        return Fore.YELLOW + line
    elif "[DASHBOARD]" in line:
        return Fore.CYAN + line
    elif "[BUS]" in line:
        return Fore.GREEN + line
    elif "[RTOS]" in line:
        return Fore.MAGENTA + line
    else:
        return Fore.WHITE + line

def run_simulation():
    exe_path = "../output/MiniRTOS_CAN.exe"

    print(Fore.MAGENTA + "🚀 Starting Mini RTOS CAN Simulation (C Binary)...\n")
    print(Fore.WHITE + "---------------------------------------------")

    # Start the C program and capture stdout
    process = subprocess.Popen(
        [exe_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1
    )

    log_file = open("simulation_log.txt", "w")

    try:
        for line in process.stdout:
            colored_line = colorize_output(line.strip())
            print(colored_line)
            log_file.write(line)
            log_file.flush()
            time.sleep(0.5)  # simulate streaming feel
    except KeyboardInterrupt:
        print(Fore.RED + "\n🛑 Simulation stopped by user.")
        process.terminate()
    finally:
        log_file.close()
        print(Fore.MAGENTA + "\n📁 Simulation log saved to simulation_log.txt")

if __name__ == "__main__":
    run_simulation()
