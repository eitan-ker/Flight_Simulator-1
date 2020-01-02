import socket
import logging

TARGET_IP = 'localhost'
TARGET_PORT = 5402

BIND_PORT = 5400
MAX_BACKLOG_SIZE = 5


logging.getLogger().setLevel(logging.INFO)
'''
These are just example client functions.
They will need modifications to work together with the simulator script.

You can first create a server (example is in the recv_data function), and
then run the fake_server.py file.
Once you are connected, you can start also sending commands to the fake simulator,
by creating a client and connecting to the simulator.
(example is in the send_data function).

'''

def send_data():
    """
    SENDING DATA TO SERVER EXAMPLE
    """
    EXAMPLE_VARIABLE = '/controls/switches/magnetos'
    EXAMPLE_VALUE = 4

    client = socket.socket()
    client.connect((TARGET_IP, TARGET_PORT))

    # Example for setting a remote variable, getting a remote variable is
    #   not supported (and also not needed for the exercise)
    out_message = 'set {var} {value}\r\n'.format(
        var=EXAMPLE_VARIABLE, value=EXAMPLE_VALUE)
    logging.info('Sent a message to server: %s', out_message)
    client.send(out_message.encode('ASCII'))


def recv_data():
    """
    RECEIVING DATA FROM THE GEAR
    """
    server = socket.socket()
    server.bind(('', BIND_PORT))
    server.listen(MAX_BACKLOG_SIZE)
    gear_socket, gear_address = server.accept()

    logging.info('Received a connection from %s:%d', *gear_address)
    # Reading data from the gear is simply receiving it,
    #   you can add logic and split it by the telnet-endline (\r\n)
    data = gear_socket.recv(1000).decode('ASCII')
    logging.info('Received data from server:\n%s', data)


def close_socks(server, client):
    server.close()
    client.close()