/**Clase Circulo de la practica 1 de PCTR
  *@author Luis José Quintana Bolaño
  *@version 1.0
*/
import java.lang.Math;
public class Circulo
{
    final static double pi=Math.PI;
    /**Método que contiene el código ejecutable
    @param args Argumentos de la linea de comandos
    @return void
    */
    public static void main(String[] args)
    {
        double d=14.2,h=20.0;
        if(args.length<2)
            System.out.println("Argumentos insuficientes, utilizando medidas por defecto.");
        else{
            d=Integer.parseInt(args[0]);
            h=Integer.parseInt(args[1]);
        }
        System.out.println("\nVolumen del cono (v):");
        System.out.println("  /|\\        v="+((pi*Math.pow(d/2,2)*h)/3)+"cm");
        System.out.println(" / |h="+h+"cm");
        System.out.println("/__|__\\ ");
        System.out.println("    d="+d+"cm");
    }
}
        
