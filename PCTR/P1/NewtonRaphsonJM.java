package Practicas.Practica1;

import java.util.*;
public class NewtonRaphson {
	public static double f(double x){
		x = Math.cos(x) - Math.pow(x, 3);
		return x;
	}
	public static double f_der(double x){
		x = (-1)*Math.sin(x) - 2*Math.pow(x, 2);
		return x;
	}
	public static double g(double x){
		x = Math.pow(x,2)-5;
		return x;
	}
	public static double g_der(double x){
		x = 2*x;
		return x;
	}
	public static void main(String[] args) {
		Scanner A = new Scanner(System.in);
		System.out.println("Introduzca la raiz: ");
		double raiz = A.nextDouble();
		System.out.println("Introduzca el numero de iteraciones: ");
		int iter = A.nextInt();
		double res1 = raiz, res2 = raiz;
		for(int i=0;i<iter;i++){
			res1 = res1 - (f(res1)/f_der(res1));
		}
		for(int i=0;i<iter;i++){
			res2 = res2 - (g(res2)/g_der(res2));
		}
		System.out.println("Aproximacion con f(x) = cos(x) - x^3:\n"+res1);
		System.out.println("Aproximacion con f(x) = x^3 - 5:\n"+res2);
	}

}
