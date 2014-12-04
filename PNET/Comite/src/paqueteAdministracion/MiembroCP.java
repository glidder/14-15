package paqueteAdministracion;

import javax.xml.bind.annotation.XmlRootElement;
@XmlRootElement
public class MiembroCP{
	private String nombre, apellidos, afiliacion, nacionalidad;
	public MiembroCP(){}
	public String getNombre() {return nombre;}
	public String getApellidos() {return apellidos;}
	public String getAfiliacion() {return afiliacion;}
	public String getNacionalidad() {return nacionalidad;}
	public void setNombre(String nom) {nombre=nom;}
	public void setApellidos(String ape) {apellidos=ape;}
	public void setAfiliacion(String afi) {afiliacion=afi;}
	public void setNacionalidad(String nac) {nacionalidad=nac;}
	public String cadena(){return nombre+" "+apellidos+", "+afiliacion+" "+nacionalidad;}
}