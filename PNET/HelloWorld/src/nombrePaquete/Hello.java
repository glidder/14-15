package nombrePaquete;

import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

@Path("/hello")
public class Hello {

	@GET
	@Produces(MediaType.TEXT_PLAIN)
	public String sayPlainTextHello(){return "Hello Plain";}
	
	@GET
	@Path("/hello2")
	@Produces(MediaType.TEXT_PLAIN)
	public String sayPlainTextHello2(){return "Hello Plain 2";}

	@GET
	@Path("/helloId/{oid}")
	@Produces(MediaType.TEXT_PLAIN)
	public String sayHelloWithId(@PathParam("oid")int id)
	{return "Hello Plain " + id;}
	
	@GET
	@Path("/dateJSON")
	@Produces({"application/json"})
	public MyDate getDate_JSON() {
	MyDate oneDate = new MyDate();
	oneDate.setDay(25);
	oneDate.setMonth(12);
	oneDate.setYear (2014);
	return oneDate;}
	
	@GET
	@Path("/dateXML")
	@Produces({"application/xml"})
	public MyDate getDate_XML() {
	MyDate oneDate = new MyDate();
	oneDate.setDay(25);
	oneDate.setMonth(12);
	oneDate.setYear (2014);
	return oneDate;}
	
	@POST
	@Path("/name")
	@Consumes(MediaType.TEXT_PLAIN)
	@Produces(MediaType.TEXT_PLAIN)
	public String HelloName(String name){
	return "Hello "+name;}
	
	@POST
	@Path("/myDate2015")
	@Consumes(MediaType.APPLICATION_JSON)
	@Produces(MediaType.APPLICATION_JSON)
	public MyDate dateToString(MyDate myDate){
	myDate.setYear(2015);
	return myDate;}
}

