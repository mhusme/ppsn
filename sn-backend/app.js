var net = require('net');
var crypto = require('../crypto.js');

var port = process.argv[2];
var privkey = process.argv[3];
var totalMessage = 1;
var totalLatency =0;

var server = net.createServer(function(socket) {
	socket.on('data', function(data){
		textChunk = data.toString('utf8');
		console.log('Message recieved: ' + textChunk);
		console.log("--------------------------------------------------");
		console.log("Total Message Received:")
		console.log(totalMessage);
		

		//textChunk = JSON.parse(textChunk);

		var message = crypto.decryptStringWithRsaPrivateKey(textChunk, privkey);
		console.log('Message decrypted: ' + message);

		message = JSON.parse(message);
		console.log('Message parsed: ' + message.message_content);
		var recvTime = new Date();
		var sendTime = new Date(message.message_content);
		console.log(`ReceiveTime: ${recvTime.toJSON()}`);
		console.log(`SentTime: ${sendTime.toJSON()}`);
		var Latency = 2*(recvTime-sendTime);
		totalLatency = totalLatency + Latency;
		var avgLatency = totalLatency/totalMessage;
		console.log(`Latency: ${Latency}ms`);
		console.log(`Average Latency for ${totalMessage} messages: ${avgLatency}ms`);
		totalMessage++;
	});
	socket.pipe(socket);
});

server.listen(port, '127.0.0.1');