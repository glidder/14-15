/**
*
*/
function getComite(){
	$.ajax({
		type: "GET",
		url: "http://localhost:8080/Comite/administracion/comite/comiteprograma/",
		success: function(data){
			$("#resSuccess").html(data); },
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
			$("#resSuccess").html(data);},
		error:function(res){
			alert("ERROR "+res.statusText);}
	});
}
function eliminarMiembro(nombre){
	$.ajax({
		type: "DELETE",
		url: "http://localhost:8080/Comite/administracion/comite/eliminar/"+nombre,
		success: function(data){
			$("#resSuccess").html(data);},
		error:function(res){
			alert("ERROR "+ res.statusText); }
	});
}

function agregarMiembro(id,nombre,apellidos,afiliacion,nacionalidad){
	$.ajax({
		type:"POST",
		url:"http://localhost:8080/Comite/administracion/comite/agregar/"+id,
		contentType:"application/json",
		dataType:"json",
		data:JSON.stringify({"nombre":nombre,"apellidos":apellidos,"afiliacion":afiliacion,"nacionalidad":nacionalidad}),
		success: function(data){
			$("#resSuccess").html(data);
		},
		error:function(res){
			alert("ERROR"+ res.statusText);
		}
	});
}

function modificarMiembro(id,nombre,apellidos,afiliacion,nacionalidad){
	$.ajax({
		type:"PUT",
		url:"http://localhost:8080/Comite/administracion/comite/actualizar/"+id,
		contentType:"application/json",
		dataType:"json",
		data:JSON.stringify({"nombre":nombre,"apellidos":apellidos,"afiliacion":afiliacion,"nacionalidad":nacionalidad}),
		success: function(data){
			$("#resSuccess").html(data);
		},
		error:function(res){
			alert("ERROR"+ res.statusText);
		}
	});
}
	
