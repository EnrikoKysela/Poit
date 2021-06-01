from threading import Lock
from flask import Flask, render_template, session, request, jsonify, url_for
from flask_socketio import SocketIO, emit, disconnect    
import time
import random
import math




import serial
import matplotlib.pyplot as plt
import numpy as np
ser=serial.Serial("/dev/ttyS1",9600)
ser.baudrate=9600
read_ser=ser.readline()
y=[]


async_mode = None

app = Flask(__name__)

app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app, async_mode=async_mode)
thread = None
thread_lock = Lock() 









def background_thread(args):
    count = 0             
    while True:
        if args:
          A = dict(args).get('A')
        else:
          A = 1 
        cas = time.time()
        socketio.sleep(0.3)
        count += 1
        
##while read_ser != b"OK\r\n":
        read_ser=ser.readline()
        y.append(float(read_ser))
        print(y[-1])
        #read_ser=ser.readline()
        socketio.emit('my_response',
                      {'data': y[-1], 'count': count},
                      namespace='/test')  

  
@socketio.on('my_event', namespace='/test')
def test_message(message):   
    session['receive_count'] = session.get('receive_count', 0) + 1 
    session['A'] = message['value']    
    emit('my_response',
         {'data': message['value'], 'count': session['receive_count'], 'ampl':1})
 
@socketio.on('connect', namespace='/test')
def test_connect():
    global thread
    with thread_lock:
        if thread is None:
            thread = socketio.start_background_task(target=background_thread, args=session._get_current_object())
    emit('my_response', {'data': 'Connected', 'count': 0})



@socketio.on('disconnect', namespace='/test')
def test_disconnect():
    print('Client disconnected', request.sid)

@socketio.on('disconnect_request', namespace='/test')
def disconnect_request():
    session['receive_count'] = session.get('receive_count', 0) + 1
    emit('my_response',
         {'data': 'Disconnected!', 'count': session['receive_count']})
    disconnect()

@app.route('/')
def index():
    return render_template('tabs.html')

@app.route('/graphlive', methods=['GET', 'POST'])
def graphlive():
    return render_template('graphlive.html', async_mode=socketio.async_mode)

@app.route('/gauge', methods=['GET', 'POST'])
def gauge():
    return render_template('gauge.html', async_mode=socketio.async_mode)

if __name__ == '__main__':
    socketio.run(app, host="0.0.0.0", port=80, debug=True)
