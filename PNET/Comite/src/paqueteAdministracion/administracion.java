package paqueteAdministracion;

import java.util.Map;

import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/comite")
public class administracion {
    @GET
    @Path("/comiteprograma")
    @Produces({"application/json"})
      public Map<String, MiembroCP> getComite() 
    {   
    	return PCdao.getObject();}

    @GET
    @Path("/comiteprograma/{nombre}")
    @Produces(MediaType.TEXT_PLAIN)
      public String getMiembro(@PathParam("nombre") String key) 
    {   
    	MiembroCP miembro =PCdao.getObject().get(key);
    	return miembro.cadena();}

    @DELETE
    @Path("/eliminar/{nombre}")
    @Produces(MediaType.TEXT_PLAIN)
      public String eliminarMiembro(@PathParam("nombre") String key) 
    {   
    	PCdao.getObject().remove(key);
    	return "Done";}    
    
   @POST
    @Path("/agregar/{nombre}")
    @Consumes({"application/json"})
   //@Produces(MediaType.TEXT_PLAIN)
      public void agregarMiembro(@PathParam("nombre") String key, MiembroCP miembro) 
    {   
	   PCdao.getObject().put(key, miembro);
	   //return PCdao.getObject().get(key).cadena();
	   }
    
   @PUT
   @Path("/actualizar/{nombre}")
   @Consumes({"application/json"})
   //@Produces(MediaType.TEXT_PLAIN)
     public void modificarMiembro(@PathParam("nombre") String key, MiembroCP miembro) 
   {   
	   PCdao.getObject().put(key, miembro);
	   //return PCdao.getObject().get(key).cadena();
    }
}
