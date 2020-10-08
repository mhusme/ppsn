/*
 * @Author: Mehedi H. 
 * @Date: 2020-03-22 13:19:45 
 * @Last Modified by: Mehedi H.
 * @Last Modified time: 2020-10-02 03:22:02
 */


var crypto = require("crypto");
var path = require("path");
var fs = require("fs");

//Encryption
//
var encryptStringWithRsaPublicKey = function(toEncrypt, relativeOrAbsolutePathToPublicKey) {

    //Encrypt message with AES-256-ctr
    var password = crypto.randomBytes(32);
    var cipher = crypto.createCipher('aes-256-ctr', password)
    var crypted = cipher.update(toEncrypt,'utf8','hex')
    crypted += cipher.final('hex');

    //Encrypt password with RSA
    var absolutePath = path.resolve(relativeOrAbsolutePathToPublicKey);
    var publicKey = fs.readFileSync(absolutePath, "utf8");
    var buffer = new Buffer(password);
    var encrypted = crypto.publicEncrypt({
        'key': publicKey,
        'padding': crypto.constants.RSA_PKCS1_PADDING
    }, buffer);

    return JSON.stringify({
        'encrypted_data': crypted,
        'password': encrypted.toString("base64")
    });
};

var decryptStringWithRsaPrivateKey = function(toDecrypt, relativeOrAbsolutePathtoPrivateKey) {

    toDecrypt = JSON.parse(toDecrypt);

    //Decrypt password with RSA
    var absolutePath = path.resolve(relativeOrAbsolutePathtoPrivateKey);
    var privateKey = fs.readFileSync(absolutePath, "utf8");
    var buffer = new Buffer(toDecrypt.password, "base64");
    var decrypted_password = crypto.privateDecrypt({
        'key': privateKey,
        'padding': crypto.constants.RSA_PKCS1_PADDING
    }, buffer);

    //Decrypt message with password
    var decipher = crypto.createDecipher('aes-256-ctr', decrypted_password)
    var dec = decipher.update(toDecrypt.encrypted_data,'hex','utf8')
    dec += decipher.final('utf8');

    return dec;
};

module.exports = {
    encryptStringWithRsaPublicKey: encryptStringWithRsaPublicKey,
    decryptStringWithRsaPrivateKey: decryptStringWithRsaPrivateKey,
    randomBytes: crypto.randomBytes
}
