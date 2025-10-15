# Simple Persistent Key-Value Store
import os, sys

DB_FILE = "data.db"

# store list of (key, value)
store = []

# read existing file (persistence)
if os.path.exists(DB_FILE):
    with open(DB_FILE, "r") as f:
        for line in f:
            parts = line.strip().split(" ", 2)
            if len(parts) == 3 and parts[0] == "SET":
                _, k, v = parts
                store.append((k, v))

# main loop
while True:
    line = sys.stdin.readline()
    if not line:
        break
    parts = line.strip().split(" ", 2)
    if len(parts) == 0:
        continue
    cmd = parts[0].upper()

    if cmd == "EXIT":
        break

    elif cmd == "SET" and len(parts) >= 3:
        k, v = parts[1], parts[2]
        with open(DB_FILE, "a") as f:
            f.write(f"SET {k} {v}\n")
            f.flush()
            os.fsync(f.fileno())
        store.append((k, v))
        print("OK")

    elif cmd == "GET" and len(parts) >= 2:
        k = parts[1]
        value = None
        for key, val in reversed(store):
            if key == k:
                value = val
                break
        print(value if value is not None else "NULL")

    else:
        print("ERR")
