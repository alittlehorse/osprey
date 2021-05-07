const  express = require('express');

var app = express();
var server = app.listen(3010);
var io = require('socket.io').listen(server);

io.on('connection', function(socket){
	console.log('用户已经连接');
  
	socket.on('disconnect', function(){
	  console.log('用户已经离开');
	});
	
	//留意on和emit的方法名和前端保持一致  
	socket.on('sendMsgToServer', function(msgObj){
	  console.log('用户'+ msgObj.user + '说：'+ msgObj.msg);
	  io.emit('recvMsgFromServer', msgObj);
	});
  
});

