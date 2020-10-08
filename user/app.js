var net = require('net');
var fs = require('fs');
var crypto = require('../crypto.js')
var client = new net.Socket();
var mix_amount = 1;

var serverArray = JSON.parse(fs.readFileSync(__dirname + '/server-array.json', 'utf8'));
var message_json = JSON.parse(fs.readFileSync(__dirname + '/message.json', 'utf8'));

//var message = message_json.message;
var datetime = new Date();
console.log(datetime);
var message = datetime.toJSON();

//Mix it!

var used_serverArray = [];
for(var i=0; i < mix_amount; i++){
	used_serverArray[i] = serverArray[i];
}

console.log(used_serverArray);

message = crypto.encryptStringWithRsaPublicKey(JSON.stringify({
			'message_content': message,
			'rand': crypto.randomBytes(256 + Math.floor(Math.random() * Math.floor(20))).toString('hex'),
		}), message_json.recipient.pubkey);

//Encrypt it backwards

for(var i = mix_amount - 1; i >= 0; i--){
	console.log(i);
	if( i == mix_amount - 1 ){
		var recipient = {
			"address": message_json.recipient.address,
			"port":  message_json.recipient.port
		};
		var pubkey = used_serverArray[i].pubkey;
	}else{
		var recipient = {
			"address": used_serverArray[i+1].address,
			"port":  used_serverArray[i+1].port
		};
		var pubkey = used_serverArray[i].pubkey;
	}

	message = crypto.encryptStringWithRsaPublicKey(JSON.stringify({
				'message_content': message,
				'rand': crypto.randomBytes(256 + Math.floor(Math.random() * Math.floor(20))).toString('hex'),
				'recipient': recipient
			}), pubkey);
}
console.log();
console.log("message length: ");
console.log(typeof message);
console.log(message.length);


let promise = new Promise(function(resolve, reject) {
	// executor (the producing code, "singer")
  });

client.connect(used_serverArray[0].port, used_serverArray[0].address, function() {
	console.log('Sent:' + message);
	client.write(message);
});

client.on('close', function() {
	console.log('Connection closed');
});

client.on('error', function(err) {
   console.log(err)
});