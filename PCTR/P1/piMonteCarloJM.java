package Practicas.Practica1;

import java.util.*;
import java.lang.*;
public class piMonteCarlo {

	public static void main(String[] args) {
		double CX,CY;
		double numCir=0;
		double coef;
		System.out.println("Introduzca el numero de puntos para obtener pi: ");
		Scanner A = new Scanner(System.in);
		int prec = A.nextInt();
		for(int i=0;i<prec;i++){
			CX = new Random().nextDouble();
			CY = new Random().nextDouble();
			if(Math.sqrt(Math.pow(CX,2)+Math.pow(CY,2))<=1){
				numCir++;
			}
		}
		coef = (numCir/prec);
		coef = 4*coef;
		System.out.println("El valor aproximado de pi es: "+coef);
	}

}
