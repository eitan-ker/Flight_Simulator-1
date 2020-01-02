import argparse
import socket
import time
import random
import logging
from threading import Thread, Event, Lock
from xml.etree import ElementTree


'''
Note ** this is an extra script that you can use as you see fit. It may very well be that you'll have to modify it,
if you have a problem with that, then don't use this script and stick to the simulator software.

This script is intended to be used as a replacement for the simulator software, and aims to "mimick" it.

You will need python 3 to run it.

To run: 
First run your server, so this simulator can connect to it.
then run: python fake_server.py -vv

the -vv is just an argument telling the server to run in verbose mode, meaning to print out the statements to the console.

** change generic_small location based on where you are running the python script from.

The server has two threads running, first the client, it blocks until it connects to the server (your server)
and then continues to run and create a server.
Once this client connects to your server is will continue to run in a loop and continuously send you updates using the generic_small values we told it to.
(24 values, in the same order they appear in the xml).
Once this simulator accepts a client (your client), it will be in a continuous loop and accept commands from you.




'''


GENERIC_SMALL_PATH = "./generic_small.xml"
DEFAULT_LISTEN_PORT = 5402 #client
DEFAULT_TARGET_PORT = 5400 #server
DEFAULT_SOCKET_BACKLOG = 5
DEFAULT_SLEEP_INTERVAL = 0.5
CLIENT_UPDATE_INTERVAL = 1 #controls how fast this client sends you values
ALTITUDE_UPDATE_INTERVAL = 1.0

gear_variables = []
gear_variables_lock = Lock()
client_connected_event = Event()


def get_gear_variable(var_name):
    with gear_variables_lock:
        return next((value for value in gear_variables if are_paths_equal(
            value.var_name, var_name)), None)


def gear_variable_to_string():
    with gear_variables_lock:
        update_gear_values()
        #print("len ", len(gear_variables))
        #print("Printing all values before sending")
        #[print(str(variable.var_value),str(variable.var_name)) for variable in gear_variables]
        return ','.join(str(variable.var_value) for variable in gear_variables).encode('ASCII')

def update_gear_values(): #you can control here how fast rpm and alt change.
        rpm = gear_variables[-1]
        print("RPM name - ", rpm.var_name)
        if rpm.var_value < 850:
            rpm.var_value += 20.0
            gear_variables[-1] = rpm
        else:
            alt = gear_variables[4]
            print("ALT name ", alt.var_name)
            alt.var_value += 100
            gear_variables[4] = alt


class GearParams:
    def __init__(self, var_name, var_value):
        self.var_name = var_name
        self.var_value = var_value

    def __getitem__(self, index):
        if index == 0:
            return self.var_name
        if index == 1:
            return self.var_value
        raise IndexError('Invalid index {}'.format(index))

    def __setitem__(self, index, value):
        if index == 0:
            self.var_name = value
        elif index == 1:
            self.var_value = value
        else:
            raise IndexError('Invalid index {}'.format(index))

    def __repr__(self):
        return '(name: {}, value: {})'.format(self.var_name, self.var_value)


class ServerSock:
    NEWLINE = '\r\n'
    RECV_CHUNK = 4096

    def __init__(self, sock):
        self.buff = ''
        self.sock = sock

    def recv(self):
        """
        :rtype str:
        """
        newline_idx = self.buff.find(self.NEWLINE)
        while newline_idx == -1:
            self.buff += self.sock.recv(self.RECV_CHUNK).decode('ASCII')
            newline_idx = self.buff.find(self.NEWLINE)

        msg = self.buff[:newline_idx]
        self.buff = self.buff[newline_idx+len(self.NEWLINE):]
        return msg


def parse_xml(xml_path): #parsing generic_small.xml
    print("----------XML ", xml_path)
    e = ElementTree.parse(xml_path).getroot()
    output = e.findall('generic')[0].findall('output')[0].findall('chunk')
    for x in output:
        gear_variables.append(GearParams(x.find('node').text, 1.0))

    logging.debug(gear_variables)


def are_paths_equal(required_path, full_path):
    """
    The required path might come with or without a
        leading backslash
    :param str required_path:
    :param str full_path:
    """
    return required_path == full_path or required_path[1:] == full_path


