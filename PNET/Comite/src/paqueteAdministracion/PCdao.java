package paqueteAdministracion;

import java.util.HashMap;
import java.util.Map;

public class PCdao {
	private static Map<String, MiembroCP> myMap = new HashMap<>();
    static{
    MiembroCP miembro = new MiembroCP();
    	miembro.setNombre("Guadalupe");
    	miembro.setApellidos("Apellidos");
    	miembro.setNacionalidad("España");
    	miembro.setAfiliacion("UCA");
    	myMap.put("guadalupe", miembro);
    	myMap.put("otra", miembro);
    	myMap.put("otro", miembro);
    	myMap.put("mas", miembro);      
      }
    static public Map<String, MiembroCP> getObject() {
    	return myMap;
    }
}
