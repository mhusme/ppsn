var net = require('net');
var crypto = require('../crypto.js');

var port = process.argv[2];
var privkey = process.argv[3];
var totalMessage = 1;

var server = net.createServer(function(socket) {
	socket.on('data', function(data){
		textChunk = data.toString('utf8');
		console.log("--------------------------------------------------");
		console.log("Total Message Received:")
		console.log(totalMessage);
		totalMessage++;
		console.log('Message recieved: ' + textChunk);

		var message = crypto.decryptStringWithRsaPrivateKey(textChunk, privkey);
		console.log("\nMessage decrypted: " + message);

		try {
			message = JSON.parse(message);
		  } catch (e) {
			// Oh well, but whatever...
		  }
		
		console.log("\nMessage parsed: " + JSON.stringify(message));

		var client = new net.Socket();
		client.connect(message.recipient.port, message.recipient.address, function() {
			client.write(message.message_content);
		});
	});
	socket.pipe(socket);
});

server.listen(port, '127.0.0.1');