def parse_client_input(client_input):
    tokens = client_input.split(' ')
    if tokens[0] == 'set':
        if len(tokens) != 3:
            raise ValueError('Invalid client message {}'.format(client_input))
        param_name = tokens[1]
        param_value = float(tokens[2])
        return param_name, param_value

    raise ValueError('Invalid command {}, Original message: {}'.format(
        tokens[0], client_input))


def handle_input(client_input):
    """
    :param str client_input:
    """
    try:
        param_name, param_value = parse_client_input(client_input)
        variable = get_gear_variable(param_name)
        if variable is not None:
            variable.var_value = float(param_value)
            logging.info('Setting %s to value %f', param_name, param_value)
        else:
            logging.warning('Variable %s was not found', param_name)
    except ValueError as e:
        logging.error(e.args[0])


def server(): #handles input from client
    s = socket.socket()
    s.bind(('', args.listen_port))
    s.listen(args.socket_backlog)
    logging.info('Listening on 0.0.0.0:%d', args.listen_port)
    clientSocket, address = s.accept()
    logging.info('Accepted a connection from %s:%d', *address)
    server = ServerSock(clientSocket)
    while True:
        print("In server waiting for data")
        msg = server.recv()
        logging.debug('msg from client: %s', msg)
        handle_input(msg)


def try_connect(target_ip, target_port, sleep_interval): #tries to connect to server
    """
    :param str target_ip:
    :param int target_port:
    :param float sleep_interval:
    """
    logging.info('Trying to connect: %s:%d...', target_ip, target_port)
    sock = socket.socket()
    while True:
        try:
            sock.connect((target_ip, target_port))
        except Exception:
            #logging.info('Trying to connect')
            time.sleep(sleep_interval)
        else:
            break

    logging.info('Connected as client!')
    return sock


def client(): #acts as client to our server, sends data every certain time interval
    NEWLINE = b'\n'
    sock = try_connect(args.target_ip, args.target_port, args.sleep_interval)
    client_connected_event.set()

    while True:
        time.sleep(CLIENT_UPDATE_INTERVAL)
        to_send = gear_variable_to_string() + NEWLINE
        sock.send(to_send) #notice our server may receive multiple flightdata as one long buffer,
        logging.info('sent to server flight data')
        #but each flight data will be separated by '\n'.
        '''
        Notice a single update contains 36 values, as the number of variables in generic_small.xml.
        example: '0.0,35.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,
        69.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,73.0,
        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,73.0,0.0,0.0,
        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,125.0,0.0,0.0,0.0,0.0,
        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,129.0,0.0,0.0,0.0,0.0,0.0,0.0,
        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,129.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,216.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,246.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
        0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,270.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,
        0.0,0.0,0.0,0.0,0.0,0.0,0.0\n0.0,288.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.'
        '''



def altitude_update(): #logs updated altitude data - increases by random numbers
    ALTITUDE_PARAM_PATH = '/instrumentation/altimeter/indicated-altitude-ft'
    altitude_param = get_gear_variable(ALTITUDE_PARAM_PATH)
    client_connected_event.wait()

    for i in range(100):
        altitude_param.var_value += random.randint(1, 50)
        logging.info('%d - new value: %s: %d', i, altitude_param.var_name,
                     altitude_param.var_value)
        time.sleep(ALTITUDE_UPDATE_INTERVAL)


def main():
    parse_xml(GENERIC_SMALL_PATH)
    Thread(target=client).start() #client thread
    #Thread(target=altitude_update).start() //uncomment to see updates to the altitude
    server() #server thread


def set_verbosity_level():
    if args.verbose == 1:
        logging.getLogger().setLevel(logging.INFO)
    elif args.verbose == 2:
        logging.getLogger().setLevel(logging.DEBUG)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--listen-port', default=DEFAULT_LISTEN_PORT, type=int)
    parser.add_argument('--verbose', '-v', action='count',
                        help='Verbosity level of the output')
    parser.add_argument('--target-ip', default='localhost',)
    parser.add_argument(
        '--target-port', default=DEFAULT_TARGET_PORT, type=int)
    parser.add_argument('--socket-backlog',
                        default=DEFAULT_SOCKET_BACKLOG, type=int)
    parser.add_argument('--sleep-interval',
                        default=DEFAULT_SLEEP_INTERVAL, type=float)
    args = parser.parse_args()
    set_verbosity_level()
    try:
        main()
    except Exception as e:
        logging.exception(e)
