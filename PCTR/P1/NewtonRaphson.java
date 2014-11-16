/**Clase NewtonRaphson de la practica 1 de PCTR
  *@author Luis José Quintana Bolaño
  *@version 1.0
*/
import java.util.*;
public class NewtonRaphson
{
    public static double f1(double x){
        return (Math.cos(x) - Math.pow(x,3));
    }

    public static double f1_p(double x){
        return ((-1)*Math.sin(x) - 2*Math.pow(x,2));
    }

    public static double f2(double x){
        return (Math.pow(x,2)-5);
    }

    public static double f2_p(double x){
        return (2*x);
    }

    /**Método que contiene el código ejecutable
    @param args Argumentos de la linea de comandos
    @return void
    */
    public static void main(String[] args)
    {
        double raiz;
        int iMax;
        if(args.length<2){
            Scanner scan = new Scanner(System.in);
            System.out.println("Introduzca la raiz y el número de iteraciones separados por un espacio:")
            raiz = scan.nextDouble();
            iMax = scan.nextInt();
        }
        else{
            raiz=Double.parseDouble(args[0]);
            iMax=Integer.parseInt(args[1]);
        }
        double aprox=raiz;
        for(int i=0;i<iMax;++i){
            aprox = aprox - (f1(aprox)/f1_p(aprox));
        }
        System.out.println("Aproximación para f(x)=cos()x)-x^3:\n"+aprox);
        aprox=raiz;
        for(int i=0;i<iMax;++i){
            aprox = aprox - (f2(aprox)/f2_p(aprox));
        }
        System.out.println("Aproximación para f(x)=x^3-5:\n"+aprox);
    }
}
        
