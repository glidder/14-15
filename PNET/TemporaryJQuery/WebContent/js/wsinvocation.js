/**
*
*/
function getHello(){
	$.ajax({
		type: "GET",
		url: "http://localhost:8080/HelloWorld/demo/hello",
		success: function(data){
			$("#resGetHello").html(data); },
		error:function(res){
			alert("ERROR: "+ res.statusText); }
});
}
function getHelloId(myId){
	var myUrl = "http://localhost:8080/HelloWorld/demo/hello/helloId/"+myId;
	$.ajax({
		type:"GET",
		url: myUrl,
		success: function(data){
			$("#resGetHello").html(data);},
		error:function(res){
			alert("ERROR "+res.statusText);}
	});
}
function getDateJSON(){
	$.ajax({
		type: "GET",
		dataType: "json",
		url: "http://localhost:8080/HelloWorld/demo/hello/dateJSON",
		success: function(data){
			var myDate = data.day+"/"+ data.month+"/"+ data.year;
			$("#resGetHello").html("Date received:"+myDate);},
		error:function(res){
			alert("ERROR "+ res.statusText); }
	});
}

function postHelloName(){
	$.ajax({
		type:"POST",
		url:"http://localhost:8080/HelloWorld/demo/hello/name",
		contentType: "text/plain",
		dataType: "text",
		data: "Luis",
		success: function(data){
			$("#resGetHello").html(data);
		},
		error:function(res){
			alert("ERROR"+ res.statusText);
		}
	});
}
	
	function postDateJSON(){
		$.ajax( {
			type:"POST",
			url:"http://localhost:8080/HelloWorld/demo/hello/myDate2015",
			contentType:"application/json",
			dataType:"json",
			data:JSON.stringify({"day":20,"month":3,"year":2014}),
			success:function(data){
				var newDate = data.day+"/"+data.month+"/"+data.year;
				$("#resGetHello").html("Date received: "+newDate);
			},
			error:function(res){
				alert("ERROR "+ res.statusText); }
		});
	}
