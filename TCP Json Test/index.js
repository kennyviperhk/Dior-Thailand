var net = require('net'),
JsonSocket = require('json-socket');

var port = 5555;
var server = net.createServer();
server.listen(port);
server.on('connection', function(socket) {
    socket = new JsonSocket(socket);
    var n;
    var isRunning = false;
    var streamInterval;
    socket.on('message', function(message) {
      console.log('client' + message)
        if (message.command == 'start') {
            if (!isRunning) {
                n = message.beginAt;
                isRunning = true;
                streamInterval = setInterval(function() {
                    socket.sendMessage(n * n);
                    n++;
                }, 1000);
            }
        } else if (message.command == 'stop') {
            if (isRunning) {
                isRunning = false;
                clearInterval(streamInterval);
            }
        }
    });
});

var port = 80; //The same port that the server is listening on
var host = '192.168.0.140';
var socket = new JsonSocket(new net.Socket()); //Decorate a standard net.Socket with JsonSocket
socket.connect(port, host);
socket.on('connect', function() { //Don't send until we're connected
    socket.sendMessage({
    "dest": 887034362,
    "from": 37418,
    "type":9,
    "msg": "The message I want to send"
}

);
    socket.on('message', function(square) {
        console.log('server'+square);
        if (square > 200) {
            socket.sendMessage({command: 'stop'});
        }
    });
});
