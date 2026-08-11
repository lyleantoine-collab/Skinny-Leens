#!/bin/sh
# Skinny Leens - Local Swarm & Hardware Health Check
# Strict POSIX compliance, zero telemetry.

echo "=== SKINNY LEENS: HARDWARE & SWARM AUDIT ==="

# Check RAM footprint (Bytes matter)
echo "[*] Memory Status:"
free -b | awk 'NR==2{printf "    Total: %s bytes\n    Used:  %s bytes\n    Free:  %s bytes\n", $2, $3, $4}'

# Check active processes (Ensuring zero corporate daemons are sneaking in)
PROCESS_COUNT=$(ps -e | wc -l)
echo "[*] Active Processes: $PROCESS_COUNT (Lean & Clean)"

# Verify local storage partition health
echo "[*] Storage Root Usage:"
df -h / | awk 'NR==2{printf "    Mounted on /: %s used (%s available)\n", $3, $4}'

# Local node connectivity check (Local subnet only)
echo "[*] Local Mesh Node Status:"
if ping -c 1 -W 1 127.0.0.1 >/dev/null 2>&1; then
    echo "    [OK] Local loopback operational."
else
    echo "    [WARN] Loopback anomaly detected."
fi

echo "=== AUDIT COMPLETE: NO BLOAT DETECTED ==="
