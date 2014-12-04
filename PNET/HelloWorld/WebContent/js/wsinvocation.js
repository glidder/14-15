/**
*
*/
function getComite(){
	$.ajax({
		type: "GET",
		url: "http://localhost:8080/Comite/administracion/comite/comiteprograma/",
		success: function(data){
			$("#resGetComite").html(data); },
		error:function(res){
			alert("ERROR: "+ res.statusText); }
});
}
function getMiembro(nombre){
	var myUrl = "http://localhost:8080/Comite/administracion/comite/comiteprograma/"+nombre;
	$.ajax({
		type:"GET",
		url: myUrl,
		success: function(data){
			$("#resGetMiembro").html(data);},
		error:function(res){
			alert("ERROR "+res.statusText);}
	});
}
function eliminarMiembro(nombre){
	$.ajax({
		type: "DELETE",
		url: "http://localhost:8080/Comite/administracion/comite/delete/"+nombre,
		success: function(data){
			$("#resdeleteMiembro").html(data);},
		error:function(res){
			alert("ERROR "+ res.statusText); }
	});
}

function agregarMiembro(nombre,datos){
	$.ajax({
		type:"POST",
		url:"http://localhost:8080/Comite/administracion/comite/agregar/"+nombre,
		contentType:"application/json",
		dataType:"json",
		data:JSON.stringify(datos),
		success: function(data){
			$("#resGetHello").html(data);
		},
		error:function(res){
			alert("ERROR"+ res.statusText);
		}
	});
}

function modificarMiembro(nombre,datos){
	$.ajax({
		type:"POST",
		url:"http://localhost:8080/Comite/administracion/comite/actualizar/"+nombre,
		contentType:"application/json",
		dataType:"json",
		data:JSON.stringify(datos),
		success: function(data){
			$("#resGetHello").html(data);
		},
		error:function(res){
			alert("ERROR"+ res.statusText);
		}
	});
}
	
