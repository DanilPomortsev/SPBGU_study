import java.util.Scanner;
import java.lang.Math;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        double accur = in.nextDouble();
        in.close();
        System.out.println("Вычисление погрешностей принципом равных влияний:");
        System.out.print("погрешность для вычисления sin(4.5x + 0.6) - ");
        System.out.println(accur/(3.0*(25)/(18)*Math.sin(1.5)));
        System.out.print("погрешность для вычисления (1 + x - 12x^2)^(1/2) - ");
        System.out.println(accur/(3.0*(5)/(3)*Math.sqrt(2)));
        System.out.println("Вычисление погрешностей принцыпом равных погрешностей:");
        System.out.print("погрешность для вычисления: (1 + x - 12x^2)^(1/2), sin(4.5x + 0.6) - ");
        System.out.println(accur/(25)/(18)*Math.sin(1.5) + (5.0)/(3)*Math.sqrt(2));
        System.out.println("значение функции sin(4.5x + 0.6)/(1 + x - 12x^2)^(1/2) при x = 0.1(0.01)0.2");
        double x = 0.1;
        for(int i = 0; i < 10; ++i){
            System.out.print("x = ");
            System.out.println(x);
            System.out.println(sin(4.5*x+0.6, accur)/ square_root((1+x-12*x*x), accur));
            x = x + 0.01;
        }

        System.out.println("значение функции sin(4.5x + 0.6)/(1 + x - 12x^2)^(1/2) при x = 0.1(0.01)0.2(функции языка)");
        x = 0.1;
        for(int i = 0; i < 10; ++i){
            System.out.print("x = ");
            System.out.println(x);
            System.out.println(Math.sin(4.5*x+0.6)/ Math.sqrt(1+x-12*x*x));
            x = x + 0.01;
        }
        System.out.println("разница в значениях между собственными функциями и функциями языка:");
        x = 0.1;
        for(int i = 0; i < 10; ++i){
            System.out.print("x = ");
            System.out.println(x);
            System.out.println(Math.abs((sin(4.5*x+0.6, accur)/ square_root((1+x-12*x*x), accur)) - (Math.sin(4.5*x+0.6)/ Math.sqrt(1+x-12*x*x))));
            x = x + 0.01;
        }
    }
    static double sin(double x, double full_accur){
        double sin_acurr = full_accur/(2.0*(5)/(3)*Math.sqrt(2));
        double curr_summand = 0;
        double result = x;
        double divisible = x;
        long divider = 1;
        int value_factorial_divider = 2;
        boolean znak = true;
        do{
            divisible *= -x*x;


            divider *= value_factorial_divider++;
            divider *= value_factorial_divider++;
            curr_summand = divisible/divider;
            result += curr_summand;


        }while (Math.abs(curr_summand) >= sin_acurr);
        return result;
    }
    static double square_root(double x, double full_accur){
        double result = 1;
        double past_result;
        double sqrt_acurr = full_accur/(2.0*(25)/(18)*Math.sin(1.5));
        do{
            past_result = result;
            result = 0.5*(result + x/result);

        } while(Math.abs(result - past_result) > sqrt_acurr);
        return result;
    }
}