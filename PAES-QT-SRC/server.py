
import socket
import cv2
import struct
import time
import sys  # Import sys to read command-line arguments
import signal

vid = None

def set_frame_rate(fps):
    return 1 / float(fps)

def signal_handler(sig, frame):
    print("Signal received, shutting down...")
    if server_socket:
        server_socket.close()
    if vid:
        vid.release()

    sys.exit(0)

# Register signal handlers
signal.signal(signal.SIGINT, signal_handler)  # Handle Ctrl+C
signal.signal(signal.SIGTERM, signal_handler)  # Handle termination signals

if len(sys.argv) != 2:
    print("Usage: python script_name.py <IP Address>")
    sys.exit()

host_ip = sys.argv[1]  # Get the IP address from command-line arguments
port = 4545
socket_address = (host_ip, port)

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  # Make socket address reusable
server_socket.bind(socket_address)
server_socket.listen(5)
print("LISTENING AT:", socket_address)

# Frame rate control
fps = 10  # Frames per second
frame_interval = set_frame_rate(fps)
last_frame_time = time.time()

# Socket Accept
while True:
    client_socket, addr = server_socket.accept()
    print('GOT CONNECTION FROM:', addr)
    if client_socket:
        vid = cv2.VideoCapture(0)

        while vid.isOpened():
            ret, frame = vid.read()
            if not ret:
                break

            current_time = time.time()
            if (current_time - last_frame_time) >= frame_interval:
                # Resize the frame to lower the resolution
                frame = cv2.resize(frame, (320, 240))  # Reduced resolution

                # Flip the frame horizontally
                flipped_frame = cv2.flip(frame, 1)

                # Encode the frame in JPEG format with reduced quality
                _, buffer = cv2.imencode('.jpg', flipped_frame, [int(cv2.IMWRITE_JPEG_QUALITY), 80])
                frame_data = buffer.tobytes()

                # Pack the length of the frame and the frame itself
                message = struct.pack("Q", len(frame_data)) + frame_data
                # Send the packed message
                client_socket.sendall(message)

                last_frame_time = current_time  # Update the last frame time

            key = cv2.waitKey(1) & 0xFF
            if key == ord('q'):
                client_socket.close()
                break

        vid.release()


