/*
Если в двумерном массиве A нет элементов, абсолютная величина которых
отличается от заданной величины P менее чем на заданную величину E,
найти для каждой его строки среднее арифметическое положительных
элементов.
 */
package com.mycompany.lab_java;

import java.util.Scanner;

/**
 *
 * @author Максим
 */

class Array{
    private final double[][] arr;
    private final int height;
    private final int width;

    Array(int height, int width) {
        this.height = height;
        this.width = width;
        this.arr = new double[height][width];
    }

    Array(double[][] template){
        int h = template.length;
        int w = template[0].length;
        this.height = h;
        this.width = w;
        this.arr = new double[h][w];
        for (int i = 0; i < h; i++){
            System.arraycopy(template[i], 0, this.arr[i], 0, w);
        }
    }

    private double abs(double a){
        if (a < 0)
            return -a;
        return a;
    }

    public void Input(Scanner sc){
        for (int i = 0; i < this.height; i++)
            for (int j = 0; j < this.width; j++){
                double tmp = sc.nextDouble();
                this.arr[i][j] = tmp;
            }

    }

    public boolean ContainsTaskEls(double P, double E){
        for (int i = 0; i < this.height; i++){
            for (int j = 0; j < this.width; j++){
                if (abs(this.arr[i][j] - P) < E){
                    return true;
                }
            }
        }
        return false;
    }

    public double[] GetSAEls(){
        double[] res = new double[this.height];
        for (int i = 0; i < this.height; i++){
            double sum = 0;
            int num = 0;
            for (int j = 0; j < this.width; j++){
                if (this.arr[i][j] > 0){
                    sum += arr[i][j];
                    num++;
                }
            }
            sum /= num;
            res[i] = sum;
        }
        return res;
    }
}

public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите n: ");
        int n = sc.nextInt();
        System.out.print("Введите m: ");
        int m = sc.nextInt();
        System.out.print("Введите P: ");
        double P = sc.nextDouble();
        System.out.print("Введите E: ");
        double E = sc.nextDouble();
        Array arr = new Array(n, m);
        arr.Input(sc);
        if (!arr.ContainsTaskEls(P, E)){
            System.out.println("Нет элементов, абсолютная величина которых отличается" +
                    " от заданной величины " + P + " менее чем на заданную величину " + E);
            double [] res;
            res = arr.GetSAEls();
            for (double el : res){
                System.out.print(el + ' ');
            }
        }

    }
    
}
