import sys
import time
import signal

def signal_handler(sig, a):
    print("Signal received, shutting down python process...")
    sys.exit(0)

# Register signal handlers
signal.signal(signal.SIGINT, signal_handler)  # Handle Ctrl+C
signal.signal(signal.SIGTERM, signal_handler)  # Handle termination signals



print("cart curt", file = sys.stdout)

time.sleep(3)

print("anan", file = sys.stdout)